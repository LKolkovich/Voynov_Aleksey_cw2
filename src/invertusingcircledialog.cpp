#include "invertusingcircledialog.h"
#include "ui_invertusingcircledialog.h"


InvertUsingCircleDialog::InvertUsingCircleDialog(QWidget *parent, int &x, int &y, int &r, bool &did, int width, int height) :
    QDialog(parent),
    ui(new Ui::InvertUsingCircleDialog), xIn(x), yIn(y), rIn(r), didIt(did)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->setupUi(this);
    setWindowTitle("Инвертировать");

    ui->info->setText(QString("Размер строки изображения %1 x %2").arg(width).arg(height));
}

InvertUsingCircleDialog::~InvertUsingCircleDialog()
{
    delete ui;
}

void InvertUsingCircleDialog::on_buttonBox_accepted(){
    bool doesXint, doesYint, doesRint;
    QString xString = ui->xCenter->text();
    QString yString = ui->yCenter->text();
    QString rString = ui->radius->text();
    if(rString == "" || xString == "" || yString == ""){
        QMessageBox::critical(nullptr, "Ошибка", "Заполните все поля");
        didIt = false;
        return;
    }

    xIn = xString.toInt(&doesXint);
    yIn = yString.toInt(&doesYint);
    rIn = rString.toInt(&doesRint);

    if(!doesRint || !doesXint || !doesYint || rIn <= 0){
        QMessageBox::critical(nullptr, "Ошибка", "Радиус должен быть натуральным числом, а координаты целыми");
        didIt = false;
        return;
    }

    didIt = true;
}
