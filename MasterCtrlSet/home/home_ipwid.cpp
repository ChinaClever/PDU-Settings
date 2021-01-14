/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "home_ipwid.h"
#include "ui_home_ipwid.h"

Home_IpWid::Home_IpWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_IpWid)
{
    ui->setupUi(this);
    set_background_icon(this,":/image/back.jpg");
    mUnitWid = new Home_LineUnitWid(ui->groupBox);
    QTimer::singleShot(10,this,SLOT(initFunSlot()));
}

Home_IpWid::~Home_IpWid()
{
    delete ui;
}

void Home_IpWid::initFunSlot()
{
    this->setEnabled(false);
    mObj = Dev_IpCfg::bulid(this);
    mItem = Cfg::bulid()->item;
    mDev = mObj->getDev();
    mUnitWid->init(mDev);
    initType();
}

void Home_IpWid::initType()
{
    sDevType *dt = &(mDev->dt); //设备类型
    int v = dt->version-1; if(v) v = 1;
    ui->ipTypeBox->setCurrentIndex(v);
    on_ipTypeBox_currentIndexChanged(v);

    ui->logBox->setCurrentIndex(dt->log_en);
    ui->sBox->setCurrentIndex(dt->standar);
    ui->lineBox->setCurrentIndex(dt->lines-1);
    ui->ipModeBox->setCurrentIndex(dt->modbus);
    ui->languageBox->setCurrentIndex(dt->language);
}


void Home_IpWid::updateType()
{
    sDevType *dt = &(mDev->dt); //设备类型
    int v = ui->ipTypeBox->currentIndex()+1;
    if(v > 1) v = 3; dt->version = v;

    dt->lines = ui->lineBox->currentIndex()+1;
    dt->modbus = ui->ipModeBox->currentIndex();
    dt->standar = ui->sBox->currentIndex();
    dt->log_en = ui->logBox->currentIndex();
    dt->language = ui->languageBox->currentIndex();
}

bool Home_IpWid::inputCheck()
{


    return true;
}

bool Home_IpWid::dataSave()
{
    bool ret = inputCheck();
    if(ret) {
        updateType();
        mUnitWid->updateData();
    }

    return ret;
}

void Home_IpWid::enabledSlot(bool en)
{
    if(mItem->modeId != IP_PDU) return;

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

void Home_IpWid::on_ipTypeBox_currentIndexChanged(int index)
{
    bool res = true;
    if(index)  res = false;

    ui->sBox->setHidden(res);
    ui->logBox->setHidden(res);
    ui->label_8->setHidden(res);
    ui->label_11->setHidden(res);
}
