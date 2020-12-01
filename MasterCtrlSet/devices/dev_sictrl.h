#ifndef DEV_SICTRL_H
#define DEV_SICTRL_H

#include "dev_sicfg.h"

class Dev_SiCtrl : public Dev_Object
{
    Q_OBJECT
    explicit Dev_SiCtrl(QObject *parent = nullptr);
public:
    static Dev_SiCtrl *bulid(QObject *parent = nullptr);

    bool factorySet();
    bool setModel();

    bool setCurTh(int i);
    bool setVolTh(int i);

protected:
    void save(){}
    bool sentRtuCmd(ushort reg, ushort value);
};

#endif // DEV_SICTRL_H
