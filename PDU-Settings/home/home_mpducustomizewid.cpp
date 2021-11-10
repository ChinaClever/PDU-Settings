#include "home_mpducustomizewid.h"
#include "ui_home_mpducustomizewid.h"

Home_MpduCustomizeWid::Home_MpduCustomizeWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_MpduCustomizeWid)
{
    ui->setupUi(this);
    set_background_icon(this,":/image/back.jpg");
    QTimer::singleShot(15,this,SLOT(initFunSlot()));
}

Home_MpduCustomizeWid::~Home_MpduCustomizeWid()
{
    delete ui;
}

void Home_MpduCustomizeWid::initFunSlot()
{
    this->setEnabled(false);
    mItem = Cfg::bulid()->item;
    mObj = Dev_MpduCustomizeCfg::bulid(this);
    mDev = mObj->getDev();
    initWid();
}

void Home_MpduCustomizeWid::initWid()
{
    QString str = tr("MPDU一期/特殊定制后台参数");
    mParamWid = new Home_SetMacWid(ui->tabWidget);
    ui->tabWidget->addTab(mParamWid, str);
    mParamWid->initWid(mDev);
}

void Home_MpduCustomizeWid::enabledSlot(bool en)
{
    if(mItem->modeId != MPDU_CUSTOMIZE) return;

    this->setEnabled(en);
    if(!en) {
        en = dataSave();
        if(en) {
            mObj->save();
        } else {
            emit errSig();
        }
    }
}

bool Home_MpduCustomizeWid::dataSave()
{
    bool ret = inputCheck();
    if(ret) {
        mParamWid->updateParams();
    }

    return ret;
}

bool Home_MpduCustomizeWid::inputCheck()
{
    QString str;
    bool ret = mParamWid->Check();
    if(!ret) str += tr("每个参数不能为空！\n");
    if(!str.isEmpty()) {
        MsgBox::critical(this, str);
        ret = false;
    }

    return ret;
}
