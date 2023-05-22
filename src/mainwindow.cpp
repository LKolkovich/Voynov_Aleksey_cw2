#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mousePressed = false;
    tool = tools::no;
    setWindowTitle("Графический редактор");

    ui->invertCircle->setIconSize(QSize(30,30));
    ui->invertCircle->setIcon(QIcon(":img/invertCircleIcon.png"));

    ui->invertCircleInSquare->setIconSize(QSize(30,30));
    ui->invertCircleInSquare->setIcon(QIcon(":img/invertSquareIcon.png"));

    ui->drawLine->setIconSize(QSize(30,30));
    ui->drawLine->setIcon(QIcon(":img/drawLineIcon.png"));

    ui->cutImg->setIconSize(QSize(30,30));
    ui->cutImg->setIcon(QIcon(":img/cutIcon.png"));

    ui->drawLine->setIconSize(QSize(30,30));
    ui->drawLine->setIcon(QIcon(":img/line.png"));

    ui->back->setIconSize(QSize(30,30));
    ui->back->setIcon(QIcon(":img/backArrow.png"));

    color = Qt::red;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showTmpPic(){
    ui->label->setFixedSize(img.getWidth(), img.getHeight());
    ui->label->setPixmap(QPixmap::fromImage(img.toQimg()));
}



void MainWindow::on_open_triggered(){
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл", "/home", "PNG_Images (*.png *.jpg)");

    path = fileName;
    if(!img.readPngFile(fileName)){
        oldImg.Copy(img);
        showTmpPic();
    }
}

void MainWindow::on_save_triggered(){
    if(!img.doesExists()){
        QMessageBox::critical(nullptr, "ошибка", "нечего сохранять");
        return;
    }
    img.writePngFile(path);
}

void MainWindow::on_saveAs_triggered(){
    if(!img.doesExists()){
        QMessageBox::critical(nullptr, "ошибка", "нечего сохранять");
        return;
    }
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл как", "/result", "PNG_Images (*.png *.jpg)");

    if(fileName == ""){
        QMessageBox::critical(nullptr, "ошибка", "файл не существует");
        return;
    }
    img.writePngFile(fileName);
}


void MainWindow::mousePressEvent(QMouseEvent *event){
    xStart = event->x() - ui->label->x();
    yStart = event->y() - ui->label->y() - 25;
}

void MainWindow::prepareForCut(int &x1, int &y1, int &x2, int &y2){ // довести до ума
    if(y1 < y2 && x1 < x2){
        return;
    }else if(x1 > x2 && y1 < y2){
        int left = x2;
        int right = x1;
        x1 = left;
        x2 = right;
    }else if(x1 > x2 && y1 > y2){
        int top = y2;
        int down = y1;
        int left = x2;
        int right = x1;
        x1 = left;
        x2 = right;
        y1 = top;
        y2 = down;
    }else if(x1 < x2 && y1 > y2){
        int top = y2;
        int down = y1;
        y1 = top;
        y2 = down;
    }
}

bool MainWindow::DoesBothCoordsOutOfImg(int x1, int y1, int x2, int y2){
    bool firstOut = false;
    bool secondOut = false;
    if(x1 < 0 || x1 > img.getWidth() || y1 < 0 || y1 > img.getHeight())
        firstOut = true;
    if(x2 < 0 || x2 > img.getWidth() || y2 < 0 || y2 > img.getHeight())
        secondOut = true;

    return  firstOut && secondOut;
}


void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    int xFin = event->x() - ui->label->x();
    int yFin = event->y() - ui->label->y() - 25;

    if(tool == tools::invert){
        int r = sqrt(pow(xFin - xStart, 2) + pow(yFin - yStart, 2));
        if(r <= 0){
            QMessageBox::critical(nullptr, "ошибка", "Радиус должен быть натуральным числом");
            return;
        }
        img.invertCircle(xStart, yStart, sqrt(pow(xFin - xStart, 2) + pow(yFin - yStart, 2)));
    }else if(tool == tools::line){
        img.drawLine(xStart, yStart, xFin, yFin, color, thikness);
    }else if(tool == tools::invertSquare){
        prepareForCut(xStart, yStart, xFin, yFin);
        if(img.invertCircle(xStart, yStart, xFin, yFin))
            QMessageBox::critical(nullptr, "ошибка", "нарисуйте квадрат или введите координаты углов через инструменты");
    }else if(tool == tools::cut){
        if(DoesBothCoordsOutOfImg(xStart, yStart, xFin, yFin)){
            QMessageBox::critical(nullptr, "ошибка", "обе точки находятся вне изображения");
            return;
        }
        prepareForCut(xStart, yStart, xFin, yFin);
        img.cutImage(xStart, yStart, xFin, yFin);
    }

    if(tool != tools::no)
        showTmpPic();
}

