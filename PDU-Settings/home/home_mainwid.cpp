/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
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
    connect(mWorkWid, SIGNAL(typeSig(int)), ui->tabWidget, SLOT(setCurrentIndex(int)));
    connect(mWorkWid, SIGNAL(startSig()), this, SIGNAL(startSig()));

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
    connect(mMpduWid, SIGNAL(sendMpduVerSig(int)), mWorkWid, SLOT(recvVerSlot(int)));

    mZpduWid = new Home_ZpduWid(ui->tabWidget);
    ui->tabWidget->addTab(mZpduWid, tr("ZPDU特殊定制参数设置"));
    connect(mZpduWid, SIGNAL(errSig()), mWorkWid, SLOT(errSlot()));
    connect(mWorkWid, SIGNAL(enabledSig(bool)), mZpduWid, SLOT(enabledSlot(bool)));

    mAtsWid = new Home_AtsWid(ui->tabWidget);
    ui->tabWidget->addTab(mAtsWid, tr("ATS-PDU参数设置"));
    connect(mAtsWid, SIGNAL(errSig()), mWorkWid, SLOT(errSlot()));
    connect(mWorkWid, SIGNAL(enabledSig(bool)), mAtsWid, SLOT(enabledSlot(bool)));

    mRpduWid = new Home_RpduWid(ui->tabWidget);
    ui->tabWidget->addTab(mRpduWid, tr("RPDU参数设置"));
    connect(mRpduWid, SIGNAL(errSig()), mWorkWid, SLOT(errSlot()));
    connect(mWorkWid, SIGNAL(enabledSig(bool)), mRpduWid, SLOT(enabledSlot(bool)));

    mIpBusbarWid = new Home_IpBusbarwid(ui->tabWidget);
    ui->tabWidget->addTab(mIpBusbarWid, tr("IP-BUSBAR参数设置"));
    connect(mIpBusbarWid, SIGNAL(errSig()), mWorkWid, SLOT(errSlot()));
    connect(mWorkWid, SIGNAL(enabledSig(bool)), mIpBusbarWid, SLOT(enabledSlot(bool)));

    mMpduCustomizeWid = new Home_MpduCustomizeWid(ui->tabWidget);
    ui->tabWidget->addTab(mMpduCustomizeWid, tr("MPDU一期或者特殊定制参数设置"));
    connect(mMpduCustomizeWid, SIGNAL(errSig()), mWorkWid, SLOT(errSlot()));
    connect(mWorkWid, SIGNAL(enabledSig(bool)), mMpduCustomizeWid, SLOT(enabledSlot(bool)));

    mIpCustomizeWid = new Home_IpCustomizewid(ui->tabWidget);
    ui->tabWidget->addTab(mIpCustomizeWid, tr("IP-PDU特殊定制参数设置"));
    connect(mIpCustomizeWid, SIGNAL(errSig()), mWorkWid, SLOT(errSlot()));
    connect(mWorkWid, SIGNAL(enabledSig(bool)), mIpCustomizeWid, SLOT(enabledSlot(bool)));

    mZpduHwWid = new Home_ZpduHwWid(1 ,ui->tabWidget );
    ui->tabWidget->addTab(mZpduHwWid, tr("ZPDU华为参数设置"));
    connect(mZpduHwWid, SIGNAL(errSig()), mWorkWid, SLOT(errSlot()));
    connect(mWorkWid, SIGNAL(enabledSig(bool)), mZpduHwWid, SLOT(enabledSlot(bool)));

    mZpduStdWid = new Home_ZpduHwWid(2 ,ui->tabWidget );
    ui->tabWidget->addTab(mZpduStdWid, tr("ZPDU标准参数设置"));
    connect(mZpduStdWid, SIGNAL(errSig()), mWorkWid, SLOT(errSlot()));
    connect(mWorkWid, SIGNAL(enabledSig(bool)), mZpduStdWid, SLOT(enabledSlot(bool)));

    mZpduNetSafeWid = new Home_ZpduHwWid(3 ,ui->tabWidget );
    ui->tabWidget->addTab(mZpduNetSafeWid, tr("ZPDU网络安全设置"));
    connect(mZpduNetSafeWid, SIGNAL(errSig()), mWorkWid, SLOT(errSlot()));
    connect(mWorkWid, SIGNAL(enabledSig(bool)), mZpduNetSafeWid, SLOT(enabledSlot(bool)));
}
