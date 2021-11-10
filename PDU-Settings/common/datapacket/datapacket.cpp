/*
 *
 *  Created on: 2020年10月1日
 *      Author: Lzy
 */
#include "datapacket.h"
#include "config.h"

sDataPacket::sDataPacket()
{
    si = new sDevData;
    ip = new sDevData;
    mpdu = new sDevData;
    zpdu = new sDevData;
    rpdu = new sDevData;
    ats = new sDevData;
    ipBusbar = new sDevData;
    mpduCustomize = new sDevData;
    ippduCustomize = new sDevData;
    pro = new sProgress();
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
    pro->pass.clear();
    pro->itPass.clear();

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
    if(pass) pass = delay(sec);
    else pro->result = Test_Fail;

    return pass;
}

bool sDataPacket::delay(int s)
{
    bool ret = true;
    for(int i=0; i<s; ++i) {
        if((pro->step < Test_Over)  || (pro->step > Test_End)){
            QThread::msleep(100);
        } else {
            ret = false;
            break;
        }
    }

    return ret;
}