void MainWindow::on_invertCircle_clicked(){
    if(!img.doesExists()){
        QMessageBox::critical(nullptr, "Ошибка", "Загрузите изображение с помощью 'файл->открыть'");
        return;
    }
    tool = tools::invert;
}



void MainWindow::on_drawLine_clicked(){
    if(!img.doesExists()){
        QMessageBox::critical(nullptr, "Ошибка", "Загрузите изображение с помощью 'файл->открыть'");
        return;
    }
    tool = tools::line;
    DialogDrawLine drawlinewindow(nullptr, thikness, color);
    drawlinewindow.exec();
}

void MainWindow::on_invertCircleInSquare_clicked(){
    if(!img.doesExists()){
        QMessageBox::critical(nullptr, "Ошибка", "Загрузите изображение с помощью 'файл->открыть'");
        return;
    }
    tool = tools::invertSquare;

}

void MainWindow::on_cutImg_clicked(){
    if(!img.doesExists()){
        QMessageBox::critical(nullptr, "Ошибка", "Загрузите изображение с помощью 'файл->открыть'");
        return;
    }
    tool = tools::cut;
}

void MainWindow::on_invertUsingCircleMenu_triggered(){// int &x, int &y, int &r, int width, int height);
    if(!img.doesExists()){
        QMessageBox::critical(nullptr, "Ошибка", "Загрузите изображение с помощью 'файл->открыть'");
        return;
    }
    int x, y, r;
    bool didIt = false;
    InvertUsingCircleDialog invertWindow(nullptr, x, y, r, didIt, img.getWidth(), img.getHeight());
    invertWindow.exec();
    if(didIt){
        img.invertCircle(x, y, r);
        showTmpPic();
    }
}



void MainWindow::on_invertUsingSquareMenu_triggered(){
    if(!img.doesExists()){
        QMessageBox::critical(nullptr, "Ошибка", "Загрузите изображение с помощью 'файл->открыть'");
        return;
    }

    int x1, y1, x2, y2;
    bool didIt = false;

    InvertUsingSquareDialog invertWindow(nullptr, x1, y1, x2, y2, didIt, img.getWidth(), img.getHeight());
    invertWindow.exec();
    if(didIt){
        img.invertCircle(x1, y1, x2, y2);
        showTmpPic();
    }
}


void MainWindow::on_drawLineMenu_triggered()
{
    if(!img.doesExists()){
        QMessageBox::critical(nullptr, "Ошибка", "Загрузите изображение с помощью 'файл->открыть'");
        return;
    }

    int x1, y1, x2, y2;
    bool didIt = false;

    DrawLineMenuDialog drawWindow(nullptr, x1, y1, x2, y2, thikness, didIt, color, img.getWidth(), img.getHeight());
    drawWindow.exec();
    if(didIt){
        img.drawLine(x1, y1, x2, y2, color, thikness);
        showTmpPic();
    }
}

void MainWindow::on_cutMenu_triggered()
{
    if(!img.doesExists()){
        QMessageBox::critical(nullptr, "Ошибка", "Загрузите изображение с помощью 'файл->открыть'");
        return;
    }

    int x1, y1, x2, y2;
    bool didIt = false;
    CutDialog cutWindow(nullptr, x1, y1, x2, y2, didIt, img.getWidth(), img.getHeight());
    cutWindow.exec();

    if(DoesBothCoordsOutOfImg(x1, y1, x2, y2)){
        QMessageBox::critical(nullptr, "ошибка", "обе точки находятся вне изображения");
        return;
    }
    if(didIt){
        prepareForCut(x1, y1, x2, y2);
        img.cutImage(x1, y1, x2, y2);
        showTmpPic();
    }
}

void MainWindow::on_info_triggered()
{
    InfoDialog infoWindow;
    infoWindow.exec();
}

void MainWindow::on_back_clicked()
{
    if(img.doesExists()){
        img.Copy(oldImg);
        showTmpPic();
    }
}

void MainWindow::on_backMenu_triggered()
{
    if(img.doesExists()){
        img.Copy(oldImg);
        showTmpPic();
    }
}
