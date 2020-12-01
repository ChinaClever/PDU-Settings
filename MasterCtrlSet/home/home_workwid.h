#ifndef HOME_WORKWID_H
#define HOME_WORKWID_H

#include <QWidget>
#include "home_mpduwid.h"

namespace Ui {
class Home_WorkWid;
}

class Home_WorkWid : public QWidget
{
    Q_OBJECT

public:
    explicit Home_WorkWid(QWidget *parent = nullptr);
    ~Home_WorkWid();

signals:
    void enabledSig(bool en);


private slots:
    void saveErrSlot();
    void on_setBtn_clicked();
    void on_outputBtn_clicked();

public slots:
    void errSlot() {QTimer::singleShot(5,this,SLOT(saveErrSlot()));}

private:
    Ui::Home_WorkWid *ui;

    int mCnt;
    Home_SetOpDlg *mSetOpDlg;
};

#endif // HOME_WORKWID_H
