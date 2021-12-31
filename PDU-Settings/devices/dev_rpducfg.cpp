#include "dev_rpducfg.h"

Dev_RpduCfg::Dev_RpduCfg(QObject *parent) : Dev_Object(parent)
{
    mDev = mPacket->getAts();
    initCfg();
}

Dev_RpduCfg *Dev_RpduCfg::bulid(QObject *parent)
{
    static Dev_RpduCfg* sington = nullptr;
    if(sington == nullptr)
        sington = new Dev_RpduCfg(parent);
    return sington;
}

void Dev_RpduCfg::initData()
{
    sDevType *ptr = &(mDev->dt);
    ptr->default_ip_prefix = read("default_ip_prefix", 0).toInt();
    ptr->default_ip_addr = read("default_ip_addr", 0).toInt();
    ptr->default_user = read("default_user", 0).toInt();
    ptr->default_password = read("default_password", 0).toInt();
    ptr->default_backendAddress = read("default_backendAddress", 0).toInt();
    ptr->default_macControlID = read("default_macControlID", 0).toInt();
    ptr->default_setMacControlID = read("default_setMacControlID", 0).toInt();

    ptr->ip_prefix = read("ip_prefix", "http://").toString();
    ptr->ip_addr = read("ip_addr", "192.168.1.163").toString();
    ptr->user = read("user", "admin").toString();
    ptr->password = read("password", "admin").toString();
    ptr->backendAddress = read("backendAddress", "./debug.html").toString();
    ptr->macControlID = read("macControlID", "mac").toString();
    ptr->setMacControlID = read("setMacControlID", "savedebug()").toString();
}

void Dev_RpduCfg::writeData()
{
    sDevType *ptr = &(mDev->dt);
    write("default_ip_prefix", ptr->default_ip_prefix);
    write("default_ip_addr", ptr->default_ip_addr);
    write("default_user", ptr->default_user);
    write("default_password", ptr->default_password);
    write("default_backendAddress", ptr->default_backendAddress);
    write("default_macControlID", ptr->default_macControlID);
    write("default_setMacControlID", ptr->default_setMacControlID);

    write("ip_prefix", ptr->ip_prefix);
    write("ip_addr", ptr->ip_addr);
    write("user", ptr->user);
    write("password", ptr->password);
    write("backendAddress", ptr->backendAddress);
    write("macControlID", ptr->macControlID);
    write("setMacControlID", ptr->setMacControlID);
}

void Dev_RpduCfg::initCfg()
{
    initData();
}

void Dev_RpduCfg::save()
{
    writeData();
}
