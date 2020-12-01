#include "home_outputwid.h"
#include "ui_home_outputwid.h"

Home_OutputWid::Home_OutputWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_OutputWid)
{
    ui->setupUi(this);

    initWid();
    QGridLayout *gridLayout = new QGridLayout(parent);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->addWidget(this);
}

Home_OutputWid::~Home_OutputWid()
{
    delete ui;
}

void Home_OutputWid::initWid()
{
    mId = 0;
    QObjectList list = children();
    foreach (QObject *obj, list) {
        if (obj->inherits("QWidget")){
            QWidget *b = qobject_cast<QWidget*>(obj);
            if(b->objectName().contains("widget_"))
                mBoxWid[mId++] = new Home_OpUnitWid(b);
        }
    }
}

void Home_OutputWid::init(sObjData *dev)
{
    for(int i=0; i<mId; ++i) {
        sUnit *opCur = &(dev->opCur[i]);
        mBoxWid[i]->init(opCur);
    }
}

void Home_OutputWid::updateData()
{
    for(int i=0; i<mId; ++i) {
        mBoxWid[i]->updateData();
    }
}

void Home_OutputWid::setUnit(sUnit &unit)
{
    for(int i=0; i<mId; ++i) {
        mBoxWid[i]->setUnit(unit);
    }
}
