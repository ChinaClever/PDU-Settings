#ifndef HOME_ZPDUHWWID_H
#define HOME_ZPDUHWWID_H

#include <QWidget>
#include "home_mpduwid.h"
#include "devices/dev_zpduhw.h"
#include "home_zpdualarmwid.h"
#include "home_zpdudebugwid.h"
#include "home_zpdusetwid.h"

namespace Ui {
class Home_ZpduHwWid;
}

class Home_ZpduHwWid : public QWidget
{
    Q_OBJECT

public:
    explicit Home_ZpduHwWid(int index , QWidget *parent = nullptr);
    ~Home_ZpduHwWid();
signals:
    void errSig();
    void sendMpduVerSig(int);

protected:
    void initWid();
    bool inputCheck();
    bool dataSave();

public slots:
    void initFunSlot();
    void enabledSlot(bool en);
    //void indexHiddenSlot(int index);

private:
    Ui::Home_ZpduHwWid *ui;
    sCfgItem *mItem;
    Dev_Object *mObj;
    sDevData *mDev;
    Home_ZpduAlarmWid* mZpduAlarmWid;
    Home_ZpduDebugWid* mZpduDebugWid;
    Home_ZpduSetWid* mZpduSetWid;
    int mindex;
};

#endif // HOME_ZPDUHWWID_H
