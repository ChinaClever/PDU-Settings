#ifndef HOME_MPDUBWID_H
#define HOME_MPDUBWID_H

#include <QWidget>
#include "common.h"

namespace Ui {
class Home_MpdubWid;
}

class Home_MpdubWid : public QWidget
{
    Q_OBJECT

public:
    explicit Home_MpdubWid(QWidget *parent = nullptr);
    ~Home_MpdubWid();

signals:
    void errSig();

protected:
    void initWid();

    bool inputCheck();
    void dataSave();

public slots:
    void enabledSlot(bool en);

private:
    Ui::Home_MpdubWid *ui;
    sDevData *mDev;
};

#endif // HOME_MPDUBWID_H
