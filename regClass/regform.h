#ifndef REGFORM_H
#define REGFORM_H

#include "qtreewidget.h"
#include <QWidget>
#include <QMenu>
#include "regwidget.h"
#include "parentwidget.h"

namespace Ui {
class RegForm;
}

enum itemPtr{
    parent,
    child
};

class RegForm : public QWidget
{
    Q_OBJECT

public:
    explicit RegForm(QWidget *parent = nullptr);
    ~RegForm();

    /** @brief 外部必须先用此函数赋值指针，再show*/
    void setRegMapPtr(QMap<QString, QMap<QString, RegPtr*>*>* newRegMap);
    /** @brief 父页使能*/
    void enableParent(bool flag);
    /** @brief 子页使能*/
    void enableReg(bool flag);
    /** @brief 如果是子节点，则获得该触发体*/
    RegPtr* getRegPtrFromMap(QString parent, QString name);
    /** @brief 传入类名 名字 和父或子。查找item*/
    QTreeWidgetItem* getItemFromTree(QString parent, QString name, itemPtr flag);
    /** @brief 填充界面*/
    void setRegInForm(RegPtr* nowReg);

    /* @brief 获取一个新的触发器，加入进来*/
    void newReg(RegStr inReg);
    /* @brief 新的触发器，加入树*/
    void treeAddReg(RegStr inReg);
    /* @brief 删除组或者某个触发器*/
    void deleteReg();
    /* @brief 删除组*/
    void deleteLei(QString parent);
    /* @brief 删除某个触发器*/
    void deleteOneReg(QString parent, QString name);
    /* @brief 删除tree中某个触发器*/
    void deleteRegOnTree(QString parent, QString name);


    /** @brief 校验函数，-1有问题，0正常，1同一组内原来名字，2同一组内非原来名字没触发器，3同一组内非原来名字有触发器，
     *  4不同组内名字没有触发器，5不同组内名字有触发器*/
    int checkChildMessage();
    /* @brief 检查大小*/
    void adsfadsfa();
protected:
    void showEvent(QShowEvent *event) override;
private slots:
    void on_closeBT_clicked();

    void on_saveBT_clicked();

    void on_parentOpenBT_clicked();

    void on_parentCloseBT_clicked();

    void on_regTrre_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

private:
    Ui::RegForm *ui;
    QMap<QString, QMap<QString, RegPtr*>*>* regMap=nullptr;
    RegPtr* oldRegPtr=nullptr;
    QString oldParentStr="";
    QMenu treeMenu;
    RegWidget regWidget;
    ParentWidget parentWidget;
};

#endif // REGFORM_H
