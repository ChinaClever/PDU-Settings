#ifndef TEST_OBJECT_H
#define TEST_OBJECT_H

#include "sn_serialnum.h"
#include "dev_atscfg.h"
#include "dev_zpducfg.h"
#include "dev_rpducfg.h"
#include "dev_ipbusbarcfg.h"
#include "dev_mpducustomizecfg.h"
#include "dev_ipcustomizecfg.h"

class Test_Object : public QThread
{
    Q_OBJECT
public:
    explicit Test_Object(QObject *parent = nullptr);
    ~Test_Object();

protected:
    void updateDev();

protected slots:
    virtual void initFunSlot(){}

protected:
    bool isRun;
    sDevType *mDt;
    sDevData *mDev;
    sCfgItem *mItem;
    sProgress *mPro;
    Dev_Object *mObj;
    sDataPacket *mPacket;
};

#endif // TEST_OBJECT_H
