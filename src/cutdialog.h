#ifndef CUTDIALOG_H
#define CUTDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class CutDialog;
}

class CutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CutDialog(QWidget *parent, int &x1, int &y1, int &x2, int &y2, bool &did, int width, int height);
    ~CutDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::CutDialog *ui;
    int &x1In;
    int &x2In;
    int &y1In;
    int &y2In;
    bool &didIt;
};

#endif // CUTDIALOG_H
