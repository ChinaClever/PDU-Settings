#ifndef HOME_ATSWID_H
#define HOME_ATSWID_H

#include "home_rpduwid.h"

namespace Ui {
class Home_AtsWid;
}

class Home_AtsWid : public QWidget
{
    Q_OBJECT

public:
    explicit Home_AtsWid(QWidget *parent = nullptr);
    ~Home_AtsWid();

private:
    Ui::Home_AtsWid *ui;
};

#endif // HOME_ATSWID_H
