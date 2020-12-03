#include "dev_ipcfg.h"

Dev_IpCfg::Dev_IpCfg(QObject *parent) : Dev_Object(parent)
{
    mDev = mPacket->getIp();
    mDt = &(mDev->dt);
    initCfg();
}


Dev_IpCfg *Dev_IpCfg::bulid(QObject *parent)
{
    static Dev_IpCfg* sington = nullptr;
    if(sington == nullptr)
        sington = new Dev_IpCfg(parent);
    return sington;
}


void Dev_IpCfg::initType()
{
    sDevType *ptr = mDt;
    ptr->ac = read("ac", 1).toInt();
    ptr->versions = read("versions", 1).toInt();
    ptr->lines = read("lines", 1).toInt();
    ptr->standar = read("standar", 0).toInt();

    ptr->language = read("language", 1).toInt();
    ptr->modbus = read("modbus", 0).toInt();
    ptr->logs = read("logs", 0).toInt();
    ptr->mac = read("mac", "").toString();
}

void Dev_IpCfg::writeType()
{
    sDevType *ptr = mDt;
    write("ac", ptr->ac);
    write("versions", ptr->versions);
    write("lines", ptr->lines);
    write("standar", ptr->standar);

    write("language", ptr->language);
    write("modbus", ptr->modbus);
    write("logs", ptr->logs);
    write("mac", ptr->mac);
}

void Dev_IpCfg::initData()
{
    sObjCfg *ptr = &(mDev->cfg);
    initUnit("vol", ptr->vol);
    initUnit("cur", ptr->cur);

    initUnit("tem", ptr->tem);
    initUnit("hum", ptr->hum);
}

void Dev_IpCfg::writeData()
{
    sObjCfg *ptr = &(mDev->cfg);
    writeUnit("vol", ptr->vol);
    writeUnit("cur", ptr->cur);

    writeUnit("tem", ptr->tem);
    writeUnit("hum", ptr->hum);
}

void Dev_IpCfg::initCfg()
{
    initType();
    initData();
}

void Dev_IpCfg::save()
{
    writeType();
    writeData();
}
