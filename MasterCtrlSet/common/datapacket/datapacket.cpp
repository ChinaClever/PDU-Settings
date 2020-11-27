/*
 *
 *  Created on: 2020年10月1日
 *      Author: Lzy
 */
#include "datapacket.h"
#include "config.h"

sDataPacket::sDataPacket()
{
    pro = new sProgress();
    dev = new sDevData;
    initCfg();
}


void sDataPacket::initType()
{
    Cfg *cfg = Cfg::bulid();
    sDevType *ptr = &(dev->dt);

    ptr->lines = cfg->read("lines", 1).toInt();
    ptr->loops = cfg->read("loops", 3).toInt();
    ptr->series = cfg->read("series", 4).toInt();
    ptr->breaker = cfg->read("breaker", 1).toInt();
    ptr->outputs = cfg->read("outputs", 24).toInt();
    ptr->language = cfg->read("language", 1).toInt();
    ptr->modbus = cfg->read("modbus", 0).toInt();
    ptr->mac = cfg->read("mac", "").toString();
}

void sDataPacket::initUnit(const QString& prefix, sUnit &unit)
{
    Cfg *cfg = Cfg::bulid();

    unit.en = cfg->read(prefix+"_en", 0).toBool();
    unit.min = cfg->read(prefix+"_min", 0).toFloat();
    unit.max = cfg->read(prefix+"_max", 10).toFloat();

    unit.crMin = cfg->read(prefix+"_crMin", 0).toFloat();
    unit.crMax = cfg->read(prefix+"_crMax", 10).toFloat();
}

void sDataPacket::initData()
{
    sObjData *ptr = &(dev->data);

    initUnit("vol", ptr->vol);
    initUnit("cur", ptr->cur);

    initUnit("tem", ptr->tem);
    initUnit("hum", ptr->hum);

    for(int i=0; i<OpSize; ++i) {
        QString str = "op_" + QString::number(i+1);
        initUnit(str, ptr->opCur[i]);
    }
}

void sDataPacket::initCfg()
{
    initType();
    initData();
}

sDataPacket *sDataPacket::bulid()
{
    static sDataPacket* sington = nullptr;
    if(sington == nullptr)
        sington = new sDataPacket();
    return sington;
}

void sDataPacket::init()
{
    pro->step = 0;
    pro->result = 0;
    pro->item.clear();
    pro->status.clear();
    pro->startTime = QTime::currentTime();

    pro->step = Test_Fun;
    pro->result = Test_Info;
    pro->startTime = QTime::currentTime();
}

bool sDataPacket::updatePro(const QString &str, bool pass, int sec)
{
    pro->time = QTime::currentTime().toString("hh:mm:ss");
    pro->pass << pass;
    pro->itPass << pass;

    pro->item << str;
    pro->status << str;

    if(pass && sec) {
        pass = delay(sec);
    } else {
        pro->step = Test_Over;
        pro->result = Test_Fail;
    }

    return pass;
}

bool sDataPacket::delay(int s)
{
    bool ret = true;
    for(int i=0; i<2*s; ++i) {
        if((pro->step < Test_Over)  || (pro->step > Test_End)){
            QThread::msleep(100);
        } else {
            ret = false;
            break;
        }
    }

    return ret;
}
