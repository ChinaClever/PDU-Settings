#ifndef HOME_RPDUWID_H
#define HOME_RPDUWID_H

#include "home_zpduwid.h"

namespace Ui {
class Home_RpduWid;
}

class Home_RpduWid : public QWidget
{
    Q_OBJECT

public:
    explicit Home_RpduWid(QWidget *parent = nullptr);
    ~Home_RpduWid();

private:
    Ui::Home_RpduWid *ui;
};

#endif // HOME_RPDUWID_H
