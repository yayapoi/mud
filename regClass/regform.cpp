#include "regform.h"
#include "ui_regform.h"
#include <QMessageBox>
#include <QDebug>

RegForm::RegForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegForm)
{
    ui->setupUi(this);
    connect(&regWidget,&RegWidget::newReg,[&](){
        //qDebug()<<"新增触发器";
        RegPtr backPtr;
        regWidget.getRegPtr(backPtr);
        newReg(backPtr.oneReg);
        treeAddReg(backPtr.oneReg);
    });
    connect(&parentWidget,&ParentWidget::newParent,[&](){
        //qDebug()<<"新增类";
        QString backStr=parentWidget.getLeiName();
        if(regMap!=nullptr)
        {
            QMap<QString, RegPtr*>* asdfasdf=new QMap<QString, RegPtr*>;
            regMap->insert(backStr,asdfasdf);
        }
        QTreeWidgetItem *topItem = new QTreeWidgetItem(ui->regTrre);
        topItem->setText(0,backStr);
        ui->regTrre->addTopLevelItem(topItem);
    });

    QAction *leiaction=new QAction(&treeMenu);//新增类
    leiaction->setText("新增类");
    treeMenu.addAction(leiaction);
    connect(leiaction,&QAction::triggered,this,[&]() mutable{
        //新增类
        //qDebug()<<"新增类";
        parentWidget.clearAll(regMap);
        parentWidget.show();
    });

    QAction *regaction=new QAction(&treeMenu);//新增Reg
    regaction->setText("新增触发器");
    treeMenu.addAction(regaction);
    connect(regaction,&QAction::triggered,this,[&]() mutable{
        //qDebug()<<"新增触发器";
        QTreeWidgetItem* currentItem=ui->regTrre->currentItem();
        if(currentItem==nullptr)
        {
            //qDebug()<<"currentItem==nullptr  "<<currentItem;
            regWidget.clearAll(regMap, "默认分组");
        }
        else
        {
            //qDebug()<<"currentItem!=nullptr  "<<currentItem;
            QTreeWidgetItem * phItem = currentItem->parent();    //获取当前item的父item
            if(!phItem)//说明是根节点
            {
                //qDebug()<<"gen "<<phItem;
                regWidget.clearAll(regMap, currentItem->text(0));
            }
            else
            {
                //qDebug()<<"zi "<<ui->leiLE->text();
                regWidget.clearAll(regMap, ui->leiLE->text());
            }
        }
        regWidget.show();
    });

    QAction *deleteaction=new QAction(&treeMenu);//删除
    deleteaction->setText("删除");
    treeMenu.addAction(deleteaction);
    connect(deleteaction,&QAction::triggered,this,[&]() mutable{
        //删除
        //qDebug()<<"删除";
        deleteReg();
    });


    ui->regTrre->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->regTrre,&QTreeWidget::customContextMenuRequested,[&](QPoint pos){
        treeMenu.exec(QCursor::pos());
    });
}

RegForm::~RegForm()
{
    delete ui;
}

void RegForm::setRegMapPtr(QMap<QString, QMap<QString, RegPtr *> *> *newRegMap)
{
    regMap=newRegMap;
}

void RegForm::enableParent(bool flag)
{
    ui->parentLE->setEnabled(flag);
    ui->parentOpenBT->setEnabled(flag);
    ui->parentCloseBT->setEnabled(flag);
}

void RegForm::enableReg(bool flag)
{
    ui->leiLE->setEnabled(flag);
    ui->nameLE->setEnabled(flag);
    ui->regStrLE->setEnabled(flag);
    ui->rowLE->setEnabled(flag);
    ui->oneStrOneRegCB->setEnabled(flag);
    ui->sysOrUserCB->setEnabled(flag);
    ui->sysOrUserWidget->setEnabled(flag);
    ui->enableCB->setEnabled(flag);
}

