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
}
