#include "regwidget.h"
#include "qdebug.h"
#include "qregularexpression.h"
#include <QMessageBox>
#include "qvalidator.h"
#include "ui_regwidget.h"

RegWidget::RegWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegWidget)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_ShowModal, true);           //属性设置 true:模态 false:非模态
    ui->leiLE->setValidator(new QRegularExpressionValidator(QRegularExpression("^[\u4e00-\u9fa5_a-zA-Z0-9]+$"),this));
    ui->nameLE->setValidator(new QRegularExpressionValidator(QRegularExpression("^[\u4e00-\u9fa5_a-zA-Z0-9]+$"),this));
    ui->rowLE->setValidator(new QRegularExpressionValidator(QRegularExpression("^[1-9][0-9]{0,1}$"),this));
    ui->userPortLE->setValidator(new QRegularExpressionValidator(QRegularExpression("^([0-9]|[1-9]\\d{1,3}|[1-5]\\d{4}|6[0-4]\\d{4}|65[0-4]\\d{2}|655[0-2]\\d|6553[0-5])$"),this));
}

RegWidget::~RegWidget()
{
    delete ui;
}

void RegWidget::clearAll(QMap<QString, QMap<QString, RegPtr *> *> *nowregMap)
{
    regMap=nowregMap;
    ui->leiLE->setText("默认分组");
    ui->nameLE->clear();
    ui->regStrLE->clear();
    ui->rowLE->setText("1");
    ui->oneStrOneRegCB->setChecked(true);
    ui->sysOrUserCB->setChecked(true);
    ui->sysOrUserWidget->setCurrentIndex(0);
    ui->enableCB->setEnabled(true);
    ui->cmdLE->clear();
    ui->userPortLE->clear();
}

bool RegWidget::getRegPtr(RegPtr &backPtr)
{
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
    return userYesOrNo;
}

void RegWidget::on_newBT_clicked()
{
    if(!checkMessage())
    {
        userYesOrNo=true;
        close();
        emit newReg();
    }
}

void RegWidget::on_closeBT_clicked()
{
    userYesOrNo=false;
    close();
}

bool RegWidget::checkMessage()
{
    bool flag=false;//找到指定名字
    QString parent=ui->leiLE->text();
    QString name=ui->nameLE->text();
    //qDebug()<<"parent--"<<parent<<"  name--"<<name;
    if(parent=="")
    {
        QMessageBox::information(this,"名字为空","组名不允许为空，请更换名字");
        flag=true;
    }
    else
    {
        if(name=="")
        {
            QMessageBox::information(this,"名字为空","触发器名字不允许为空，请更换名字");
            flag=true;
        }
        else
        {
            if(ui->sysOrUserCB->isChecked() && ui->userPortLE->text()=="")
            {
                flag=true;
                QMessageBox::information(this,"没有填写端口","请填写正确的端口");
            }
            else
            {
                if(ui->regStrLE->text()=="")
                {
                    flag=true;
                    QMessageBox::information(this,"没有填写触发器语句","请填写正确的触发器语句");
                }
                else
                {
                    if(!ui->sysOrUserCB->isChecked() && ui->cmdLE->text()=="")
                    {
                        flag=true;
                        QMessageBox::information(this,"没有填写命令","请填写正确的命令");
                    }
                    else
                    {
                        if(regMap!=nullptr)
                        {
                            QMap<QString, QMap<QString, RegPtr*>*>::Iterator firstMapIter=regMap->begin();
                            while (firstMapIter!=regMap->end()) {
                                //qDebug()<<"firstMapIter.key()--"<<firstMapIter.key();
                                if(firstMapIter.key()==parent)
                                {
                                    QMap<QString, RegPtr*>* secondMapPtr=firstMapIter.value();
                                    QMap<QString, RegPtr*>::Iterator secondMapIter=secondMapPtr->begin();
                                    while (secondMapIter!=secondMapPtr->end()) {
                                        //qDebug()<<"secondMapIter.key()--"<<secondMapIter.key();
                                        if(secondMapIter.key()==name)
                                        {
                                            //qDebug()<<"name--"<<name;
                                            QMessageBox::information(this,"名字重复","该触发器名字在该组已存在，请更换名字");
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
                    }
                }
            }
        }
    }
    return flag;
}


void RegWidget::on_sysOrUserCB_stateChanged(int arg1)
{
    //qDebug()<<"arg1--"<<arg1;
    switch (arg1) {
    case 0:
        ui->sysOrUserWidget->setCurrentIndex(1);
        break;
    case 2:
        ui->sysOrUserWidget->setCurrentIndex(0);
        break;
    default:
        break;
    }
}

void RegWidget::closeEvent(QCloseEvent *event)
{
    on_closeBT_clicked();
}

