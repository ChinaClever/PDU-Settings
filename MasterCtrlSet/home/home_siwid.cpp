#include "home_siwid.h"
#include "ui_home_siwid.h"

Home_SiWid::Home_SiWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_SiWid)
{
    ui->setupUi(this);
    set_background_icon(this,":/image/back.jpg");
    mUnitWid = new Home_LineUnitWid(ui->groupBox);
    QTimer::singleShot(13,this,SLOT(initFunSlot()));
}

Home_SiWid::~Home_SiWid()
{
    delete ui;
}


void Home_SiWid::initFunSlot()
{
    this->setEnabled(false);
    mObj = Dev_SiCfg::bulid(this);
    mDev = mObj->getDev();
    mUnitWid->init(mDev);
    initType();
}

void Home_SiWid::initType()
{
    sDevType *dt = &(mDev->dt); //设备类型
    int v = dt->lines-1; if(v) v = 1;
    ui->lineBox->setCurrentIndex(v);
    ui->sBox->setCurrentIndex(dt->standar);
}

void Home_SiWid::updateType()
{
    sDevType *dt = &(mDev->dt); //设备类型
    int v = ui->lineBox->currentIndex();
    if(v) v = 3; else v = 1; dt->lines = v;
    dt->standar = ui->sBox->currentIndex();
}

bool Home_SiWid::inputCheck()
{


    return true;
}

bool Home_SiWid::dataSave()
{
    bool ret = inputCheck();
    if(ret) {
        updateType();
        mUnitWid->updateData();
    }

    return ret;
}

void Home_SiWid::enabledSlot(bool en)
{
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
