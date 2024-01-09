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
    connect(mRead , SIGNAL(sendVersionSig(QString)) , this , SLOT(getVersionSlot(QString)));
}

void Test_CoreThread::getVersionSlot(QString str)
{
    if( str.size() != 0 ){
        QString str1 = str.right(11);
        char targetChar = '.'; // 目标字符
        int index = str1.indexOf(targetChar); // 查找目标字符的索引
        if (index != -1){
            this->mVersion = str1.mid(0, index).trimmed(); // 截取从开头到目标字符之间的子字符串（包括目标字符）
            mPro->softwareVersion = this->mVersion;
        }
    }
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
    case ZPDUNETSAFE: exe += "zpdunetsafe"; break;
    }

    exe += ".exe";
    qDebug()<<exe<<endl;
    mRead->mac = true;
    bool ret = checkNet();
    if(ret){
        try {
            mProcess->close();
            mProcess->start(exe);
            mLogs->updatePro(tr("网页设置功能启动"));
            ret = mProcess->waitForFinished(420*1000);
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
    mPro = sDataPacket::bulid()->getPro();
    mLogs->writeMac(mItem->mac);
    MacAddr *mac = MacAddr::bulid();
    // mItem->mac = mac->macAdd(mItem->mac, step);
    QString url = "mac/test?work_order=%1&serial_id=%2";
    sleep(1);
    url = url.arg(mPro->clientName).arg(mPro->productSN);
    // sleep(1);
    QString temp = Json_Pack::bulid()->http_get(url,"192.168.1.12");
    QJsonDocument jsonDoc = QJsonDocument::fromJson(temp.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();
    mItem->mac = jsonObj["mac_address"].toString();
    mPro->macAddress = mItem->mac;

    Cfg::bulid()->write("mac", mItem->mac, "Mac");
}


void Test_CoreThread::workResult(bool res)
{
    if(mItem->enSn)mSn->snEnter();
    QString str = tr("最终结果");
    if(mPro->result != Test_Fail) {
        res = true;
        str += tr("通过");
        mPro->uploadPassResult = 1;
    } else {
        res = false;
        str += tr("失败");
        mPro->uploadPassResult = 0;
    }

    mLogs->updatePro(str, res);
    mLogs->saveLogs();

    sleep(2);
    Json_Pack::bulid()->http_post("debugdata/add","192.168.1.12");//全流程才发送记录(http)
    //全流程才发送记录
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
