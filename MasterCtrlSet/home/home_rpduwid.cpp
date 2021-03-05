#include "home_rpduwid.h"
#include "ui_home_rpduwid.h"

Home_RpduWid::Home_RpduWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_RpduWid)
{
    ui->setupUi(this);
    set_background_icon(this,":/image/back.jpg");
}

Home_RpduWid::~Home_RpduWid()
{
    delete ui;
}
