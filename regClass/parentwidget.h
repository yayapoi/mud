#ifndef PARENTWIDGET_H
#define PARENTWIDGET_H

#include "globalhead.h"
#include <QWidget>

namespace Ui {
class ParentWidget;
}

class ParentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ParentWidget(QWidget *parent = nullptr);
    ~ParentWidget();

    /** @brief 显示此窗口时，应该调用此函数再显示*/
    void clearAll(QMap<QString, QMap<QString, RegPtr*>*>*);
    /** @brief 当此窗口关闭时，返回类名*/
    QString getLeiName();
private slots:
    void on_newBT_clicked();

    void on_closeBT_clicked();

protected:
    void closeEvent(QCloseEvent *event) override;
signals:
    void newParent();
private:
    Ui::ParentWidget *ui;
    bool userYesOrNo=false;
    QMap<QString, QMap<QString, RegPtr*>*>* regMap=nullptr;

    /** @brief 校验函数，不返回true不保存*/
    bool checkMessage();
};

#endif // PARENTWIDGET_H
