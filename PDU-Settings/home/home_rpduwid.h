#ifndef HOME_RPDUWID_H
#define HOME_RPDUWID_H

#include "home_zpduwid.h"
#include "dev_rpducfg.h"

namespace Ui {
class Home_RpduWid;
}

class Home_RpduWid : public QWidget
{
    Q_OBJECT

public:
    explicit Home_RpduWid(QWidget *parent = nullptr);
    ~Home_RpduWid();
    void initWid();
    bool dataSave();
    bool inputCheck();

signals:
    void errSig();

public slots:
    void initFunSlot();
    void enabledSlot(bool en);
private:
    Ui::Home_RpduWid *ui;
    sCfgItem *mItem;
    Dev_Object *mObj;
    sDevData *mDev;

    Home_SetMacWid *mParamWid;

};

#endif // HOME_RPDUWID_H