RegPtr *RegForm::getRegPtrFromMap(QString parent, QString name)
{
    RegPtr* backPtr=nullptr;
    bool flag=false;
    if(regMap!=nullptr)
    {
        QMap<QString, QMap<QString, RegPtr*>*>::Iterator firstMapIter=regMap->begin();
        while (firstMapIter!=regMap->end()) {
            if(firstMapIter.key()==parent)
            {
                QMap<QString, RegPtr*>* secondMapPtr=firstMapIter.value();
                QMap<QString, RegPtr*>::Iterator secondMapIter=secondMapPtr->begin();
                while (secondMapIter!=secondMapPtr->end()) {
                    if(secondMapIter.key()==name)
                    {
                        backPtr=secondMapIter.value();
                        flag=true;
                        break;
                    }
                    secondMapIter++;
                }
            }
            if(flag==true)
            {
                break;//找到了指针
            }
            firstMapIter++;
        }
    }
    return backPtr;
}

QTreeWidgetItem *RegForm::getItemFromTree(QString parent, QString name, itemPtr flag)
{
    QTreeWidgetItem *backItem=nullptr;
    switch (flag) {
    case itemPtr::parent:
    {
        QTreeWidgetItemIterator iterator(ui->regTrre);
        while (*iterator) {
            if ((*iterator)->text(0) == parent && !(*iterator)->parent()) {
                backItem = (*iterator);
                break;
            }
            ++iterator;
        }
        break;
    }
    case itemPtr::child:
    {
        QTreeWidgetItemIterator iterator(ui->regTrre);
        while (*iterator) {
            if ((*iterator)->text(0) == parent && !(*iterator)->parent()) {
                    int childNum=(*iterator)->childCount();
                    while (childNum!=0) {
                        //qDebug()<<"name--"<<(parentItem->child(childNum-1))->text(0);
                        if (((*iterator)->child(childNum-1))->text(0) == name) {
                            //qDebug()<<"find  name--"<<(parentItem->child(childNum-1))->text(0);
                            backItem=((*iterator)->child(childNum-1));
                            break;
                        }
                        childNum--;
                    }
                break;
            }
            ++iterator;
        }
        break;
    }
    default:
        break;
    }
    return backItem;
}

void RegForm::setRegInForm(RegPtr *nowReg)
{
    ui->leiLE->setText(nowReg->oneReg.parent);
    ui->enableCB->setChecked(nowReg->oneReg.enable);
    ui->nameLE->setText(nowReg->oneReg.regName);
    ui->regStrLE->setText(nowReg->oneReg.regStr);
    ui->rowLE->setText(QString::number(nowReg->oneReg.row));
    ui->oneStrOneRegCB->setChecked(nowReg->oneReg.oneStrOneReg);
    ui->sysOrUserCB->setChecked(!nowReg->oneReg.sysOrUser);
    if(ui->sysOrUserCB->isChecked())
    {
        ui->sysOrUserWidget->setCurrentIndex(0);
    }
    else
    {
        ui->sysOrUserWidget->setCurrentIndex(1);
    }
    ui->userPortLE->setText(QString::number(nowReg->oneReg.port));//tcp模式
    ui->cmdLE->setText(nowReg->oneReg.sysStr);//系统命令模式
}

void RegForm::newReg(RegStr inReg)
{
    QMap<QString, QMap<QString, RegPtr*>*>::const_iterator firstMap = regMap->find(inReg.parent);
    if(firstMap!=regMap->end())//主分类存在
    {
        QMap<QString, RegPtr*>* secondMap=firstMap.value();
        QMap<QString, RegPtr*>::const_iterator secondMapIter = secondMap->find(inReg.regName);
        if(secondMapIter!=secondMap->end())//该名字存在
        {
            secondMapIter.value()->oneReg=inReg;
        }
        else//该名字不存在
        {
            RegPtr* newReg=new RegPtr;
            newReg->oneReg=inReg;
            secondMap->insert(inReg.regName,newReg);
        }
    }
    else//主分类不存在
    {
        QMap<QString, RegPtr*>* secondMap=new QMap<QString, RegPtr*>;
        RegPtr* newReg=new RegPtr;
        newReg->oneReg=inReg;
        secondMap->insert(inReg.regName,newReg);
        regMap->insert(inReg.parent,secondMap);
    }
}

