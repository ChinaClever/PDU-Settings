#include "home_rpduwid.h"
#include "ui_home_rpduwid.h"

Home_RpduWid::Home_RpduWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_RpduWid)
{
    ui->setupUi(this);
    set_background_icon(this,":/image/back.jpg");
    QTimer::singleShot(15,this,SLOT(initFunSlot()));
}

Home_RpduWid::~Home_RpduWid()
{
    delete ui;
}

void Home_RpduWid::initFunSlot()
{
    this->setEnabled(false);
    mItem = Cfg::bulid()->item;
    mObj = Dev_RpduCfg::bulid(this);
    mDev = mObj->getDev();
    initWid();
}

void Home_RpduWid::initWid()
{
    QString str = tr("RPDU后台参数");
    mParamWid = new Home_SetMacWid(ui->tabWidget);
    ui->tabWidget->addTab(mParamWid, str);
    mParamWid->initWid(mDev);
}

void Home_RpduWid::enabledSlot(bool en)
{
    if(mItem->modeId != RPDU) return;

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

bool Home_RpduWid::dataSave()
{
    bool ret = inputCheck();
    if(ret) {
        mParamWid->updateParams();
    }

    return ret;
}

bool Home_RpduWid::inputCheck()
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
