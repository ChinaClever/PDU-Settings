#ifndef HOME_SETOPDLG_H
#define HOME_SETOPDLG_H

#include <QDialog>
#include "home_outputwid.h"

namespace Ui {
class Home_SetOpDlg;
}

class Home_SetOpDlg : public QDialog
{
    Q_OBJECT

public:
    explicit Home_SetOpDlg(QWidget *parent = nullptr);
    ~Home_SetOpDlg();

private slots:
    void on_okBtn_clicked();

private:
    Ui::Home_SetOpDlg *ui;
    Home_OutputWid *mOutputWid;
};

#endif // HOME_SETOPDLG_H
