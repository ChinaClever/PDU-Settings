#include "home_ipbusbarwid.h"
#include "ui_home_ipbusbarwid.h"

Home_IpBusbarwid::Home_IpBusbarwid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_IpBusbarwid)
{
    ui->setupUi(this);
    set_background_icon(this,":/image/back.jpg");
    QTimer::singleShot(15,this,SLOT(initFunSlot()));
}

Home_IpBusbarwid::~Home_IpBusbarwid()
{
    delete ui;
}

void Home_IpBusbarwid::initFunSlot()
{
    this->setEnabled(false);
    mItem = Cfg::bulid()->item;
    mObj = Dev_IpBusbarCfg::bulid(this);
    mDev = mObj->getDev();
    initWid();
}

void Home_IpBusbarwid::initWid()
{
    QString str = tr("IP-Busbar后台参数");
    mParamWid = new Home_SetMacWid(ui->tabWidget);
    ui->tabWidget->addTab(mParamWid, str);
    mParamWid->initWid(mDev);
}

void Home_IpBusbarwid::enabledSlot(bool en)
{
    if(mItem->modeId != IP_BUSBAR) return;

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

bool Home_IpBusbarwid::dataSave()
{
    bool ret = inputCheck();
    if(ret) {
        mParamWid->updateParams();
    }

    return ret;
}

bool Home_IpBusbarwid::inputCheck()
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
