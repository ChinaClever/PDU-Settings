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
    ui->tabWidget->addTab(mZpduWid, tr("ZPDU参数设置"));

    mAtsWid = new Home_AtsWid(ui->tabWidget);
    ui->tabWidget->addTab(mAtsWid, tr("ATS-PDU参数设置"));

    mRpduWid = new Home_RpduWid(tr("标准RPDU"),ui->tabWidget);
    ui->tabWidget->addTab(mRpduWid, tr("标准RPDU参数设置"));

    mXRpduWid = new Home_RpduWid(tr("西蒙RPDU"),ui->tabWidget);
    ui->tabWidget->addTab(mXRpduWid, tr("西蒙RPDU参数设置"));

    mIpBusbarWid = new Home_IpBusbarwid(tr("IP-BUSBAR"),ui->tabWidget);
    ui->tabWidget->addTab(mIpBusbarWid, tr("IP-BUSBAR参数设置"));
}
