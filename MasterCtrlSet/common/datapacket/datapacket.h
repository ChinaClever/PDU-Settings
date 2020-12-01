#ifndef DATAPACKET_H
#define DATAPACKET_H
#include <QtCore>
#include <QColor>

#define OpSize  6

/**
 * 数据单元：包括当前值，阈值，临界值，告警状态等
 */
struct sUnit
{
    uchar en;
    uchar id;
    float min; // 最小值
    float max; // 最大值

    float crMin; // 最小值
    float crMax; // 最大值
};



/**
 * 数据对象：包括电流，电压，功率，电能，开关状态，插接位名称
 */
struct sObjData
{
    sUnit vol; // 电压
    sUnit cur; // 电流
    sUnit output; // 电流
    sUnit opCur[OpSize]; // 输出位电流

    sUnit tem; // 温度
    sUnit hum; // 湿度
};

struct sDevType
{
    uchar devType; // 1 ZPDU执行板类型  2 MPDU执行板类型   3 RPDU执行板类型
    // 4 SI-PDU  5 IP-PDU  6 BM-PDU

    uchar ac;
    uchar series; // 1 A系列  2 B系列  3 C系列  4 D系列1
    uchar lines;
    uchar loops;
    uchar outputs;
    uchar breaker;
    uchar language;
    uchar modbus;
    uchar standar;
    uchar versions;
    uchar logs;

    QString mac;
};



/**
 * 设备数据结构体：
 */
struct sDevData
{
    sDevType dt; //设备类型
    sObjData data; // MPDU配置数据
};


enum {
    Test_Fun, // 功能
    Test_Start, // 开始
    Test_vert, // 验证
    Test_Over, // 终止
    Test_End, // 完成

    Test_Info=0,
    Test_Pass=1,
    Test_Fail=2,
};

struct sProgress
{
    sProgress() {step=0;}

    uchar step; // 步骤
    QString time;
    QList<bool> pass, itPass;
    QStringList status, item;

    uchar result;    // 最终结果
    QTime startTime;
};


/**
 * 数据包
 */
class sDataPacket
{
    sDataPacket();
public:
    static sDataPacket *bulid();

    void init();
    sDevData *getSi() {return si;}
    sDevData *getIp() {return ip;}
    sDevData *getMpdu() {return mpdu;}
    sDevData *getZpdu() {return zpdu;}
    sProgress *getPro() {return pro;}

    bool updatePro(const QString &str, bool pass=true, int sec=1);
    bool delay(int s=1);
private:
    sDevData *si;
    sDevData *ip;
    sDevData *mpdu;
    sDevData *zpdu;
    sProgress *pro;
};



#endif // DATAPACKET_H
