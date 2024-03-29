#ifndef HOME_ATSWID_H
#define HOME_ATSWID_H

#include "home_rpduwid.h"
#include "dev_atscfg.h"

namespace Ui {
class Home_AtsWid;
}

class Home_AtsWid : public QWidget
{
    Q_OBJECT

public:
    explicit Home_AtsWid(QWidget *parent = nullptr);
    ~Home_AtsWid();
    void initWid();
    bool dataSave();
    bool inputCheck();

signals:
    void errSig();

public slots:
    void initFunSlot();
    void enabledSlot(bool en);
private:
    Ui::Home_AtsWid *ui;
    sCfgItem *mItem;
    Dev_Object *mObj;
    sDevData *mDev;

    Home_SetMacWid *mParamWid;
};

#endif // HOME_ATSWID_H
