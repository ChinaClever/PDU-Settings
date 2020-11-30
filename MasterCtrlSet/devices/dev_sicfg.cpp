#include "dev_sicfg.h"

Dev_SiCfg::Dev_SiCfg(QObject *parent) : Dev_Object(parent)
{
    mDev = mPacket->getSi();
    mDt = &(mDev->dt);
    initCfg();
}

Dev_SiCfg *Dev_SiCfg::bulid(QObject *parent)
{
    static Dev_SiCfg* sington = nullptr;
    if(sington == nullptr)
        sington = new Dev_SiCfg(parent);
    return sington;
}

void Dev_SiCfg::initType()
{
    sDevType *ptr = mDt;
    ptr->ac = read("ac", 1).toInt();
    ptr->lines = read("lines", 1).toInt();
    ptr->standar = read("standar", 0).toInt();
}

void Dev_SiCfg::writeType()
{
    sDevType *ptr = mDt;
    write("ac", ptr->ac);
    write("lines", ptr->lines);
    write("standar", ptr->standar);
}

void Dev_SiCfg::initData()
{
    sObjData *ptr = &(mDev->data);
    initUnit("vol", ptr->vol);
    initUnit("cur", ptr->cur);

    initUnit("tem", ptr->tem);
    initUnit("hum", ptr->hum);
}

void Dev_SiCfg::writeData()
{
    sObjData *ptr = &(mDev->data);
    writeUnit("vol", ptr->vol);
    writeUnit("cur", ptr->cur);

    writeUnit("tem", ptr->tem);
    writeUnit("hum", ptr->hum);
}

void Dev_SiCfg::initCfg()
{
    initType();
    initData();
}

void Dev_SiCfg::save()
{
    writeType();
    writeData();
}
