/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
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
    ptr->ac = read("si_ac", 1).toInt();
    ptr->lines = read("si_lines", 1).toInt();
    ptr->series = read("si_series", 0).toInt();
    ptr->standar = read("si_standar", 0).toInt();
}

void Dev_SiCfg::writeType()
{
    sDevType *ptr = mDt;
    write("si_ac", ptr->ac);
    write("si_lines", ptr->lines);
    write("si_series", ptr->series);
    write("si_standar", ptr->standar);
}

void Dev_SiCfg::initData()
{
    sObjCfg *ptr = &(mDev->cfg);
    initUnit("vol", ptr->vol);
    initUnit("cur", ptr->cur);

    initUnit("tem", ptr->tem);
    initUnit("hum", ptr->hum);
}

void Dev_SiCfg::writeData()
{
    sObjCfg *ptr = &(mDev->cfg);
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
