#ifndef HOME_SETMACWID_H
#define HOME_SETMACWID_H

#include <QWidget>
#include "common.h"
#include "dev_object.h"

namespace Ui {
class Home_SetMacWid;
}

class Home_SetMacWid : public QWidget
{
    Q_OBJECT

public:
    explicit Home_SetMacWid(QWidget *parent = nullptr);
    ~Home_SetMacWid();
    bool Check();
    void updateParams();
    void initWid(sDevData *dev);

private slots:
    void on_defaultIPPrefix_clicked(bool checked);
    void on_defaultIPAddr_clicked(bool checked);
    void on_defaultUser_clicked(bool checked);
    void on_defaultPassword_clicked(bool checked);
    void on_defaultBackendAddr_clicked(bool checked);
    void on_defaultmacControlID_clicked(bool checked);
    void on_defaultSetMacControlID_clicked(bool checked);
private:
    Ui::Home_SetMacWid *ui;

    sCfgItem *mItem;
    Dev_Object *mObj;
    sDevData *mDev;
};

#endif // HOME_SETMACWID_H
