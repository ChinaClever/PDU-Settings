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


void Dev_Object::initUnit(const QString& prefix, sUnit &unit, int f)
{
    unit.min = read(prefix+"_min", 0).toFloat();
    unit.max = read(prefix+"_max", 10).toFloat();

    switch (f) {
    case 2:
        unit.en = read(prefix+"_en", 0).toInt();
        unit.id = read(prefix+"_id", 0).toInt();
    case 1:
        unit.crMin = read(prefix+"_crMin", 0).toFloat();
        unit.crMax = read(prefix+"_crMax", 10).toFloat();
        break;
    }
}

void Dev_Object::writeUnit(const QString& prefix, sUnit &unit, int f)
{
    write(prefix+"_min", QString::number(unit.min));
    write(prefix+"_max", QString::number(unit.max));

    switch (f) {
    case 2:
        write(prefix+"_en", unit.en);
        write(prefix+"_id", unit.id);
    case 1:
        write(prefix+"_crMin", QString::number(unit.crMin));
        write(prefix+"_crMax", QString::number(unit.crMax));
        break;
    }
}


void Dev_Object::write(const QString &key, const QVariant& v)
{
    Cfg::bulid()->write(key, v, cfgGroup());
}

QVariant Dev_Object::read(const QString &key, const QVariant &v)
{
    return Cfg::bulid()->read(key, v, cfgGroup());
}
