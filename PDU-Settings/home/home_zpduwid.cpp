#include "home_zpduwid.h"
#include "ui_home_zpduwid.h"

Home_ZpduWid::Home_ZpduWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_ZpduWid)
{
    ui->setupUi(this);
    set_background_icon(this,":/image/back.jpg");
}

Home_ZpduWid::~Home_ZpduWid()
{
    delete ui;
}
