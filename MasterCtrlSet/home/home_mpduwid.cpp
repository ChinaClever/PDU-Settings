/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "home_mpduwid.h"
#include "ui_home_mpduwid.h"

Home_MpduWid::Home_MpduWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_MpduWid)
{
    ui->setupUi(this);
    set_background_icon(this,":/image/back.jpg");
    QTimer::singleShot(15,this,SLOT(initFunSlot()));
}

Home_MpduWid::~Home_MpduWid()
{
    delete ui;
}

void Home_MpduWid::initFunSlot()
{
    this->setEnabled(false);
    mItem = Cfg::bulid()->item;
    mObj = Dev_Mpdu::bulid(this);
    mDev = mObj->getDev();
    initWid();

    connect(mObj, SIGNAL(setMacSig()), this, SLOT(updateMacSlot()));
}

void Home_MpduWid::initType()
{
    sDevType *dt = &(mDev->dt); //设备类型
    int v = dt->lines-1; if(v) v = 1;
    ui->lineBox->setCurrentIndex(v);
    v = dt->loops-1; if(v>4) v = 4;
    ui->loopBox->setCurrentIndex(v);

    ui->outputSpin->setValue(dt->outputs);
    ui->breakerBox->setCurrentIndex(dt->breaker);
    ui->standardBox->setCurrentIndex(dt->standar);
    ui->seriesBox->setCurrentIndex(dt->series-1);
    ui->modbusBox->setCurrentIndex(dt->modbus);
    ui->languageBox->setCurrentIndex(dt->language);
    ui->macEdit->setText(dt->mac);
}


void Home_MpduWid::initData()
{
    sObjCfg *obj = &(mDev->cfg);
    ui->outputMinSpin->setValue(obj->output.min);
    ui->outputMaxSpin->setValue(obj->output.max);
    ui->outputCrMinSpin->setValue(obj->output.crMin);
    ui->outputCrMaxSpin->setValue(obj->output.crMax);

    ui->curMinSpin->setValue(obj->cur.min);
    ui->curMaxSpin->setValue(obj->cur.max);
    ui->curCrMinSpin->setValue(obj->cur.crMin);
    ui->curCrMaxSpin->setValue(obj->cur.crMax);

    ui->volMinSpin->setValue(obj->vol.min);
    ui->volMaxSpin->setValue(obj->vol.max);

    ui->temMinSpin->setValue(obj->tem.min);
    ui->temMaxSpin->setValue(obj->tem.max);

    ui->humMinSpin->setValue(obj->hum.min);
    ui->humMaxSpin->setValue(obj->hum.max);
}


void Home_MpduWid::initWid()
{
    initType();
    initData();
}


void Home_MpduWid::updateData()
{
    sObjCfg *obj = &(mDev->cfg);
    obj->output.min = ui->outputMinSpin->value();
    obj->output.max = ui->outputMaxSpin->value();
    obj->output.crMin = ui->outputCrMinSpin->value();
    obj->output.crMax = ui->outputCrMaxSpin->value();

    obj->cur.min = ui->curMinSpin->value();
    obj->cur.max = ui->curMaxSpin->value();
    obj->cur.crMin = ui->curCrMinSpin->value();
    obj->cur.crMax = ui->curCrMaxSpin->value();

    obj->vol.min = ui->volMinSpin->value();
    obj->vol.max = ui->volMaxSpin->value();

    obj->tem.min = ui->temMinSpin->value();
    obj->tem.max = ui->temMaxSpin->value();
    obj->hum.min = ui->humMinSpin->value();
    obj->hum.max = ui->humMaxSpin->value();
}


void Home_MpduWid::updateType()
{
    sDevType *dt = &(mDev->dt); //设备类型
    int v = ui->lineBox->currentIndex();
    if(v) v = 3; else v = 1; dt->lines = v;

    v = ui->loopBox->currentIndex()+1;
    if(v > 4) v = 6; dt->loops = v;

    dt->outputs = ui->outputSpin->value();
    dt->breaker = ui->breakerBox->currentIndex();
    dt->standar = ui->standardBox->currentIndex();
    dt->series = ui->seriesBox->currentIndex()+1;

    dt->modbus = ui->modbusBox->currentIndex();
    dt->language = ui->languageBox->currentIndex();
    dt->mac = ui->macEdit->text();
}


void Home_MpduWid::updateMacSlot()
{
    ui->macEdit->setText(mDev->dt.mac);
}


bool Home_MpduWid::inputCheck()
{


    return true;
}

bool Home_MpduWid::dataSave()
{
    bool ret = inputCheck();
    if(ret) {
        updateType();
        updateData();
    }

    return ret;
}

void Home_MpduWid::enabledSlot(bool en)
{
    if(mItem->modeId != MPDU) return;

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
