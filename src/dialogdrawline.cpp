#include "dialogdrawline.h"
#include "ui_dialogdrawline.h"

DialogDrawLine::DialogDrawLine(QWidget *parent, int &thikness, QColor &color) :
    QDialog(parent),
    ui(new Ui::DialogDrawLine), insideThikness(thikness), colorIn(color)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle("Настройки линии");
}

DialogDrawLine::~DialogDrawLine(){
    delete ui;
}



void DialogDrawLine::on_buttonBox_accepted(){
    bool doesInt;
    QString thiknessStr = ui->thikness->text();
    insideThikness = thiknessStr.toInt(&doesInt);
    if(!doesInt || insideThikness <= 0){
        QMessageBox::critical(nullptr, "Ошибка", "Введите натуральное число");
        return;
    }
    colorIn = QColorDialog::getColor(Qt::red,nullptr,"Выберите цвет линии",QColorDialog::ShowAlphaChannel);
}
