#ifndef HOME_MAINWID_H
#define HOME_MAINWID_H

#include <QWidget>
#include "home_workwid.h"
#include "home_mpducustomizewid.h"
#include "home_ipcustomizewid.h"
#include "home_zpduhwwid.h"

namespace Ui {
class Home_MainWid;
}

class Home_MainWid : public QWidget
{
    Q_OBJECT

public:
    explicit Home_MainWid(QWidget *parent = nullptr);
    ~Home_MainWid();

signals:
    void startSig();

protected:
    void initWid();

private:
    Ui::Home_MainWid *ui;
    Home_IpWid *mIpWid;
    Home_SiWid *mSiWid;
    Home_WorkWid *mWorkWid;
    Home_MpduWid *mMpduWid;
    Home_ZpduWid *mZpduWid;
    Home_RpduWid *mRpduWid;
    Home_AtsWid *mAtsWid;
    Home_IpBusbarwid *mIpBusbarWid;
    Home_MpduCustomizeWid *mMpduCustomizeWid;
    Home_IpCustomizewid *mIpCustomizeWid;
    Home_ZpduHwWid *mZpduHwWid;
    Home_ZpduHwWid *mZpduStdWid;
    Home_ZpduHwWid *mZpduNetSafeWid;
};

#endif // HOME_MAINWID_H
