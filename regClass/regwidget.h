#ifndef REGWIDGET_H
#define REGWIDGET_H

#include "globalhead.h"
#include <QWidget>

namespace Ui {
class RegWidget;
}

class RegWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RegWidget(QWidget *parent = nullptr);
    ~RegWidget();

    /** @brief 显示此窗口时，应该调用此函数再显示*/
    void clearAll(QMap<QString, QMap<QString, RegPtr*>*>*);
    /** @brief 当此窗口关闭时，返回用户是否想要添加，并返回一个指针*/
    bool getRegPtr(RegPtr &backPtr);
private slots:
    void on_newBT_clicked();

    void on_closeBT_clicked();

    void on_sysOrUserCB_stateChanged(int arg1);

protected:
    void closeEvent(QCloseEvent *event) override;
signals:
    void newReg();
private:
    Ui::RegWidget *ui;
    bool userYesOrNo=false;
    QMap<QString, QMap<QString, RegPtr*>*>* regMap=nullptr;

    /** @brief 校验函数，不返回true不保存*/
    bool checkMessage();
};

#endif // REGWIDGET_H
