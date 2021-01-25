#ifndef HOME_MPDUPARAMWID_H
#define HOME_MPDUPARAMWID_H

#include <QSpinBox>
#include "home_mpdualarmwid.h"

namespace Ui {
class Home_MpduParamWid;
}

class Home_MpduParamWid : public QWidget
{
    Q_OBJECT

public:
    explicit Home_MpduParamWid(QWidget *parent = nullptr);
    ~Home_MpduParamWid();

    void updateType();

protected:
    void initType();
    void initWid();

protected slots:
    void initFunSlot();

private slots:
    void on_verBox_currentIndexChanged(int index);
    void on_boardSpin_valueChanged(int arg1);
    void on_loopBox_currentIndexChanged(int index);

private:
    Ui::Home_MpduParamWid *ui;
    sCfgItem *mItem;
    Dev_Object *mObj;
    sDevData *mDev;

    QSpinBox *mLoops[6];
    QSpinBox *mBoards[3];
};

#endif // HOME_MPDUPARAMWID_H