#include "mainwindow.h"
#include "image.h"


#include <QApplication>
#include <iostream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":img/appIcon.png"));
    MainWindow w;


    w.show();
    return a.exec();
}
