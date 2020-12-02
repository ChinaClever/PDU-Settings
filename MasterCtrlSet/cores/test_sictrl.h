#ifndef TEST_SICTRL_H
#define TEST_SICTRL_H

#include "test_network.h"

class Test_SiCtrl : public Test_Object
{
    Q_OBJECT
    explicit Test_SiCtrl(QObject *parent = nullptr);
public:
    static Test_SiCtrl *bulid(QObject *parent = nullptr);

    bool setAlarm();

protected:
    bool volAlarmWrite(int i);
    bool curAlarmWrite(int i);
    bool envAlarmWrite();
    bool writeAlarmTh();

protected slots:
    void initFunSlot();

private:
    Dev_SiCtrl *mCtrl;
    Test_Logs *mLogs;
};

#endif // TEST_SICTRL_H
