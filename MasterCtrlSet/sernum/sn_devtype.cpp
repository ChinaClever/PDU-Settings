/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "sn_devtype.h"
#include "common/json/json_build.h"
#include "common/json/json_recv.h"

Sn_DevType::Sn_DevType()
{
    QJsonObject json;
    Json_Build::bulid()->getJson(json);
    Json_Recv::bulid()->recv("PDU-CalibrateTool");
}

Sn_DevType * Sn_DevType::bulid()
{
    static  Sn_DevType* sington = nullptr;
    if(sington == nullptr)
        sington = new  Sn_DevType();
    return sington;
}

QString Sn_DevType::getDevStr(uint id)
{
    QString dev_type = Json_Recv::bulid()->getDevTypeByID(id);
    return dev_type;
}


bool Sn_DevType::analysDevType(uint id)
{
    bool ret = true;
    QString str = getDevStr(id);
    if(str.size()) {
        Cfg::bulid()->item->dev_type = str;
    } else {
        ret = false;
    }

    return ret;
}

