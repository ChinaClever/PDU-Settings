#ifndef HOME_ZPDUWID_H
#define HOME_ZPDUWID_H

#include "home_mpduwid.h"

namespace Ui {
class Home_ZpduWid;
}

class Home_ZpduWid : public QWidget
{
    Q_OBJECT

public:
    explicit Home_ZpduWid(QWidget *parent = nullptr);
    ~Home_ZpduWid();

private:
    Ui::Home_ZpduWid *ui;
};

#endif // HOME_ZPDUWID_H
