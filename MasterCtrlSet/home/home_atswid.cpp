#include "home_atswid.h"
#include "ui_home_atswid.h"

Home_AtsWid::Home_AtsWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_AtsWid)
{
    ui->setupUi(this);
    set_background_icon(this,":/image/back.jpg");
}

Home_AtsWid::~Home_AtsWid()
{
    delete ui;
}
