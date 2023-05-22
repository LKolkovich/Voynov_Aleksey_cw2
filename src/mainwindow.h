#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMouseEvent>
#include "image.h"
#include <QLabel>
#include <QColor>
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <iostream>
#include <QPixmap>
#include <string>
#include <cstdlib>
#include <cmath>
#include "invertusingsquaredialog.h"
#include "cutdialog.h"
#include <windows.h>
#include <QSize>
#include <QIcon>
#include "dialogdrawline.h"
#include <QColorDialog>
#include "invertusingcircledialog.h"
#include "drawlinemenudialog.h"
#include "infodialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


enum tools{
    no,
    invert,
    invertSquare,
    cut,
    line
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_open_triggered();
    void on_save_triggered();
    void on_saveAs_triggered();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void showTmpPic();

    void on_invertCircle_clicked();

    void on_drawLine_clicked();

    void on_invertCircleInSquare_clicked();

    void on_cutImg_clicked();

    void on_invertUsingCircleMenu_triggered();

    void on_invertUsingSquareMenu_triggered();


    void on_drawLineMenu_triggered();

    void on_cutMenu_triggered();

    void on_info_triggered();

    void on_back_clicked();

    void on_backMenu_triggered();

private:
    void prepareForCut(int &x1, int &y1, int &x2, int &y2);
    bool DoesBothCoordsOutOfImg(int x1, int y1, int x2, int y2);
    Ui::MainWindow *ui;
    image img;
    QString path;
    image oldImg;

    //x and y position of mouse;
    int xStart;
    int yStart;

    tools tool;
    bool mousePressed;
    int thikness;
    QColor color;
};



#endif // MAINWINDOW_H