void RegForm::treeAddReg(RegStr inReg)
{
    QTreeWidgetItemIterator iterator(ui->regTrre);
    QTreeWidgetItem *parentItem=nullptr;
    while (*iterator) {
        if ((*iterator)->text(0) == inReg.parent && !(*iterator)->parent()) {
            parentItem = (*iterator);
            break;
        }
        ++iterator;
    }
    if(parentItem==nullptr)
    {
        parentItem = new QTreeWidgetItem(ui->regTrre);
        parentItem->setText(0,inReg.parent);
        ui->regTrre->addTopLevelItem(parentItem);
    }
    QTreeWidgetItem *childItem = new QTreeWidgetItem(parentItem);
    childItem->setText(0,inReg.regName);
    childItem->setText(1,inReg.regStr);
    ui->regTrre->setCurrentItem(childItem);
}

void RegForm::deleteReg()
{
    QList<QTreeWidgetItem *> selectItem=ui->regTrre->selectedItems();
    //qDebug()<<""<<selectItem;
    if(!selectItem.empty())
    {
        QTreeWidgetItem * phItem = selectItem[0]->parent();    //获取当前item的父item
        if(!phItem)//说明是根节点
        {
            deleteLei(selectItem[0]->text(0));
        }
        else
        {
            deleteOneReg(phItem->text(0),selectItem[0]->text(0));
        }
        //adsfadsfa();
        delete selectItem[0];
    }
}

void RegForm::deleteLei(QString parent)
{
    if(regMap!=nullptr)
    {
        QMap<QString, QMap<QString, RegPtr*>*>::Iterator backIter=regMap->find(parent);
        if(backIter!=regMap->end())
        {
            QMap<QString, RegPtr*>* backSendMapPtr=backIter.value();
            regMap->remove(parent);
            QMap<QString, RegPtr*>::Iterator SendMapIter=backSendMapPtr->begin();
            while (SendMapIter!=backSendMapPtr->end()) {
                RegPtr* oneReg=SendMapIter.value();
                delete oneReg;
                SendMapIter++;
            }
            delete backSendMapPtr;
        }
    }
}

void RegForm::deleteOneReg(QString parent, QString name)
{
    if(regMap!=nullptr)
    {
        QMap<QString, QMap<QString, RegPtr*>*>::Iterator firstMapIter=regMap->begin();
        while (firstMapIter!=regMap->end()) {
            if(firstMapIter.key()==parent)
            {
                QMap<QString, RegPtr*>::Iterator backIter=firstMapIter.value()->find(name);
                if(backIter!=firstMapIter.value()->end())
                {
                    RegPtr* backSendMapPtr=backIter.value();
                    delete backSendMapPtr;
                    firstMapIter.value()->remove(name);
                }
                break;
            }
            firstMapIter++;
        }
    }
}

void RegForm::deleteRegOnTree(QString parent, QString name)
{
    //qDebug()<<"deleteRegOnTree name--"<<name;
    QTreeWidgetItemIterator iterator(ui->regTrre);
    QTreeWidgetItem *parentItem=nullptr;
    while (*iterator) {
        if ((*iterator)->text(0) == parent && !(*iterator)->parent()) {
            parentItem = (*iterator);
            break;
        }
        ++iterator;
    }
    if(parentItem!=nullptr)
    {
        int childNum=parentItem->childCount();
        while (childNum!=0) {
            //qDebug()<<"name--"<<(parentItem->child(childNum-1))->text(0);
            if ((parentItem->child(childNum-1))->text(0) == name) {
                //qDebug()<<"find  name--"<<(parentItem->child(childNum-1))->text(0);
                delete parentItem->child(childNum-1);
                break;
            }
            childNum--;
        }
    }
}

