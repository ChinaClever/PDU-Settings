/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "dev_object.h"

Dev_Object::Dev_Object(QObject *parent) : QThread(parent)
{
    mPacket = sDataPacket::bulid();
    mItem = Cfg::bulid()->item;
    mPro = mPacket->getPro();

    mDev = nullptr;
    mDt = nullptr;
}


void Dev_Object::initUnit(const QString& prefix, sUnit &unit)
{
    unit.en = read(prefix+"_en", 0).toBool();
    unit.min = read(prefix+"_min", 0).toFloat();
    unit.max = read(prefix+"_max", 10).toFloat();

    unit.crMin = read(prefix+"_crMin", 0).toFloat();
    unit.crMax = read(prefix+"_crMax", 10).toFloat();
}

void Dev_Object::writeUnit(const QString& prefix, sUnit &unit)
{
    write(prefix+"_en", unit.en);
    write(prefix+"_min", QString::number(unit.min));
    write(prefix+"_max", QString::number(unit.max));

    write(prefix+"_crMin", QString::number(unit.crMin));
    write(prefix+"_crMax", QString::number(unit.crMax));
}


void Dev_Object::write(const QString &key, const QVariant& v)
{
    Cfg::bulid()->write(key, v, cfgGroup());
}

QVariant Dev_Object::read(const QString &key, const QVariant &v)
{
    return Cfg::bulid()->read(key, v, cfgGroup());
}
