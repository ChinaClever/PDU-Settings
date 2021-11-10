#include "home_atswid.h"
#include "ui_home_atswid.h"

Home_AtsWid::Home_AtsWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_AtsWid)
{
    ui->setupUi(this);
    set_background_icon(this,":/image/back.jpg");
    QTimer::singleShot(15,this,SLOT(initFunSlot()));
}

Home_AtsWid::~Home_AtsWid()
{
    delete ui;
}

void Home_AtsWid::initFunSlot()
{
    this->setEnabled(false);
    mItem = Cfg::bulid()->item;
    mObj = Dev_AtsCfg::bulid(this);
    mDev = mObj->getDev();
    initWid();
}

void Home_AtsWid::initWid()
{
    QString str = tr("ATS后台参数");
    mParamWid = new Home_SetMacWid(ui->tabWidget);
    ui->tabWidget->addTab(mParamWid, str);
    mParamWid->initWid(mDev);
}

void Home_AtsWid::enabledSlot(bool en)
{
    if(mItem->modeId != ATS) return;

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

bool Home_AtsWid::dataSave()
{
    bool ret = inputCheck();
    if(ret) {
        mParamWid->updateParams();
    }

    return ret;
}

bool Home_AtsWid::inputCheck()
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
