#include "test_sictrl.h"

Test_SiCtrl::Test_SiCtrl(QObject *parent) : Test_Object(parent)
{

}

void Test_SiCtrl::initFunSlot()
{
    mCtrl = Dev_SiCtrl::bulid(this);
    mLogs = Test_NetWork::bulid(this);
    mDev = Dev_SiCfg::bulid(this)->getDev();
    mDt = &(mDev->dt);
}

Test_SiCtrl *Test_SiCtrl::bulid(QObject *parent)
{
    static Test_SiCtrl* sington = nullptr;
    if(sington == nullptr)
        sington = new Test_SiCtrl(parent);
    return sington;
}


bool Test_SiCtrl::curAlarmWrite(int i)
{
    QString str = tr("电流报警阈值 L%1 写入").arg(i+1);
    bool ret = mCtrl->setCurTh(i);
    if(ret) str += tr("正常");
    else str += tr("错误");

    return mLogs->updatePro(str, ret);
}

bool Test_SiCtrl::volAlarmWrite(int i)
{
    QString str = tr("电压报警阈值 L%1 写入").arg(i+1);
    bool ret = mCtrl->setVolTh(i);
    if(ret) str += tr("正常");
    else str += tr("错误");

    return mLogs->updatePro(str, ret);
}

bool Test_SiCtrl::writeAlarmTh()
{
    bool ret = true;
    for(int i=0; i<mDt->lines; ++i) {
        ret = curAlarmWrite(i); if(!ret) break;
        ret = volAlarmWrite(i); if(!ret) break;
    }

    return ret;
}

