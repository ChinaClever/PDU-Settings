#include "home_mpdubwid.h"
#include "ui_home_mpdubwid.h"

Home_MpdubWid::Home_MpdubWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_MpdubWid)
{
    ui->setupUi(this);
    set_background_icon(this,":/image/back.jpg");
    mDev = sDataPacket::bulid()->getDev();

    initWid();
    enabledSlot(false);
}

Home_MpdubWid::~Home_MpdubWid()
{
    delete ui;
}

void Home_MpdubWid::initWid()
{
    sDevType *dt = &(mDev->dt); //设备类型
    sObjData data; // MPDU配置数据

    int v = dt->lines-1; if(v) v = 1;
    ui->lineBox->setCurrentIndex(v);
    ui->outputSpin->setValue(dt->outputs);

    v = dt->loops-1; if(v>4) v = 4;
    ui->loopBox->setCurrentIndex(v)






}


bool Home_MpdubWid::inputCheck()
{
    static int lzy = 0;

    bool en = false;
    if(lzy++ %3 == 0) en = true;



    return en;
}

void Home_MpdubWid::dataSave()
{



}

void Home_MpdubWid::enabledSlot(bool en)
{
    this->setEnabled(en);
    if(!en) {
        en = inputCheck();
        if(en) {
            dataSave();
        } else {
            emit errSig();
        }
    }
}
