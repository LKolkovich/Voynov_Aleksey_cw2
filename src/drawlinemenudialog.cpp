#include "drawlinemenudialog.h"
#include "ui_drawlinemenudialog.h"


DrawLineMenuDialog::DrawLineMenuDialog(QWidget *parent, int &x1, int &y1, int &x2, int &y2, int &thick, bool &did, QColor &color, int width, int height) :
    QDialog(parent),
    ui(new Ui::DrawLineMenuDialog), x1In(x1), x2In(x2), y1In(y1), y2In(y2), didIt(did), thickIn(thick), colorIn(color)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->setupUi(this);
    setWindowTitle("Нарисовать линию");

    ui->info->setText(QString("Размер строки изображения %1 x %2").arg(width).arg(height));
}

DrawLineMenuDialog::~DrawLineMenuDialog()
{
    delete ui;
}

void DrawLineMenuDialog::on_buttonBox_accepted()
{
    QString x1String = ui->x1Text->text();
    QString x2String = ui->x2Text->text();
    QString y1String = ui->y1Text->text();
    QString y2String = ui->y2Text->text();
    QString thickString = ui->thickText->text();
    bool changeColor = ui->ChangeColor->isChecked();
    bool doesx1Int, doesx2Int, doesy1Int, doesy2Int, doesThickInt;

    if(x1String == "" || x2String == "" || y1String == "" || y2String == "" || thickString == ""){
        QMessageBox::critical(nullptr, "Ошибка", "Заполните все поля");
        didIt = false;
        return;
    }

    x1In = x1String.toInt(&doesx1Int);
    x2In = x2String.toInt(&doesx2Int);
    y1In = y1String.toInt(&doesy1Int);
    y2In = y2String.toInt(&doesy2Int);
    thickIn = thickString.toInt(&doesThickInt);

    if(!doesx1Int || !doesx2Int || !doesy1Int || !doesy2Int){
        QMessageBox::critical(nullptr, "Ошибка", "Координаты должны быть целыми числами");
        didIt = false;
        return;
    }

    if(!doesThickInt || thickIn <= 0){
        QMessageBox::critical(nullptr, "Ошибка", "Толщина должна быть натуральным числом");
        didIt = false;
        return;
    }

    if(changeColor){
        colorIn = QColorDialog::getColor(Qt::red,nullptr,"Выберите цвет линии",QColorDialog::ShowAlphaChannel);
    }

    didIt = true;
}
