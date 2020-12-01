#include "test_network.h"

Test_NetWork::Test_NetWork(QObject *parent) : Test_Object(parent)
{

}

Test_NetWork *Test_NetWork::bulid(QObject *parent)
{
    static Test_NetWork* sington = nullptr;
    if(sington == nullptr)
        sington = new Test_NetWork(parent);
    return sington;
}

void Test_NetWork::initFunSlot()
{
    mSn = Sn_SerialNum::bulid(this);
    mLogs = Test_Logs::bulid(this);
    mUdp = new UdpRecvSocket(this);
    mUdp->initSocket(10086);
    this->start();
}

bool Test_NetWork::updatePro(const QString &str, bool pass)
{
    mLogs->updatePro(str, pass);
    if(str == "设置结束") {
        mSn->snEnter();
        mLogs->saveLogs();
        mPro->step = Test_Over;
    }

    return pass;
}

void Test_NetWork::workDown()
{
    UdpBaseData *res = mUdp->getData();
    if(res) {
        QStringList list = QString(res->datagram).split("; ");
        bool pass = list.first().toInt();
        QString str = list.last();
        updatePro(str, pass);
        delete res;
    } else {
        msleep(1);
    }
}

void Test_NetWork::run()
{
    isRun = true;
    while (isRun) {
        workDown();
    }
}
