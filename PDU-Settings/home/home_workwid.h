#ifndef HOME_WORKWID_H
#define HOME_WORKWID_H

#include <QWidget>
#include "home_ipbusbarwid.h"
#include "test_corethread.h"

namespace Ui {
class Home_WorkWid;
}

class Home_WorkWid : public QWidget
{
    Q_OBJECT

public:
    explicit Home_WorkWid(QWidget *parent = nullptr);
    ~Home_WorkWid();

signals:
    void startSig();
    void typeSig(int i);
    void enabledSig(bool en);

protected:
    void initLayout();
    void insertText();
    void setTextColor();
    void initTypeComboBox();

    QString getTime();
    void updateWid();
    void updateTime();
    void updateResult();
    void updateCnt();

    bool initSerial();
    bool initWid();

private slots:
    void timeoutDone();
    void initFunSlot();
    void saveFunSlot();
    void saveErrSlot();
    void on_setBtn_clicked();
    void on_startBtn_clicked();
    void on_outputBtn_clicked();
    void on_typeComboBox_currentIndexChanged(int index);
    void on_snCheckBox_clicked(bool checked);
    void recvVerSlot(int ver);

    void on_pcbEdit_textChanged(const QString &arg1);

public slots:
    void errSlot() {QTimer::singleShot(5,this,SLOT(saveErrSlot()));}

private:
    Ui::Home_WorkWid *ui;

    int mId, mCnt;
    QTimer *timer;
    sProgress *mPro;
    sCfgItem *mItem;
    sDataPacket *mPacket;
    Home_SetOpDlg *mSetOpDlg;
    Test_CoreThread *mCoreThread;

    Dev_Object *mObj;
    sDevData *mDev;
};

#endif // HOME_WORKWID_H
