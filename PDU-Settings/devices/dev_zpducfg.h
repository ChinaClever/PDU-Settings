#ifndef DEV_ZPDUCFG_H
#define DEV_ZPDUCFG_H
#include "dev_object.h"

class Dev_ZpduCfg : public Dev_Object
{
    Q_OBJECT
    explicit Dev_ZpduCfg(QObject *parent = nullptr);
public:
    static Dev_ZpduCfg *bulid(QObject *parent = nullptr);

    void save();

protected:
    QString cfgGroup(){return "zpduCfg";}

    void initType();
    void initData();
    void initCfg();

    void writeType();
    void writeData();
};

#endif // DEV_ZPDUCFG_H
