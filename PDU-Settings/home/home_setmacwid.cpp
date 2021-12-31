#include "home_setmacwid.h"
#include "ui_home_setmacwid.h"

Home_SetMacWid::Home_SetMacWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_SetMacWid)
{
    ui->setupUi(this);
    set_background_icon(this,":/image/back.jpg");
}

Home_SetMacWid::~Home_SetMacWid()
{
    delete ui;
}

void Home_SetMacWid::initWid(sDevData * dev)
{
    mDev = dev;
    sDevType* ptr =&( dev->dt );
    ui->defaultIPPrefix->setChecked(ptr->default_ip_prefix);
    ui->defaultIPAddr->setChecked(ptr->default_ip_addr);
    ui->defaultUser->setChecked(ptr->default_user);
    ui->defaultPassword->setChecked(ptr->default_password);
    ui->defaultBackendAddr->setChecked(ptr->default_backendAddress);
    ui->defaultmacControlID->setChecked(ptr->default_macControlID);
    ui->defaultSetMacControlID->setChecked(ptr->default_setMacControlID);

    ui->ipPrefix->setText(ptr->ip_prefix);
    ui->ipAddr->setText(ptr->ip_addr);
    ui->user->setText(ptr->user);
    ui->password->setText(ptr->password);
    ui->backendAddr->setText(ptr->backendAddress);
    ui->macControlID->setText(ptr->macControlID);
    ui->setMacControlID->setText(ptr->setMacControlID);
}


void Home_SetMacWid::on_defaultIPPrefix_clicked(bool checked)
{
    ui->ipPrefix->setEnabled(checked);
}

void Home_SetMacWid::on_defaultIPAddr_clicked(bool checked)
{
    ui->ipAddr->setEnabled(checked);
}

void Home_SetMacWid::on_defaultUser_clicked(bool checked)
{
    ui->user->setEnabled(checked);
}

void Home_SetMacWid::on_defaultPassword_clicked(bool checked)
{
    ui->password->setEnabled(checked);
}

void Home_SetMacWid::on_defaultBackendAddr_clicked(bool checked)
{
    ui->backendAddr->setEnabled(checked);
}

void Home_SetMacWid::on_defaultmacControlID_clicked(bool checked)
{
    ui->macControlID->setEnabled(checked);
}

void Home_SetMacWid::on_defaultSetMacControlID_clicked(bool checked)
{
    ui->setMacControlID->setEnabled(checked);
}

bool Home_SetMacWid::Check()
{
    bool ret = false;
    if( !ui->ipPrefix->text().isEmpty() &&
        !ui->ipAddr->text().isEmpty() &&
        !ui->user->text().isEmpty() &&
        !ui->password->text().isEmpty() &&
        !ui->backendAddr->text().isEmpty() &&
        !ui->macControlID->text().isEmpty() &&
        !ui->setMacControlID->text().isEmpty() )
        ret = true;
    return ret;
}

void Home_SetMacWid::updateParams()
{
    sDevType* ptr =&( mDev->dt );
    ptr->default_ip_prefix = ui->defaultIPPrefix->isChecked()?1:0;
    ptr->default_ip_addr = ui->defaultIPAddr->isChecked()?1:0;
    ptr->default_user = ui->defaultUser->isChecked()?1:0;
    ptr->default_password = ui->defaultPassword->isChecked()?1:0;
    ptr->default_backendAddress = ui->defaultBackendAddr->isChecked()?1:0;
    ptr->default_macControlID = ui->defaultmacControlID->isChecked()?1:0;
    ptr->default_setMacControlID = ui->defaultSetMacControlID->isChecked()?1:0;

    ptr->ip_prefix = ui->ipPrefix->text();
    ptr->ip_addr = ui->ipAddr->text();
    ptr->user = ui->user->text();
    ptr->password = ui->password->text();
    ptr->backendAddress = ui->backendAddr->text();
    ptr->macControlID = ui->macControlID->text();
    ptr->setMacControlID = ui->setMacControlID->text();
}
