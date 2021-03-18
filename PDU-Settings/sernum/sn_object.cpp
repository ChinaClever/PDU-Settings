#include "sn_object.h"

Sn_Object::Sn_Object(QObject *parent) : QThread(parent)
{
    QTimer::singleShot(850,this,SLOT(initFunSlot()));
    mPacket = sDataPacket::bulid();
    mItem = Cfg::bulid()->item;
    mPro = mPacket->getPro();

    mDev = nullptr;
    mDt = nullptr;
}

void Sn_Object::initFunSlot()
{
    mModbus = Rtu_Modbus::bulid(this)->get();
    if(!mModbus) QTimer::singleShot(150,this,SLOT(initFunSlot()));
}

void Sn_Object::initDev()
{
    switch (mItem->modeId) {
    case SI_PDU: mDev = mPacket->getSi(); break;
    case IP_PDU: mDev = mPacket->getIp(); break;
    case MPDU: mDev = mPacket->getMpdu(); break;
    }

    if(mDev) mDt = &(mDev->dt);
}
