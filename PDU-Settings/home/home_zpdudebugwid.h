#ifndef HOME_ZPDUDEBUGWID_H
#define HOME_ZPDUDEBUGWID_H

#include <QWidget>
#include "common.h"
#include "devices/dev_object.h"
#include "devices/dev_zpduhw.h"

namespace Ui {
class Home_ZpduDebugWid;
}

class Home_ZpduDebugWid : public QWidget
{
    Q_OBJECT

public:
    explicit Home_ZpduDebugWid(QWidget *parent = nullptr);
    ~Home_ZpduDebugWid();

    void updateData();
    bool loopCheck();
    bool lineCheck();

protected slots:
    void initFunSlot();

private slots:
    void on_logopathBtn_clicked();

private:
    void initData();
    QString selectFile(const QString &filter, QString dir);

private:
    Ui::Home_ZpduDebugWid *ui;
    sCfgItem *mItem;
    Dev_Object *mObj;
    sDevData *mDev;
};

#endif // HOME_ZPDUDEBUGWID_H