int RegForm::checkChildMessage()
{
    int flag=0;//找到指定名字
    QString parent=ui->leiLE->text();
    QString name=ui->nameLE->text();
    //qDebug()<<"parent--"<<parent<<"  name--"<<name;
    if(parent=="")
    {
        QMessageBox::information(this,"名字为空","组名不允许为空，请更换名字");
        flag=-1;
    }
    else
    {
        if(name=="")
        {
            QMessageBox::information(this,"名字为空","触发器名字不允许为空，请更换名字");
            flag=-1;
        }
        else
        {
            if(ui->sysOrUserCB->isChecked() && ui->userPortLE->text()=="")
            {
                flag=-1;
                QMessageBox::information(this,"没有填写端口","请填写正确的端口");
            }
            else
            {
                if(ui->regStrLE->text()=="")
                {
                    flag=-1;
                    QMessageBox::information(this,"没有填写触发器语句","请填写正确的触发器语句");
                }
                else
                {
                    if(!ui->sysOrUserCB->isChecked() && ui->cmdLE->text()=="")
                    {
                        flag=-1;
                        QMessageBox::information(this,"没有填写命令","请填写正确的命令");
                    }
                    else
                    {
                        if(oldRegPtr!=nullptr)
                        {
                            if(oldRegPtr->oneReg.parent==parent)//同类
                            {
                                if(oldRegPtr->oneReg.regName!=name)//不同名
                                {
                                    RegPtr* backPtr=getRegPtrFromMap(parent, name);
                                    if(backPtr!=nullptr)
                                    {
                                        QMessageBox::StandardButton backButton=QMessageBox::information(this,"重名触发器","类中有同样名字的触发器，是否覆盖它",QMessageBox::Ok | QMessageBox::Cancel);
                                        if(backButton==QMessageBox::Cancel)
                                        {
                                            flag=-1;
                                        }
                                        else//-1有问题，0正常，1同一组内原来名字，2同一组内非原来名字，3同一组内非原来名字有触发器，4不同组内名字有触发器
                                        {
                                            flag=3;
                                        }
                                    }
                                    else
                                    {
                                        flag=2;
                                    }
                                }
                                else
                                {
                                    flag=1;
                                }
                            }
                            else
                            {
                                RegPtr* backPtr=getRegPtrFromMap(parent, name);
                                if(backPtr!=nullptr)//-1有问题，0正常，1同一组内原来名字，2同一组内非原来名字，3同一组内非原来名字有触发器，4不同组内名字有触发器
                                {
                                    QMessageBox::StandardButton backButton=QMessageBox::information(this,"重名触发器","移到的类中有同样名字的触发器，是否覆盖它",QMessageBox::Ok | QMessageBox::Cancel);
                                    if(backButton==QMessageBox::Cancel)
                                    {
                                        flag=-1;
                                    }
                                    else
                                    {
                                        flag=5;
                                    }
                                }
                                else
                                {
                                    flag=4;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return flag;
}

void RegForm::adsfadsfa()
{
    if(regMap!=nullptr)
    {
        QMap<QString, QMap<QString, RegPtr*>*>::Iterator firstMapIter=regMap->begin();
        while (firstMapIter!=regMap->end()) {
            //qDebug()<<"firstMapIter.key()--"<<firstMapIter.key();
            QMap<QString, RegPtr*>::Iterator secondMapIter=firstMapIter.value()->begin();
            while (secondMapIter!=firstMapIter.value()->end()) {
                //qDebug()<<"secondMapIter.key()--"<<secondMapIter.key()<<"   --"<<secondMapIter.value()->oneReg.enable;

                secondMapIter++;
            }
            firstMapIter++;
        }
    }
}

void RegForm::showEvent(QShowEvent *event)
{
    ui->regTrre->clear();
    if(regMap!=nullptr)
    {
        QTreeWidgetItem *topItem;
        QMap<QString, QMap<QString, RegPtr*>*>::Iterator firstMapIter=regMap->begin();
        while (firstMapIter!=regMap->end()) {
            topItem = new QTreeWidgetItem(ui->regTrre);
            topItem->setText(0,firstMapIter.key());
            ui->regTrre->addTopLevelItem(topItem);
            QMap<QString, RegPtr*>* secondMapPtr=firstMapIter.value();
            QMap<QString, RegPtr*>::Iterator secondMapIter=secondMapPtr->begin();
            while (secondMapIter!=secondMapPtr->end()) {
                RegPtr* regPtr=secondMapIter.value();
                QTreeWidgetItem *item = new QTreeWidgetItem(topItem);
                item->setText(0,regPtr->oneReg.regName);
                item->setText(1,regPtr->oneReg.regStr);
                secondMapIter++;
            }
            firstMapIter++;
        }
        ui->regTrre->setCurrentItem(topItem);
    }
    QWidget::showEvent(event);
}

void RegForm::on_closeBT_clicked()
{
    this->close();
}

void RegForm::on_saveBT_clicked()
{
    QList<QTreeWidgetItem *> selectItem=ui->regTrre->selectedItems();
    //qDebug()<<""<<selectItem;
    //判断父子
    //数据校验格式
    //数据查重
    //弹框提醒
    //保存
    //父同时需要改变所有子的父名
    if(!selectItem.empty())
    {
        QTreeWidgetItem *parentItem=selectItem[0]->parent();
        if(!parentItem)//父
        {
            QString newParentNaem=ui->parentLE->text();
            //qDebug()<<"newParentNaem--"<<newParentNaem<<"  oldParentStr--"<<oldParentStr;
            if(newParentNaem=="")
            {
                QMessageBox::information(this,"组名为空","组名为空，请填入非空名字");
            }
            else
            {
                if(newParentNaem!=oldParentStr)
                {
                    if(regMap->find(newParentNaem)!=regMap->end())
                    {
                        QMessageBox::information(this,"组名重复","组名重复，请填入其它名字");
                    }
                    else
                    {
                        QMap<QString, QMap<QString, RegPtr*>*>::Iterator parentIter=regMap->find(selectItem[0]->text(0));
                        if(parentIter==regMap->end())
                        {
                            QMessageBox::information(this,"错误","找不到旧的组");
                        }
                        else
                        {
                            QMap<QString, RegPtr*>* secondMapPtr=parentIter.value();
                            regMap->remove(selectItem[0]->text(0));
                            regMap->insert(newParentNaem,secondMapPtr);
                            QMap<QString, RegPtr*>::Iterator sedondMapIte=secondMapPtr->begin();//父同时需要改变所有子的父名
                            while (sedondMapIte!=secondMapPtr->end()) {
                                sedondMapIte.value()->oneReg.parent=newParentNaem;
                                sedondMapIte++;
                            }
                            selectItem[0]->setText(0,newParentNaem);
                            oldParentStr=newParentNaem;
                        }
                    }
                }
            }
        }
        else//子
        {
            int backint=checkChildMessage();
            if(backint!=-1)
            {
                QString oldName=selectItem[0]->text(0);
                QString oldparentName=parentItem->text(0);
                RegPtr backPtr;
                backPtr.oneReg.parent=ui->leiLE->text();
                backPtr.oneReg.regName=ui->nameLE->text();
                backPtr.oneReg.regStr=ui->regStrLE->text();
                backPtr.oneReg.row=ui->rowLE->text().toInt();
                backPtr.oneReg.oneStrOneReg=ui->oneStrOneRegCB->isChecked();
                backPtr.oneReg.enable=ui->enableCB->isChecked();
                backPtr.oneReg.sysOrUser=!ui->sysOrUserCB->isChecked();
                if(ui->sysOrUserCB->isChecked())
                    backPtr.oneReg.port=ui->userPortLE->text().toInt();
                else
                    backPtr.oneReg.sysStr=ui->cmdLE->text();
                if(regMap!=nullptr)
                {
                    //qDebug()<<"-------";-1有问题，0正常，1同一组内原来名字，2同一组内非原来名字，3同一组内非原来名字有触发器，4不同组内名字有触发器
                    deleteOneReg(oldparentName, oldName);
                    deleteOneReg(backPtr.oneReg.parent, backPtr.oneReg.regName);
                    newReg(backPtr.oneReg);
                    switch (backint) {
                    case 5:
                    {
                        //不同组内名字有触发器
                        delete selectItem[0];
                        QTreeWidgetItem* backitem=getItemFromTree(backPtr.oneReg.parent, backPtr.oneReg.regName, itemPtr::child);
                        if(backitem!=nullptr)
                        {
                            backitem->setText(1,backPtr.oneReg.regStr);
                            ui->regTrre->setCurrentItem(backitem);
                        }
                        break;
                    }
                    case 4:
                    {
                        //不同组内名字没有触发器
                        delete selectItem[0];
                        treeAddReg(backPtr.oneReg);
                        break;
                    }
                    case 3:
                    {
                        //同一组内非原来名字有触发器
                        delete selectItem[0];
                        QTreeWidgetItem* backitem=getItemFromTree(backPtr.oneReg.parent, backPtr.oneReg.regName, itemPtr::child);
                        if(backitem!=nullptr)
                        {
                            backitem->setText(1,backPtr.oneReg.regStr);
                            ui->regTrre->setCurrentItem(backitem);
                        }
                        break;
                    }
                    case 2:
                    {
                        //同一组内非原来名字 没有重名触发器
                        selectItem[0]->setText(0, backPtr.oneReg.regName);
                        break;
                    }
                    default:
                        break;
                    }
                }
            }
        }
    }
    adsfadsfa();
}

void RegForm::on_parentOpenBT_clicked()
{
    //循环开启所有触发
    QList<QTreeWidgetItem *> selectItem=ui->regTrre->selectedItems();
    if(!selectItem.empty())
    {
        if(regMap!=nullptr)
        {
            QMap<QString, QMap<QString, RegPtr*>*>::Iterator firstMapIter=regMap->begin();
            while (firstMapIter!=regMap->end()) {
                if(firstMapIter.key()==selectItem[0]->text(0))
                {
                    QMap<QString, RegPtr*>::Iterator secondMapIter=firstMapIter.value()->begin();
                    while (secondMapIter!=firstMapIter.value()->end()) {
                        secondMapIter.value()->oneReg.enable=true;
                        secondMapIter++;
                    }
                    break;
                }
                firstMapIter++;
            }
        }
    }
    //adsfadsfa();
}

void RegForm::on_parentCloseBT_clicked()
{
    //循环关闭所有触发
    QList<QTreeWidgetItem *> selectItem=ui->regTrre->selectedItems();
    if(!selectItem.empty())
    {
        if(regMap!=nullptr)
        {
            QMap<QString, QMap<QString, RegPtr*>*>::Iterator firstMapIter=regMap->begin();
            while (firstMapIter!=regMap->end()) {
                if(firstMapIter.key()==selectItem[0]->text(0))
                {
                    QMap<QString, RegPtr*>::Iterator secondMapIter=firstMapIter.value()->begin();
                    while (secondMapIter!=firstMapIter.value()->end()) {
                        secondMapIter.value()->oneReg.enable=false;
                        secondMapIter++;
                    }
                    break;
                }
                firstMapIter++;
            }
        }
    }
    //adsfadsfa();
}


void RegForm::on_regTrre_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    if(current!=nullptr)
    {
        QTreeWidgetItem * phItem = current->parent();    //获取当前item的父item
        //qDebug()<<current->childCount();
        //qDebug()<<"phItem--"<<phItem;
        if(!phItem)//说明是根节点
        {
            enableParent(true);
            ui->parentStackedWidget->setCurrentIndex(0);
            oldParentStr=current->text(0);
            ui->parentLE->setText(oldParentStr);
            oldRegPtr=nullptr;
            ui->saveBT->setEnabled(true);
        }
        else
        {
            //qDebug()<<phItem->text(0);
            //qDebug()<<item->text(0);
            ui->parentStackedWidget->setCurrentIndex(1);
            RegPtr* backPtr=getRegPtrFromMap(phItem->text(0), current->text(0));
            if(backPtr!=nullptr)//若是找到了则加载界面
            {
                enableReg(true);
                oldRegPtr=backPtr;
                setRegInForm(oldRegPtr);
                ui->saveBT->setEnabled(true);
            }
            else//若是没找到，则全部不能点击
            {
                oldRegPtr=nullptr;
                enableReg(false);
                ui->saveBT->setEnabled(false);
            }
        }
    }
}

