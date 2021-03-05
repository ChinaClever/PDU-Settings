/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
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
    ptr->ac = read("ip_ac", 1).toInt();
    ptr->version = read("ip_version", 1).toInt();
    ptr->lines = read("ip_lines", 1).toInt();
    ptr->standar = read("ip_standar", 0).toInt();

    ptr->language = read("ip_language", 1).toInt();
    ptr->modbus = read("ip_modbus", 0).toInt();
    ptr->log_en = read("log_en", 0).toInt();
    ptr->ip_lcd = read("ip_lcd", 0).toInt();
}

void Dev_IpCfg::writeType()
{
    sDevType *ptr = mDt;
    write("ip_ac", ptr->ac);
    write("ip_version", ptr->version);
    write("ip_lines", ptr->lines);
    write("ip_standar", ptr->standar);

    write("ip_language", ptr->language);
    write("ip_modbus", ptr->modbus);
    write("log_en", ptr->log_en);
    write("ip_lcd", ptr->ip_lcd);
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
