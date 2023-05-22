#ifndef DRAWLINEMENUDIALOG_H
#define DRAWLINEMENUDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QColor>
#include <QColorDialog>

namespace Ui {
class DrawLineMenuDialog;
}

class DrawLineMenuDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DrawLineMenuDialog(QWidget *parent, int &x1, int &y1, int &x2, int &y2, int &thick, bool &did, QColor &color, int width, int height);
    ~DrawLineMenuDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DrawLineMenuDialog *ui;
    int &x1In;
    int &x2In;
    int &y1In;
    int &y2In;
    bool &didIt;
    int &thickIn;
    QColor &colorIn;
};

#endif // DRAWLINEMENUDIALOG_H
