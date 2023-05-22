#ifndef INVERTUSINGSQUAREDIALOG_H
#define INVERTUSINGSQUAREDIALOG_H

#include <QDialog>
#include <QString>
#include <QMessageBox>


namespace Ui {
class InvertUsingSquareDialog;
}

class InvertUsingSquareDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InvertUsingSquareDialog(QWidget *parent, int &x1, int &y1, int &x2, int &y2, bool &did, int width, int height);
    ~InvertUsingSquareDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::InvertUsingSquareDialog *ui;
    int &x1In;
    int &x2In;
    int &y1In;
    int &y2In;
    bool &didIt;
};

#endif // INVERTUSINGSQUAREDIALOG_H
