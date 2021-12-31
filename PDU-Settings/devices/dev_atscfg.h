#ifndef DEV_ATSCFG_H
#define DEV_ATSCFG_H
#include "dev_object.h"

class Dev_AtsCfg : public Dev_Object
{
    Q_OBJECT
    explicit Dev_AtsCfg(QObject *parent = nullptr);
public:
    static Dev_AtsCfg *bulid(QObject *parent = nullptr);

    void save();

protected:
    QString cfgGroup(){return "atsCfg";}

    void initType();
    void initData();
    void initCfg();

    void writeType();
    void writeData();
};

#endif // DEV_ATSCFG_H
