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
    mWorkWid = new Home_WorkWid(ui->workWid);
    //    connect(mWorkWid, SIGNAL(startSig()), this, SIGNAL(startSig()));

    ui->tabWidget->tabBar()->hide();
    mMpduWid = new Home_MpdubWid(ui->tabWidget);
    ui->tabWidget->insertTab(0, mMpduWid, tr("MPDU参数设置"));
    connect(mWorkWid, SIGNAL(enabledSig(bool)), mMpduWid, SLOT(enabledSlot(bool)));
}
