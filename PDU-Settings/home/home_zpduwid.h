#ifndef HOME_ZPDUWID_H
#define HOME_ZPDUWID_H

#include "home_mpduwid.h"
#include "home_setmacwid.h"
#include "dev_zpducfg.h"

namespace Ui {
class Home_ZpduWid;
}

class Home_ZpduWid : public QWidget
{
    Q_OBJECT

public:
    explicit Home_ZpduWid(QWidget *parent = nullptr);
    ~Home_ZpduWid();
    void initWid();
    bool dataSave();
    bool inputCheck();

signals:
    void errSig();

public slots:
    void initFunSlot();
    void enabledSlot(bool en);
private:
    Ui::Home_ZpduWid *ui;
    sCfgItem *mItem;
    Dev_Object *mObj;
    sDevData *mDev;

    Home_SetMacWid *mParamWid;
};

#endif // HOME_ZPDUWID_H
