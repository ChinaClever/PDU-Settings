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
    mProcess = new QProcess(this);
}

bool Test_CoreThread::checkNet()
{
    QString str = tr("检测设备网络");
    bool ret = cm_pingNet("192.168.1.163");
    if(ret) str += tr("正常");
    else str += tr("错误");

    return mLogs->updatePro(str, ret);
}

bool Test_CoreThread::startProcess()
{
    QString exe = "pyweb_ctrlset_";
    if(MPDU == mItem->modeId) {
        exe += "mpdu.run";
    } else exe += "ip.run";

    mProcess->start(exe);
    bool ret = checkNet();
    if(ret) {
        ret = mProcess->waitForFinished(100*1000);
    }
    mProcess->close();

    return ret;
}

void Test_CoreThread::updateMacAddr()
{
    if(mItem->mac.size() > 5) {
        mLogs->writeMac(mItem->mac);
        MacAddr *mac = MacAddr::bulid();
        mItem->mac = mac->macAdd(mItem->mac);
    }
}


void Test_CoreThread::workResult(bool res)
{
    if(res) res = mSn->snEnter();
    QString str = tr("最终结果");
    if(res) str += tr("通过");
    else str += tr("失败");

    mLogs->updatePro(str, res, 0);
    if(res) mLogs->saveLogs();
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
