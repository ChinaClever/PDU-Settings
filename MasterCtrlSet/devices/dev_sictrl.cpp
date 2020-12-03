/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "dev_sictrl.h"

Dev_SiCtrl::Dev_SiCtrl(QObject *parent) : Dev_Object(parent)
{
    mDev = mPacket->getSi();
    mDt = &(mDev->dt);
}

Dev_SiCtrl *Dev_SiCtrl::bulid(QObject *parent)
{
    static Dev_SiCtrl* sington = nullptr;
    if(sington == nullptr)
        sington = new Dev_SiCtrl(parent);
    return sington;
}

bool Dev_SiCtrl::setCurTh(int i)
{
    bool ret = true;
    ushort reg = 0x1008 + 2*i;
    if(DC == mDt->ac) reg = 0x1016;

    sUnitCfg *unit = &(mDev->cfg.cur);
    ushort value = unit->max * 10;
    if((mDt->lines == 2) && i) value = (value/10 +1)/2 * 10; // 解决单项二路阈值问题
    if(mDev->data.cur.max[i] != value) {
        ret = sentRtuCmd(reg++, value); if(!ret) return ret;
    } else reg++;

    value = unit->min * 10;
    if(mDev->data.cur.min[i] != value) {
        ret = sentRtuCmd(reg++, value); if(!ret) return ret;
    } else reg++;

    return ret;
}

bool Dev_SiCtrl::setVolTh(int i)
{
    ushort reg = 0x1002 + 2*i;
    if(DC == mDt->ac) reg = 0x1014;

    return writeReg(reg, i, mDev->data.vol, mDev->cfg.vol);
}

bool Dev_SiCtrl::setTem()
{
    return writeReg(0x100E, 0, mDev->data.tem, mDev->cfg.tem);
}

bool Dev_SiCtrl::setHum()
{
    return writeReg(0x1010, 0, mDev->data.hum, mDev->cfg.hum);
}

bool Dev_SiCtrl::writeReg(ushort reg, int i, sDataUnit &it, sUnitCfg &unit, int r)
{
    bool ret = true;

    ushort value = unit.max * r;
    if(it.max[i] != value) {
        ret = sentRtuCmd(reg++, value); if(!ret) return ret;
    } else reg++;

    value = unit.min * r;;
    if(it.min[i] != value) {
        ret = sentRtuCmd(reg++, value); if(!ret) return ret;
    } else reg++;

    return ret;
}

// 表示行业标准 Modbus RTU 模式
bool Dev_SiCtrl::setModel()
{
    sRtuSetItem it;
    it.addr = mItem->addr;
    it.fn = 0x06;
    it.reg = 0x1019;
    it.data = 1;

    return mModbus->write(it);
}

bool Dev_SiCtrl::factorySet()
{
    bool ret = sentRtuCmd(0x1013, 0xFF00); // 清除电能
    if(ret) {
        if(mDt->standar) // 切换成行业标准
            ret = setModel();
    }

    return ret;
}

bool Dev_SiCtrl::sentRtuCmd(ushort reg, ushort value)
{
    sRtuSetItem it;
    it.addr = mItem->addr;
    it.fn = 0x10;
    it.reg = reg;
    it.data = value;

    return mModbus->write(it);
}
