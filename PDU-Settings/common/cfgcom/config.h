#ifndef CONFIGBASH
#define CONFIGBASH
#include "cfgcom.h"
#include "serialstatuswid.h"

enum eDevTypes {
    SI_PDU=0,
    IP_PDU,
    MPDU,
    ZPDU,
    ATS,
    RPDU,
    IP_BUSBAR,
    MPDU_CUSTOMIZE,
    IP_PDU_CUSTOMIZE,

    AC = 1, // 交流
    DC,     // 直流

    Sum=0,
    Transformer, // 互感器
    Mn    // 锰铜
};


/**
 * RTU传输统计结构体
 */
struct sCount
{
    sCount() {all=ok=err=cnt=0;}

    int cnt;
    int all;
    int ok;
    int err;
};

struct sCfgItem
{    
    uchar modeId;
    uchar addr;
    uint devId;

    QString sn;
    QString mac;
    QString user;
    QString dev_type;
    QString startMac;
    QString endMac;
    uint cntMac;

    sCount cnt;
    int logCount;

    bool enSn;
    uchar pcNum;
    ushort currentNum;
    SerialPort *com;
};


class Cfg
{
    Cfg();
public:
    static Cfg *bulid();

    sCfgItem *item;

    QString getSerialBr(const QString &com);
    QString getSerialName(const QString &key);
    void setSerialBr(const QString &com, const QString &br);
    void setSerialName(const QString &key, const QString &v);

    QString getLoginName();
    void setLoginName(const QString &name);

    void writeCnt();
    void writeCfgDev();

    void setCurrentNum();
    void write(const QString &key, const QVariant& v, const QString &g="cfg");
    QVariant read(const QString &key, const QVariant &v = QVariant(), const QString &g="cfg");

protected:
    void initMac();
    void wirteMac();
    void initCnt();
    bool getDate();
    void setDate();
    void initCfgDev();
    void initCurrentNum();

private:
    CfgCom *mCfg;
};

#endif // CONFIGBASH
