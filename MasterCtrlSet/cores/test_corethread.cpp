#include "test_corethread.h"

Test_CoreThread::Test_CoreThread(QObject *parent) : Test_Object(parent)
{

}

void Test_CoreThread::initFunSlot()
{
    mLogs = Test_Logs::bulid(this);
    mRead = Test_NetWork::bulid(this);
    mCtrl = Test_SiCtrl::bulid(this);
    mSn = Sn_SerialNum::bulid(this);
}

bool Test_CoreThread::checkNet()
{
    QString str = tr("检测设备网络");
    bool ret = cm_pingNet("192.168.1.163");
    if(ret) {
        str += tr("正常");
    } else {
        str += tr("错误");
    }

    return mLogs->updatePro(str, ret);
}

bool Test_CoreThread::startProcess()
{
    int sec = 15;
    QString exe = "ip_web.exe";
    if(MPDU == mItem->modeId) {
        exe = "mpdu_web.exe";
    }

    QProcess process(this);
    process.start(exe);
    bool ret = checkNet();
    if(ret) {
        process.waitForFinished(sec*1000);
    }
    process.close();

    return ret;
}

void Test_CoreThread::updateMacAddr()
{
    if(mDt->mac.size() > 5) {
        mLogs->writeMac(mDt->mac);
        MacAddr *mac = MacAddr::bulid();
        mDt->mac = mac->macAdd(mDt->mac);
        mObj->setMacAddr();
    }
}


void Test_CoreThread::workResult(bool res)
{
    QString str = tr("最终结果");
    bool ret = mSn->snEnter();
    if(res&&ret) {
        str += tr("通过");
    } else {
        str += tr("失败");
        ret = false;
    }
    mLogs->updatePro(str, ret);

    mLogs->saveLogs();
    mPro->step = Test_Over;
}

void Test_CoreThread::workDown()
{
    bool ret = true;
    mLogs->updatePro(tr("自动设置已启动"));
    if(mItem->modeId) {
        ret = startProcess();
        if(ret) updateMacAddr();
    } else {
        ret = mCtrl->setAlarm();
    }

    workResult(ret);
}

void Test_CoreThread::run()
{
    if(isRun) return;
    isRun = true;

    updateDev();
    workDown();
    isRun = false;
}
