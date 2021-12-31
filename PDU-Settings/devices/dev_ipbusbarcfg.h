#ifndef DEV_IPBUSBARCFG_H
#define DEV_IPBUSBARCFG_H
#include "dev_object.h"

class Dev_IpBusbarCfg : public Dev_Object
{
    Q_OBJECT
    explicit Dev_IpBusbarCfg(QObject *parent = nullptr);
public:
    static Dev_IpBusbarCfg *bulid(QObject *parent = nullptr);

    void save();

protected:
    QString cfgGroup(){return "ipbusbarCfg";}

    void initType();
    void initData();
    void initCfg();

    void writeType();
    void writeData();
};

#endif // DEV_IPBUSBARCFG_H
