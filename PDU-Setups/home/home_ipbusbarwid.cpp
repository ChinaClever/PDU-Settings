#include "home_ipbusbarwid.h"
#include "ui_home_ipbusbarwid.h"

Home_IpBusbarwid::Home_IpBusbarwid(QString str, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_IpBusbarwid)
{
    ui->setupUi(this);
    ui->label->setText(str);
    set_background_icon(this,":/image/back.jpg");
}

Home_IpBusbarwid::~Home_IpBusbarwid()
{
    delete ui;
}
