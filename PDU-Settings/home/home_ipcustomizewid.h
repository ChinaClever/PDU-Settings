#ifndef HOME_IPCUSTOMIZEWID_H
#define HOME_IPCUSTOMIZEWID_H

#include <QWidget>
#include "home_mpducustomizewid.h"
#include "dev_ipcustomizecfg.h"

namespace Ui {
class Home_IpCustomizewid;
}

class Home_IpCustomizewid : public QWidget
{
    Q_OBJECT

public:
    explicit Home_IpCustomizewid(QWidget *parent = nullptr);
    ~Home_IpCustomizewid();
    void initWid();
    bool dataSave();
    bool inputCheck();

signals:
    void errSig();

public slots:
    void initFunSlot();
    void enabledSlot(bool en);
private:
    Ui::Home_IpCustomizewid *ui;
    sCfgItem *mItem;
    Dev_Object *mObj;
    sDevData *mDev;

    Home_SetMacWid *mParamWid;
};

#endif // HOME_IPCUSTOMIZEWID_H
