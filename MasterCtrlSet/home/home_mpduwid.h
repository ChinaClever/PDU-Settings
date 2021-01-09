#ifndef HOME_MPDUBWID_H
#define HOME_MPDUBWID_H

#include <QWidget>
#include "home_ipwid.h"

namespace Ui {
class Home_MpduWid;
}

class Home_MpduWid : public QWidget
{
    Q_OBJECT

public:
    explicit Home_MpduWid(QWidget *parent = nullptr);
    ~Home_MpduWid();

signals:
    void errSig();

protected:
    void initType();
    void initData();
    void initWid();

    void updateType();
    void updateData();

    bool inputCheck();
    bool dataSave();

public slots:
    void initFunSlot();
    void enabledSlot(bool en);

private:
    Ui::Home_MpduWid *ui;
    sCfgItem *mItem;
    Dev_Object *mObj;
    sDevData *mDev;
};

#endif // HOME_MPDUBWID_H
