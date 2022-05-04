#include "statusform.h"
#include "ui_statusform.h"
#include <statusBar/pointbar.h>

StatusForm::StatusForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusForm)
{
    ui->setupUi(this);
    ui->mpBar->setPointStatus(pointStatus::mp);
}

StatusForm::~StatusForm()
{
    delete ui;
}

void StatusForm::setHpMpStatus(int hpMax, int hped, int hpNow, int mpMax, int mped, int mpNow)
{
    ui->hpNum->setText(QString(" %1% ( %2 / %3 / %4 )").arg(QString::number(100.0*hpNow/hpMax, 'f', 2)).arg(hpNow).arg(hped).arg(hpMax));
    ui->hpBar->setPointNum(hpNow, hped, hpMax);
    ui->mpNum->setText(QString(" %1% ( %2 / %3 / %4 )").arg(QString::number(100.0*mpNow/mpMax, 'f', 2)).arg(mpNow).arg(mped).arg(mpMax));
    ui->mpBar->setPointNum(mpNow, mped, mpMax);
}
