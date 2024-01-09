#ifndef TEST_CORETHREAD_H
#define TEST_CORETHREAD_H

#include "test_sithread.h"

class Test_CoreThread : public Test_Object
{
    Q_OBJECT
public:
    explicit Test_CoreThread(QObject *parent = nullptr);

protected:
    void run();
    void workDown();
    bool checkNet();
    bool startProcess();
    void updateMacAddr(int step);
    void workResult(bool res);

protected slots:
    void initFunSlot();
    void getVersionSlot(QString str);
private:
    Test_Logs *mLogs;
    Sn_SerialNum *mSn;
    Test_SiThread *mCtrl;
    Test_NetWork *mRead;
    QProcess *mProcess;
    QString mVersion;
};

#endif // TEST_CORETHREAD_H
