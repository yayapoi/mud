#include "parentwidget.h"
#include "qregularexpression.h"
#include "qvalidator.h"
#include "ui_parentwidget.h"
#include <QMessageBox>

ParentWidget::ParentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParentWidget)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_ShowModal, true);           //属性设置 true:模态 false:非模态
    ui->leiLE->setValidator(new QRegularExpressionValidator(QRegularExpression("^[\u4e00-\u9fa5_a-zA-Z0-9]+$"),this));
}

ParentWidget::~ParentWidget()
{
    delete ui;
}

void ParentWidget::clearAll(QMap<QString, QMap<QString, RegPtr *> *> *nowregMap)
{
    regMap=nowregMap;
    ui->leiLE->clear();
}

QString ParentWidget::getLeiName()
{
    return ui->leiLE->text();
}

void ParentWidget::on_newBT_clicked()
{
    if(!checkMessage())
    {
        userYesOrNo=true;
        close();
        emit newParent();
    }
}


void ParentWidget::on_closeBT_clicked()
{
    userYesOrNo=false;
    close();
}

void ParentWidget::closeEvent(QCloseEvent *event)
{
    on_closeBT_clicked();
}

bool ParentWidget::checkMessage()
{
    bool flag=false;//找到指定名字
    QString parent=ui->leiLE->text();
    //qDebug()<<"parent--"<<parent;
    if(parent=="")
    {
        QMessageBox::information(this,"名字为空","组名不允许为空，请更换名字");
        flag=true;
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
                    QMessageBox::information(this,"名字重复","该组名已存在，请更换名字");
                    flag=true;
                    break;
                }
                firstMapIter++;
            }
        }
    }
    return flag;
}

