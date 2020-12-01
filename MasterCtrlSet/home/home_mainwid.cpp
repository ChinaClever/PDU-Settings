#include "home_mainwid.h"
#include "ui_home_mainwid.h"

Home_MainWid::Home_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_MainWid)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
    initWid();
}

Home_MainWid::~Home_MainWid()
{
    delete ui;
}


void Home_MainWid::initWid()
{
    ui->tabWidget->tabBar()->hide();
    mWorkWid = new Home_WorkWid(ui->workWid);
    //    connect(mWorkWid, SIGNAL(startSig()), this, SIGNAL(startSig()));

    mSiWid = new Home_SiWid(ui->tabWidget);
    ui->tabWidget->addTab(mSiWid, tr("SI-PDU参数设置"));
    connect(mSiWid, SIGNAL(errSig()), mWorkWid, SLOT(errSlot()));
    connect(mWorkWid, SIGNAL(enabledSig(bool)), mSiWid, SLOT(enabledSlot(bool)));

    mIpWid = new Home_IpWid(ui->tabWidget);
    ui->tabWidget->addTab(mIpWid, tr("IP-PDU参数设置"));
    connect(mIpWid, SIGNAL(errSig()), mWorkWid, SLOT(errSlot()));
    connect(mWorkWid, SIGNAL(enabledSig(bool)), mIpWid, SLOT(enabledSlot(bool)));

    mMpduWid = new Home_MpduWid(ui->tabWidget);
    ui->tabWidget->addTab(mMpduWid, tr("MPDU参数设置"));
    connect(mMpduWid, SIGNAL(errSig()), mWorkWid, SLOT(errSlot()));
    connect(mWorkWid, SIGNAL(enabledSig(bool)), mMpduWid, SLOT(enabledSlot(bool)));
}
