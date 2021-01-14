#ifndef HOME_IPWID_H
#define HOME_IPWID_H

#include "home_siwid.h"

namespace Ui {
class Home_IpWid;
}

class Home_IpWid : public QWidget
{
    Q_OBJECT

public:
    explicit Home_IpWid(QWidget *parent = nullptr);
    ~Home_IpWid();

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

private slots:
    void on_ipTypeBox_currentIndexChanged(int index);

private:
    Ui::Home_IpWid *ui;
    Home_LineUnitWid *mUnitWid;

    sCfgItem *mItem;
    Dev_Object *mObj;
    sDevData *mDev;
};

#endif // HOME_IPWID_H
