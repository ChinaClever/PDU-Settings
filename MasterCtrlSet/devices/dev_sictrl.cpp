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

    sUnit *unit = &(mDev->data.cur);
    ushort value = unit->max;
    if((mDt->lines == 2) && i) value = (value/10 +1)/2 * 10; // 解决单项二路阈值问题
    ret = sentRtuCmd(reg++, value); if(!ret) return ret;

    value = unit->min;
    ret = sentRtuCmd(reg++, value); if(!ret) return ret;

    return ret;
}

bool Dev_SiCtrl::setVolTh(int i)
{
    ushort reg = 0x1002 + 2*i;
    if(DC == mDt->ac) reg = 0x1014;

    return writeReg(reg, mDev->data.vol);;
}

bool Dev_SiCtrl::setTem()
{
    return writeReg(0x100E, mDev->data.tem);
}

bool Dev_SiCtrl::setHum()
{
    return writeReg(0x1010, mDev->data.hum);
}

bool Dev_SiCtrl::writeReg(ushort reg, sUnit &unit, int r)
{
    bool ret = true;

    ushort value = unit.max * r;
    ret = sentRtuCmd(reg++, value); if(!ret) return ret;

    value = unit.min *r;
    ret = sentRtuCmd(reg++, value); if(!ret) return ret;

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
    return sentRtuCmd(0x1013, 0xFF00); // 清除电能
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
