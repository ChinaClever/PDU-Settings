#ifndef DEV_MPDUCUSTOMIZECFG_H
#define DEV_MPDUCUSTOMIZECFG_H

#include "dev_object.h"

class Dev_MpduCustomizeCfg : public Dev_Object
{
    Q_OBJECT
    explicit Dev_MpduCustomizeCfg(QObject *parent = nullptr);
public:
    static Dev_MpduCustomizeCfg *bulid(QObject *parent = nullptr);

    void save();

protected:
    QString cfgGroup(){return "mpduCustomizeCfg";}

    void initType();
    void initData();
    void initCfg();

    void writeType();
    void writeData();
};

#endif // DEV_MPDUCUSTOMIZECFG_H
