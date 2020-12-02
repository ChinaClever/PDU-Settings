#include "home_workwid.h"
#include "ui_home_workwid.h"

Home_WorkWid::Home_WorkWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_WorkWid)
{
    ui->setupUi(this);

    QTimer::singleShot(150,this,SLOT(initFunSlot()));
    QGridLayout *gridLayout = new QGridLayout(parent);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->addWidget(this);
}

Home_WorkWid::~Home_WorkWid()
{
    delete ui;
}

void Home_WorkWid::initFunSlot()
{
    mCnt = 0;
    mItem = Cfg::bulid()->item;
    mSetOpDlg = new Home_SetOpDlg(this);
    initTypeComboBox();
}

void Home_WorkWid::on_setBtn_clicked()
{
    QString str = tr("修改");
    bool en = ++mCnt % 2;
    if(en) str = tr("保存");
    else {
        mItem->user = ui->userEdit->text();
        Cfg::bulid()->writeCfgDev();
    }

    emit enabledSig(en);
    ui->setBtn->setText(str);
    ui->userEdit->setEnabled(en);
}

void Home_WorkWid::saveErrSlot()
{
    mCnt = 1;
    emit enabledSig(true);
    ui->setBtn->setText(tr("保存"));
}

void Home_WorkWid::on_outputBtn_clicked()
{
    mSetOpDlg->exec();
}

void Home_WorkWid::on_typeComboBox_currentIndexChanged(int index)
{
    emit typeSig(index);
    mItem->modeId = index;
    Cfg::bulid()->writeCfgDev();
}

void Home_WorkWid::initTypeComboBox()
{
    int index = mItem->modeId;
    ui->typeComboBox->setCurrentIndex(index);
    emit typeSig(index);
}
