/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "test_corethread.h"

Test_CoreThread::Test_CoreThread(QObject *parent) : Test_Object(parent)
{

}

void Test_CoreThread::initFunSlot()
{
    mLogs = Test_Logs::bulid(this);
    mRead = Test_NetWork::bulid(this);
    mCtrl = Test_SiThread::bulid(this);
    mSn = Sn_SerialNum::bulid(this);
}

bool Test_CoreThread::checkNet()
{
    QString str = tr("检测设备网络");
    bool ret = cm_pingNet("192.168.1.168");
    if(ret) {
        str += tr("正常");
    } else {
        str += tr("错误");
    }

    return mLogs->updatePro(str, ret);
}

bool Test_CoreThread::startProcess()
{
    int sec = 45;
    QString exe = "ip_web.exe";
    if(MPDU == mItem->modeId) {
        exe = "mpdu_web.exe";
    }

    QProcess process(this);
    process.start(exe);
    bool ret = checkNet();
    if(ret) {
        ret = process.waitForFinished(sec*1000);
    }
    process.close();
    msleep(100);

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
    bool ret = true;
    // bool ret = mSn->snEnter();
    QString str = tr("最终结果");
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
        ret = mCtrl->setDev();
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
