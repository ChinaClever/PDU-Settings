#include "home_setopdlg.h"
#include "ui_home_setopdlg.h"

Home_SetOpDlg::Home_SetOpDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Home_SetOpDlg)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
    mOutputWid = new Home_OutputWid(ui->groupBox);
}

Home_SetOpDlg::~Home_SetOpDlg()
{
    delete ui;
}

void Home_SetOpDlg::on_okBtn_clicked()
{
    sUnit unit;

    unit.en = ui->enComboBox->currentIndex();
    unit.min = ui->curMinSpin->value();
    unit.max = ui->curMaxSpin->value();
    unit.crMin = ui->curCrMinSpin->value();
    unit.crMax = ui->curCrMaxSpin->value();
    mOutputWid->setUnit(unit);
}

void Home_SetOpDlg::updateIndex(int id)
{
    Dev_Object *dev = Dev_Mpdu::bulid(this);
    switch (id) {
    case 2: break;
    case 3: break;
    }

    sObjData *obj = &(dev->getDev()->data);
    mOutputWid->init(obj);
}
