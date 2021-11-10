#include "dev_ipcustomizecfg.h"

Dev_IpCustomizeCfg::Dev_IpCustomizeCfg(QObject *parent) : Dev_Object(parent)
{
    mDev = mPacket->getIpPDUCustomize();
    initCfg();
}

Dev_IpCustomizeCfg *Dev_IpCustomizeCfg::bulid(QObject *parent)
{
    static Dev_IpCustomizeCfg* sington = nullptr;
    if(sington == nullptr)
        sington = new Dev_IpCustomizeCfg(parent);
    return sington;
}

void Dev_IpCustomizeCfg::initData()
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
    ptr->backendAddress = read("backendAddress", "./correct.html").toString();
    ptr->macControlID = read("macControlID", "mac1").toString();
    ptr->setMacControlID = read("setMacControlID", "Button3").toString();
}

void Dev_IpCustomizeCfg::writeData()
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

void Dev_IpCustomizeCfg::initCfg()
{
    initData();
}

void Dev_IpCustomizeCfg::save()
{
    writeData();
}
