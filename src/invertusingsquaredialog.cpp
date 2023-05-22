#include "invertusingsquaredialog.h"
#include "ui_invertusingsquaredialog.h"


InvertUsingSquareDialog::InvertUsingSquareDialog(QWidget *parent, int &x1, int &y1, int &x2, int &y2, bool &did, int width, int height) :
    QDialog(parent),
    ui(new Ui::InvertUsingSquareDialog), x1In(x1), x2In(x2), y1In(y1), y2In(y2), didIt(did)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    ui->setupUi(this);
    setWindowTitle("Инвертировать");
    ui->info->setText(QString("Размер строки изображения %1 x %2").arg(width).arg(height));
}

InvertUsingSquareDialog::~InvertUsingSquareDialog()
{
    delete ui;
}

void InvertUsingSquareDialog::on_buttonBox_accepted(){
    QString x1String = ui->x1Text->text();
    QString x2String = ui->x2Text->text();
    QString y1String = ui->y1Text->text();
    QString y2String = ui->y2Text->text();
    bool doesx1Int, doesx2Int, doesy1Int, doesy2Int;

    if(x1String == "" || x2String == "" || y1String == "" || y2String == ""){
        QMessageBox::critical(nullptr, "Ошибка", "Заполните все поля");
        didIt = false;
        return;
    }

    x1In = x1String.toInt(&doesx1Int);
    x2In = x2String.toInt(&doesx2Int);
    y1In = y1String.toInt(&doesy1Int);
    y2In = y2String.toInt(&doesy2Int);

    if(!doesx1Int || !doesx2Int || !doesy1Int || !doesy2Int){
        QMessageBox::critical(nullptr, "Ошибка", "Координаты должны быть целыми числами");
        didIt = false;
        return;
    }

    if(x2In - x1In != y2In - y1In){
        QMessageBox::critical(nullptr, "Ошибка", "Введенные координаты не являются углами квадрата");
        didIt = false;
        return;
    }

    if(x2In < x1In || y2In < y1In){
        QMessageBox::critical(nullptr, "Ошибка", "Неверное расположение углов");
        didIt = false;
        return;
    }

    didIt = true;
}
