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
    QString ipstr = "192.168.1.163";
    if(mDt && !mDt->ip_addr.isEmpty()) ipstr = mDt->ip_addr;
    bool ret = cm_pingNet(ipstr);
    if(ret) str += tr("正常");
    else{
      str += tr("错误");
      mPro->result = Test_Fail;
    }

    return mLogs->updatePro(str, ret);
}



bool Test_CoreThread::startProcess()
{
    QString exe = "pyweb_ctrlset_";
    switch (mItem->modeId) {
    case IP_PDU:  exe += "ip"; break;
    case MPDU:  exe += "mpdu"; break;
    case ZPDU:  exe += "zpdu"; break;
    case ATS:  exe += "ats"; break;
    case RPDU:  exe += "rpdu"; break;
    case IP_BUSBAR:  exe += "ipbusbar"; break;
    case MPDU_CUSTOMIZE:  exe += "mpducustomize"; break;
    case IP_PDU_CUSTOMIZE:  exe += "ippducustomize"; break;
    case ZPDUHW:  exe += "zpduhw"; break;
    case ZPDUSTD: exe += "zpdustd"; break;
    }

    exe += ".exe";
    qDebug()<<exe<<endl;
    mRead->mac = true;
    bool ret = checkNet();
    if(ret){
        try {
            mProcess->close();
//            if(mItem->modeId == MPDU) mProcess->startDetached(exe);
//            else
                mProcess->start(exe);
            mLogs->updatePro(tr("网页设置功能启动"));
            ret = mProcess->waitForFinished(420*1000);

//            if(mItem->modeId == MPDU) {sleep(92); ret = true;}
            mLogs->updatePro(tr("网页设置功能正常退出"), ret , 2);
        } catch (...) {
            ret = mLogs->updatePro(tr("网页设置功能异常退出"), false, 1);
            updateMacAddr(1);
        }
    }

    return ret;
}

void Test_CoreThread::updateMacAddr(int step)
{
    if(mItem->mac.size() > 5) {
        mLogs->writeMac(mItem->mac);
        MacAddr *mac = MacAddr::bulid();
        mItem->mac = mac->macAdd(mItem->mac, step);
        Cfg::bulid()->write("mac", mItem->mac, "Mac");
    }
}


void Test_CoreThread::workResult(bool res)
{
    if(mItem->enSn)mSn->snEnter();
    QString str = tr("最终结果");
    if(mPro->result != Test_Fail) {
        res = true;
        str += tr("通过");
    } else {
        res = false;
        str += tr("失败");
    }

    mLogs->updatePro(str, res);
    mLogs->saveLogs();
    mPro->step = Test_Over;
}

void Test_CoreThread::workDown()
{
    bool ret = true;
    mItem->sn.clear();
    mLogs->updatePro(tr("自动设置已启动"));
    if(mItem->modeId) {
        updateMacAddr(1);
        ret = startProcess();
        //if(!mRead->mac) updateMacAddr(-1);
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
