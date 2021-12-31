#include "home_ipcustomizewid.h"
#include "ui_home_ipcustomizewid.h"

Home_IpCustomizewid::Home_IpCustomizewid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_IpCustomizewid)
{
    ui->setupUi(this);
    set_background_icon(this,":/image/back.jpg");
    QTimer::singleShot(15,this,SLOT(initFunSlot()));
}

Home_IpCustomizewid::~Home_IpCustomizewid()
{
    delete ui;
}

void Home_IpCustomizewid::initFunSlot()
{
    this->setEnabled(false);
    mItem = Cfg::bulid()->item;
    mObj = Dev_IpCustomizeCfg::bulid(this);
    mDev = mObj->getDev();
    initWid();
}

void Home_IpCustomizewid::initWid()
{
    QString str = tr("IP-PDU特殊定制后台参数");
    mParamWid = new Home_SetMacWid(ui->tabWidget);
    ui->tabWidget->addTab(mParamWid, str);
    mParamWid->initWid(mDev);
}

void Home_IpCustomizewid::enabledSlot(bool en)
{
    if(mItem->modeId != IP_PDU_CUSTOMIZE) return;

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

bool Home_IpCustomizewid::dataSave()
{
    bool ret = inputCheck();
    if(ret) {
        mParamWid->updateParams();
    }

    return ret;
}

bool Home_IpCustomizewid::inputCheck()
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
