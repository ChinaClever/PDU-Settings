#ifndef HOME_SIWID_H
#define HOME_SIWID_H

#include "home_setopdlg.h"

namespace Ui {
class Home_SiWid;
}

class Home_SiWid : public QWidget
{
    Q_OBJECT

public:
    explicit Home_SiWid(QWidget *parent = nullptr);
    ~Home_SiWid();

signals:
    void errSig();

protected:
    void initType();

    void updateType();
    void updateData();

    bool inputCheck();
    bool dataSave();

public slots:
    void initFunSlot();
    void enabledSlot(bool en);
private:
    Ui::Home_SiWid *ui;
    Home_LineUnitWid *mUnitWid;

    Dev_Object *mObj;
    sDevData *mDev;
};

#endif // HOME_SIWID_H
