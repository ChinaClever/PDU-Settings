#ifndef CONFIGBASH
#define CONFIGBASH
#include "cfgcom.h"
#include "serialstatuswid.h"

enum eDevTypes {
    PDU=0,
    ZPDU,
    MPDU,
    RPDU,     // RPDU 执行板
    RPDU_Mc, // RPDU 主控
    SI_PDU,
    IP_PDU,
    BM_PDU,

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
    sCount() {all=ok=err =0;}

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
    QString user;
    QString dev_type;

    sCount cnt;
    int logCount;

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
    void initCnt();
    bool getDate();
    void setDate();
    void initCfgDev();
    void initCurrentNum();

private:
    CfgCom *mCfg;
};

#endif // CONFIGBASH
