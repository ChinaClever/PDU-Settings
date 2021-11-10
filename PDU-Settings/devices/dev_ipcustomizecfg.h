#ifndef DEV_IPCUSTOMIZECFG_H
#define DEV_IPCUSTOMIZECFG_H
#include "dev_object.h"

class Dev_IpCustomizeCfg : public Dev_Object
{
    Q_OBJECT
    Dev_IpCustomizeCfg(QObject *parent = nullptr);
public:
    static Dev_IpCustomizeCfg *bulid(QObject *parent = nullptr);
    void save();

protected:
    QString cfgGroup(){return "ipCustomizeCfg";}

    void initType();
    void initData();
    void initCfg();

    void writeType();
    void writeData();
};

#endif // DEV_IPCUSTOMIZECFG_H
