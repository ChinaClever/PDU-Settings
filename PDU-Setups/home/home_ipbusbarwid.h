#ifndef HOME_IPBUSBARWID_H
#define HOME_IPBUSBARWID_H

#include "home_atswid.h"

namespace Ui {
class Home_IpBusbarwid;
}

class Home_IpBusbarwid : public QWidget
{
    Q_OBJECT

public:
    explicit Home_IpBusbarwid(QString str, QWidget *parent = nullptr);
    ~Home_IpBusbarwid();

private:
    Ui::Home_IpBusbarwid *ui;
};

#endif // HOME_IPBUSBARWID_H
