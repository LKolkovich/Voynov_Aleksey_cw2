#ifndef INVERTUSINGCIRCLEDIALOG_H
#define INVERTUSINGCIRCLEDIALOG_H

#include <QDialog>
#include <QString>
#include <QMessageBox>

namespace Ui {
class InvertUsingCircleDialog;
}

class InvertUsingCircleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InvertUsingCircleDialog(QWidget *parent, int &x, int &y, int &r, bool &did, int width, int height);
    ~InvertUsingCircleDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::InvertUsingCircleDialog *ui;
    int &xIn;
    int &yIn;
    int &rIn;
    bool &didIt;
};

#endif // INVERTUSINGCIRCLEDIALOG_H
