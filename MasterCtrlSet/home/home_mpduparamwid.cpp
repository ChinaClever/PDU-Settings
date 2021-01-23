#include "home_mpduparamwid.h"
#include "ui_home_mpduparamwid.h"

Home_MpduParamWid::Home_MpduParamWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_MpduParamWid)
{
    ui->setupUi(this);
    set_background_icon(this,":/image/back.jpg");
    QTimer::singleShot(15,this,SLOT(initFunSlot()));
}

Home_MpduParamWid::~Home_MpduParamWid()
{
    delete ui;
}


void Home_MpduParamWid::initFunSlot()
{
    mItem = Cfg::bulid()->item;
    mObj = Dev_Mpdu::bulid(this);
    mDev = mObj->getDev();
    initWid();
    initType();
}

void Home_MpduParamWid::initWid()
{
    int i = 0;
    mLoops[i++] = ui->lpSpin_1;
    mLoops[i++] = ui->lpSpin_2;
    mLoops[i++] = ui->lpSpin_3;
    mLoops[i++] = ui->lpSpin_4;
    mLoops[i++] = ui->lpSpin_5;
    mLoops[i++] = ui->lpSpin_6;

    i = 0;
    mBoards[i++] = ui->opSpin_1;
    mBoards[i++] = ui->opSpin_2;
    mBoards[i++] = ui->opSpin_3;
}

void Home_MpduParamWid::initType()
{
    sDevType *dt = &(mDev->dt); //设备类型
    int v = dt->lines-1; if(v) v = 1;
    ui->lineBox->setCurrentIndex(v);
    v = dt->loops-1; if(v>4) v = 4;
    ui->loopBox->setCurrentIndex(v);

    ui->outputSpin->setValue(dt->outputs);
    ui->breakerBox->setCurrentIndex(dt->breaker);
    ui->standardBox->setCurrentIndex(dt->standar);
    ui->seriesBox->setCurrentIndex(dt->series-1);
    ui->envBox->setCurrentIndex(dt->envbox);
    ui->modbusBox->setCurrentIndex(dt->modbus);
    ui->languageBox->setCurrentIndex(dt->language);
    ui->verBox->setCurrentIndex(dt->mpdu_ver);
    ui->levelBox->setCurrentIndex(dt->level);
    ui->versionEdit->setText(dt->versions);
    ui->boardSpin->setValue(dt->boards);

    for(int i=0; i<6; ++i) mLoops[i]->setValue(dt->loop[i]);
    for(int i=0; i<3; ++i) mBoards[i]->setValue(dt->board[i]);
}


void Home_MpduParamWid::updateType()
{
    sDevType *dt = &(mDev->dt); //设备类型
    int v = ui->lineBox->currentIndex();
    if(v) v = 3; else v = 1; dt->lines = v;

    v = ui->loopBox->currentIndex()+1;
    if(v > 4) v = 6; dt->loops = v;

    dt->outputs = ui->outputSpin->value();
    dt->breaker = ui->breakerBox->currentIndex();
    dt->standar = ui->standardBox->currentIndex();
    dt->series = ui->seriesBox->currentIndex()+1;

    dt->envbox = ui->envBox->currentIndex();
    dt->modbus = ui->modbusBox->currentIndex();
    dt->language = ui->languageBox->currentIndex();
    dt->mpdu_ver = ui->verBox->currentIndex();
    dt->level = ui->levelBox->currentIndex();
    dt->versions = ui->versionEdit->text();
    dt->boards = ui->boardSpin->value();

    for(int i=0; i<6; ++i) dt->loop[i] = mLoops[i]->value();
    for(int i=0; i<3; ++i) dt->board[i] = mBoards[i]->value();
}

void Home_MpduParamWid::on_verBox_currentIndexChanged(int index)
{
    ui->groupBox_2->setHidden(!index);
}

void Home_MpduParamWid::on_boardSpin_valueChanged(int arg1)
{
    bool en = true;
    for(int i=0; i<3; ++i) {
        if(i < arg1) en = false; else {en = true; mBoards[i]->setValue(0);}
        mBoards[i]->setHidden(en);
    }
}

void Home_MpduParamWid::on_loopBox_currentIndexChanged(int index)
{
    bool en = true;
    if(index >= 4) index++;
    for(int i=0; i<6; ++i) {
        if(i > index){en = true; mLoops[i]->setValue(0);} else en = false;
        mLoops[i]->setHidden(en);
    }
}
