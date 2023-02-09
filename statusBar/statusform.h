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
    void setHpMpStatus(QString);
    void hideAll(bool flag);
    ///界面隐藏至只剩按钮时，界面依旧占用很大面积，不能点击主界面，所以记录下宽高，改变本界面大小
    void setSizes(int Width, int Height);
    ///主界面获取这界面是否缩小状态 true:隐藏  false:不隐藏
    bool getHideStatus();
private slots:
    void on_resizeBT_clicked(bool checked);

private:
    Ui::StatusForm *ui;

    ///隐藏后的宽高
    int width=100;
    ///隐藏后的宽高
    int height=100;
signals:
    /* @brief 告诉主界面自己是否隐藏，挪动自己*/
    void StatusFormHide(bool);
};

#endif // STATUSFORM_H
