#include "statusform.h"
#include "ui_statusform.h"
#include <statusBar/pointbar.h>

StatusForm::StatusForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusForm)
{
    ui->setupUi(this);
    ui->mpBar->setPointStatus(pointStatus::mp);
    ui->jingliBar->setPointStatus(pointStatus::mp);
    setStyleSheet("background-color: rgb(255,255,255);");
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
    int hpMax=testList[6].toInt(), hped=testList[7].toInt(), hpNow=testList[8].toInt(), mpMax=testList[9].toInt(), mped=testList[10].toInt(), mpNow=testList[11].toInt();
    ui->hpBar->setPointNum(hpNow, hped, hpMax);
    ui->mpBar->setPointNum(mpNow, mped, mpMax);
    ui->neiliBar->setPointNum(testList[3].toInt(), testList[2].toInt(), testList[2].toInt());
    ui->jingliBar->setPointNum(testList[5].toInt(), testList[4].toInt(), testList[4].toInt());
    ui->jingyan->setText("经验:  "+testList[0]);
    ui->qianneng->setText("潜能:  "+testList[1]);
    ui->zhenqi->setText("真气:  "+testList[12]);
    ui->zhanyi->setText("战意:  "+testList[13]);
    ui->shiwu->setText("食物:  "+testList[14]);
    ui->yinshui->setText("饮水:  "+testList[15]);
    QString zhandou(testList[16].toInt()==1?"是":"否");
    ui->zhandou->setText("战斗:  "+zhandou);
    QString manglu(testList[17].toInt()==1?"是":"否");
    ui->mang->setText("忙碌:  "+manglu);
}
