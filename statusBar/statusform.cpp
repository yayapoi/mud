#include "statusform.h"
#include "ui_statusform.h"
#include <statusBar/pointbar.h>
#include <QRegularExpression>

StatusForm::StatusForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusForm)
{
    ui->setupUi(this);
    ui->resizeBT->setCheckable(true);
    ui->mpBar->setPointStatus(pointStatus::mp);
    ui->jingliBar->setPointStatus(pointStatus::mp);
    setStyleSheet("background-color: rgb(255,255,255);");
    //on_resizeBT_clicked(true);
}

StatusForm::~StatusForm()
{
    delete ui;
}

void StatusForm::setHpMpStatus(int hpMax, int hped, int hpNow, int mpMax, int mped, int mpNow)
{
    ui->hpBar->setPointNum(hpNow, hped, hpMax);
    ui->mpBar->setPointNum(mpNow, mped, mpMax);
}

void StatusForm::setHpMpStatus(QStringList testList)
{
    if(testList.size()>=18)
    {
        int hpMax=testList[6].toInt(), hped=testList[7].toInt(), hpNow=testList[8].toInt(), mpMax=testList[9].toInt(), mped=testList[10].toInt(), mpNow=testList[11].toInt();
        ui->hpBar->setPointNum(hpNow, hped, hpMax);
        ui->mpBar->setPointNum(mpNow, mped, mpMax);
        ui->neiliBar->setPointNum(testList[3].toInt(), testList[2].toInt(), testList[2].toInt());
        ui->jingliBar->setPointNum(testList[5].toInt(), testList[4].toInt(), testList[4].toInt());
        ui->jingyan->setText("经验:"+testList[0]+"   ");
        ui->qianneng->setText("潜能:"+testList[1]+"   ");
        ui->zhenqi->setText("真气:"+testList[12]+"   ");
        ui->zhanyi->setText("战意:"+testList[13]+"   ");
        ui->shiwu->setText("食物:"+testList[14]+"   ");
        ui->yinshui->setText("饮水:"+testList[15]+"   ");
        QString zhandou(testList[16].toInt()==1?"是":"否");
        ui->zhandou->setText("战斗:"+zhandou+"   ");
        QString manglu(testList[17].toInt()==1?"是":"否");
        ui->mang->setText("忙碌:"+manglu+"   ");
    }
}

void StatusForm::setHpMpStatus(QString instr)
{
    QRegularExpression regStr("^#setHpBar\\(\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\"\\)$");
    QRegularExpressionMatch regularmatch=regStr.match(instr);
    if(regularmatch.hasMatch())
    {
        QStringList testList=regularmatch.capturedTexts();
        testList.removeFirst();
        setHpMpStatus(testList);
    }
}

void StatusForm::hideAll(bool flag)
{
    ui->hpHead->setHidden(flag);
    ui->hpBar->setHidden(flag);
    ui->mpHead->setHidden(flag);
    ui->mpBar->setHidden(flag);
    ui->neiliHead->setHidden(flag);
    ui->neiliBar->setHidden(flag);
    ui->jingliHead->setHidden(flag);
    ui->jingliBar->setHidden(flag);
    ui->jingyan->setHidden(flag);
    ui->qianneng->setHidden(flag);
    ui->zhenqi->setHidden(flag);
    ui->zhanyi->setHidden(flag);
    ui->shiwu->setHidden(flag);
    ui->yinshui->setHidden(flag);
    ui->zhandou->setHidden(flag);
    ui->mang->setHidden(flag);
}

void StatusForm::setSizes(int Width, int Height)
{
    width=Width;
    height=Height;
}

bool StatusForm::getHideStatus()
{
    return ui->hpHead->isHidden();
}

void StatusForm::on_resizeBT_clicked(bool checked)
{
    hideAll(checked);
    if(checked)
    {
        resize(20,20);
    }
    else
    {
        resize(width,height);
    }
    emit StatusFormHide(checked);
}

