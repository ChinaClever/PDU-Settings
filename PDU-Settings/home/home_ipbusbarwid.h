#ifndef HOME_IPBUSBARWID_H
#define HOME_IPBUSBARWID_H

#include "home_atswid.h"
#include "dev_ipbusbarcfg.h"

namespace Ui {
class Home_IpBusbarwid;
}

class Home_IpBusbarwid : public QWidget
{
    Q_OBJECT

public:
    explicit Home_IpBusbarwid(QWidget *parent = nullptr);
    ~Home_IpBusbarwid();

    void initWid();
    bool dataSave();
    bool inputCheck();

signals:
    void errSig();

public slots:
    void initFunSlot();
    void enabledSlot(bool en);
private:
    Ui::Home_IpBusbarwid *ui;
    sCfgItem *mItem;
    Dev_Object *mObj;
    sDevData *mDev;

    Home_SetMacWid *mParamWid;
};

#endif // HOME_IPBUSBARWID_H
