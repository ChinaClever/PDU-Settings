/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "sn_serialnum.h"

Sn_SerialNum::Sn_SerialNum(QObject *parent) : Sn_Object(parent)
{
    mTypeId = Sn_DevId::bulid(this);
}

Sn_SerialNum *Sn_SerialNum::bulid(QObject *parent)
{
    Sn_SerialNum* sington = nullptr;
    if(sington == nullptr)
        sington = new Sn_SerialNum(parent);
    return sington;
}

void Sn_SerialNum::initReadCmd(sRtuItem &item)
{
    item.addr = mItem->addr;
    item.fn = 0x03;
    item.reg = 0xA003;
    item.num = 4;
}

bool Sn_SerialNum::checkSn(uchar *sn, int len)
{
    bool ret = false;
    if((len == 8) && (sn[0] == 0)){
        uchar exor = mModbus->xorNum(sn, len-1);//暂时注释下面的异或和校验不对
        if(exor == sn[len-1]) {
            ret = true;
        }
    } else {
        qDebug() << "SN check err" << len << sn[0];
    }
    return ret;
}

void Sn_SerialNum::initDevType(sSnItem &it)
{
    uint id = mItem->devId;
    for(int i=3; i>=0; --i) {
        it.devType[i] = (0xFF) & (id >> ((3-i)*8));
    }
    it.sn.clear();
}

bool Sn_SerialNum::analySn(uchar *sn, int len, sSnItem &it)
{
    uchar *ptr = sn;
    bool ret = checkSn(sn, len);
    if(ret) {
        for(int i=0; i<4; ++i) {
            it.date[i] = *ptr++;
        }
        it.num = (*ptr++) << 8;
        it.num += *ptr++;
        it.pc = *ptr++;
        it.exor = *ptr++;
    }

    return ret;
}

void Sn_SerialNum::toSnStr(sSnItem &it)
{
    QString cmd;
    for(int i=0; i<11; ++i) {cmd += "%" + QString::number(i+1); if(i%4 == 0) cmd += " ";}
    QString sn  = QString(cmd)
            .arg(it.devType[0], 2, 16, QLatin1Char('0'))
            .arg(it.devType[1], 2, 16, QLatin1Char('0'))
            .arg(it.devType[2], 2, 16, QLatin1Char('0'))
            .arg(it.devType[3], 2, 16, QLatin1Char('0'))
            .arg(it.date[0], 2, 10, QLatin1Char('0'))
            .arg(it.date[1], 2, 10, QLatin1Char('0'))
            .arg(it.date[2], 2, 10, QLatin1Char('0'))
            .arg(it.date[3], 2, 10, QLatin1Char('0'))
            .arg(it.num, 4, 10, QLatin1Char('0'))
            .arg(it.pc, 2, 16, QLatin1Char('0'))
            .arg(it.exor, 2, 16, QLatin1Char('0'));

    it.sn = sn.toUpper();
}

bool Sn_SerialNum::readSn(sSnItem &itSn)
{
    sRtuItem itRtu;
    bool ret = false;
    uchar buf[32] = {0};
    QString str = tr("序列号读取成功");

    initDevType(itSn);
    initReadCmd(itRtu);
    int len = mModbus->read(itRtu, buf);
    if(8 != len) len = mModbus->read(itRtu, buf);
    if(len == 8) {
        ret = analySn(buf, len, itSn);
        if(ret) toSnStr(itSn);
    } else {
        str = tr("读序列号未返数据长度错误 %1").arg(len);
    }

    return mPacket->updatePro(str, ret);
}


void Sn_SerialNum::initWriteCmd(sRtuSetItems &item, uchar *data, int len)
{
    item.addr = mItem->addr;
    item.fn = 0x10;
    item.reg = 0xA003;
    item.num = 4;
    item.len = len;

    for(int i=0; i<len; ++i) {
        item.data[i] = data[i];
    }
}


void Sn_SerialNum::createSn(sSnItem &it)
{
    int k = 0;
    QDate date = QDate::currentDate();
    it.date[k++] = 0;
    it.date[k++] = date.year() % 100;
    it.date[k++] = date.month();
    it.date[k++] = date.day();

    it.num = ++(mItem->currentNum);
    it.pc = mItem->pcNum;
}


int Sn_SerialNum::toSnData(sSnItem &it, uchar *data)
{
    int k = 0;
    for(int i=0; i<4; ++i) {
        data[k++] = it.date[i];
    }

    data[k++] = it.num / 256;
    data[k++] = it.num % 256;
    data[k++] = it.pc;

    uchar exor = mModbus->xorNum(data, k);
    data[k++] = it.exor = exor;
    toSnStr(it);

    return k;
}

bool Sn_SerialNum::writeSn(sSnItem &itSn)
{
    createSn(itSn);
    uchar buf[32] = {0};
    int len = toSnData(itSn, buf);

    sRtuSetItems itRtu;
    initWriteCmd(itRtu, buf, len);
    mPacket->delay(1);

    return mModbus->writes(itRtu);
}

void Sn_SerialNum::writeStatus(bool ret)
{
    QString str = tr("已写入序列号");
    if(ret) {
        Cfg::bulid()->setCurrentNum();
    } else {
        str = tr("序列号写入失败");
        mItem->currentNum -= 1;
    }

    mPacket->updatePro(str, ret);
}

bool Sn_SerialNum::snEnter()
{
    if((mDt->devType == SI_PDU) &&(mItem->ledSi)) {
        mItem->sn.clear(); return true;
    }

    bool ret = mTypeId->readDevType();
    if(ret) {
        ret = readSn(mSnItem);
        if(!ret) {
            ret = writeSn(mSnItem);
            writeStatus(ret);
        }
    }

    mItem->sn = mSnItem.sn;
    mSnItem.sn.clear();

    return ret;
}

