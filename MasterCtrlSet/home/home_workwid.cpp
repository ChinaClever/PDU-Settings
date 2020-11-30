#include "home_workwid.h"
#include "ui_home_workwid.h"

Home_WorkWid::Home_WorkWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_WorkWid)
{
    ui->setupUi(this);

    mCnt = 0;
    QGridLayout *gridLayout = new QGridLayout(parent);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->addWidget(this);
}

Home_WorkWid::~Home_WorkWid()
{
    delete ui;
}

void Home_WorkWid::on_setBtn_clicked()
{
    QString str = tr("修改");
    bool en = ++mCnt % 2;
    if(en) str = tr("保存");
    ui->setBtn->setText(str);
    emit enabledSig(en);
}

void Home_WorkWid::saveErrSlot()
{
    mCnt = 1;
    emit enabledSig(true);
    ui->setBtn->setText(tr("保存"));
}
