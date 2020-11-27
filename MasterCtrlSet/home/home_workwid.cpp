#include "home_workwid.h"
#include "ui_home_workwid.h"

Home_WorkWid::Home_WorkWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_WorkWid)
{
    ui->setupUi(this);

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
    QString str = tr("")
    static int lzy = 0;
    bool en = ++lzy % 2;
    if(en) {

    } else {

    }

    emit enabledSig(en);
}
