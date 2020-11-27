#ifndef HOME_WORKWID_H
#define HOME_WORKWID_H

#include <QWidget>
#include "home_mpdubwid.h"

namespace Ui {
class Home_WorkWid;
}

class Home_WorkWid : public QWidget
{
    Q_OBJECT

public:
    explicit Home_WorkWid(QWidget *parent = nullptr);
    ~Home_WorkWid();

signals:
     void enabledSig(bool en);

private slots:
    void on_setBtn_clicked();

private:
    Ui::Home_WorkWid *ui;
};

#endif // HOME_WORKWID_H
