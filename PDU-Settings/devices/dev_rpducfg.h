#ifndef DEV_RPDUCFG_H
#define DEV_RPDUCFG_H
#include "dev_object.h"

class Dev_RpduCfg : public Dev_Object
{
    Q_OBJECT
    explicit Dev_RpduCfg(QObject *parent = nullptr);
public:
    static Dev_RpduCfg *bulid(QObject *parent = nullptr);

    void save();

protected:
    QString cfgGroup(){return "rpduCfg";}

    void initType();
    void initData();
    void initCfg();

    void writeType();
    void writeData();
};

#endif // DEV_RPDUCFG_H
