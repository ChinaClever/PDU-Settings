/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "test_object.h"

Test_Object::Test_Object(QObject *parent) : QThread(parent)
{
    isRun = false;
    mPacket = sDataPacket::bulid();
    mItem = Cfg::bulid()->item;
    mPro = mPacket->getPro();
    mDev = nullptr;
    mDt = nullptr;
    QTimer::singleShot(500,this,SLOT(initFunSlot()));
}

Test_Object::~Test_Object()
{
    isRun = false;
    wait();
}

void Test_Object::updateDev()
{
    switch (mItem->modeId) {
    case SI_PDU: mObj = Dev_SiCfg::bulid(this); break;
    case IP_PDU: mObj = Dev_IpCfg::bulid(this); break;
    case MPDU: mObj = Dev_Mpdu::bulid(this); break;
    case ZPDU:  mObj = Dev_ZpduCfg::bulid(this); break;
    case ATS:  mObj = Dev_AtsCfg::bulid(this); break;
    case RPDU:  mObj = Dev_RpduCfg::bulid(this); break;
    case IP_BUSBAR:  mObj = Dev_IpBusbarCfg::bulid(this); break;
    case MPDU_CUSTOMIZE:  mObj = Dev_MpduCustomizeCfg::bulid(this); break;
    case IP_PDU_CUSTOMIZE:  mObj = Dev_IpCustomizeCfg::bulid(this); break;
    }

    if(mObj != NULL) {
        mDev = mObj->getDev();
        mDt = &(mDev->dt);
    }
}
