#ifndef STATUSFORM_H
#define STATUSFORM_H

#include <QWidget>

namespace Ui {
class StatusForm;
}

class StatusForm : public QWidget
{
    Q_OBJECT

public:
    explicit StatusForm(QWidget *parent = nullptr);
    ~StatusForm();

    void setHpMpStatus(int hpMax, int hped, int hpNow, int mpMax, int mped, int mpNow);
    void setHpMpStatus(QStringList);
private:
    Ui::StatusForm *ui;
};

#endif // STATUSFORM_H
