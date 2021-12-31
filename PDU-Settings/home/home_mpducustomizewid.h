#ifndef HOME_MPDUCUSTOMIZEWID_H
#define HOME_MPDUCUSTOMIZEWID_H

#include <QWidget>
#include "home_ipbusbarwid.h"
#include "dev_mpducustomizecfg.h"

namespace Ui {
class Home_MpduCustomizeWid;
}

class Home_MpduCustomizeWid : public QWidget
{
    Q_OBJECT

public:
    explicit Home_MpduCustomizeWid(QWidget *parent = nullptr);
    ~Home_MpduCustomizeWid();
    void initWid();
    bool dataSave();
    bool inputCheck();

signals:
    void errSig();

public slots:
    void initFunSlot();
    void enabledSlot(bool en);
private:
    Ui::Home_MpduCustomizeWid *ui;
    sCfgItem *mItem;
    Dev_Object *mObj;
    sDevData *mDev;

    Home_SetMacWid *mParamWid;

};

#endif // HOME_MPDUCUSTOMIZEWID_H
