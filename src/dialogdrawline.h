#ifndef DIALOGDRAWLINE_H
#define DIALOGDRAWLINE_H

#include <QDialog>
#include <QString>
#include <QMessageBox>
#include <QColor>
#include <QColorDialog>

namespace Ui {
class DialogDrawLine;
}

class DialogDrawLine : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDrawLine(QWidget *parent, int &thikness, QColor &color) ;
    ~DialogDrawLine();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogDrawLine *ui;
    int &insideThikness;
    QColor &colorIn;
};

#endif // DIALOGDRAWLINE_H
