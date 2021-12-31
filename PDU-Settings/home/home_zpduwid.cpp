#include "home_zpduwid.h"
#include "ui_home_zpduwid.h"

Home_ZpduWid::Home_ZpduWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_ZpduWid)
{
    ui->setupUi(this);
    set_background_icon(this,":/image/back.jpg");
    QTimer::singleShot(15,this,SLOT(initFunSlot()));
}

Home_ZpduWid::~Home_ZpduWid()
{
    delete ui;
}

void Home_ZpduWid::initFunSlot()
{
    this->setEnabled(false);
    mItem = Cfg::bulid()->item;
    mObj = Dev_ZpduCfg::bulid(this);
    mDev = mObj->getDev();
    initWid();
}

void Home_ZpduWid::initWid()
{
    QString str = tr("ZPDU后台参数");
    mParamWid = new Home_SetMacWid(ui->tabWidget);
    ui->tabWidget->addTab(mParamWid, str);
    mParamWid->initWid(mDev);
}

void Home_ZpduWid::enabledSlot(bool en)
{
    if(mItem->modeId != ZPDU) return;

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

bool Home_ZpduWid::dataSave()
{
    bool ret = inputCheck();
    if(ret) {
        mParamWid->updateParams();
    }

    return ret;
}

bool Home_ZpduWid::inputCheck()
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
