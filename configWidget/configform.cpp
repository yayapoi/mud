#include "configform.h"
#include "ui_configform.h"
#include <INI/inimanarge.h>
#include "work/maptomapmanage.h"
#include <QDateTime>

ConfigForm::ConfigForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigForm)
{
    ui->setupUi(this);
    UserNameGmcp backstruct;
    INIManarge::GetInstance()->getUserNameGmcp(backstruct);
    ui->nameLE->setText(backstruct.userName);
    ui->idLE->setText(backstruct.userEnName);
    showGmcpCheck showGmcpChecks;
    INIManarge::GetInstance()->getCheckGmcp(showGmcpChecks);
    ui->GMCPGB->setEnabled(showGmcpChecks.showGmcpAll);
    ui->allGMCPset->setChecked(showGmcpChecks.showGmcpAll);
    ui->buffCB->setChecked(showGmcpChecks.buff);
    ui->combatCB->setChecked(showGmcpChecks.combat);
    ui->messageCB->setChecked(showGmcpChecks.message);
    ui->moveCB->setChecked(showGmcpChecks.move);
    ui->statusCB->setChecked(showGmcpChecks.status);
}

ConfigForm::~ConfigForm()
{
    delete ui;
}

void ConfigForm::getNameAndID(QString &name, QString &id)
{
    name=ui->nameLE->text();
    id=ui->idLE->text();
}

void ConfigForm::on_OKBT_clicked()
{
    UserNameGmcp backstruct;
    backstruct.userName=ui->nameLE->text();
    backstruct.userEnName=ui->idLE->text();
    INIManarge::GetInstance()->setUserNameGmcp(backstruct);
    showGmcpCheck showGmcpChecks;
    showGmcpChecks.showGmcpAll=ui->allGMCPset->isChecked();
    showGmcpChecks.buff=ui->buffCB->isChecked();
    showGmcpChecks.combat=ui->combatCB->isChecked();
    showGmcpChecks.message=ui->messageCB->isChecked();
    showGmcpChecks.move=ui->moveCB->isChecked();
    showGmcpChecks.status=ui->statusCB->isChecked();
    INIManarge::GetInstance()->setCheckGmcp(showGmcpChecks);
    emit closeWidget();
    close();
}


void ConfigForm::on_allGMCPset_stateChanged(int arg1)
{
    //qDebug()<<"ConfigForm::on_allGMCPset_stateChanged-- arg1--"<<arg1;
    switch (arg1) {
    case 0:
    {
    ui->GMCPGB->setEnabled(false);
    }
        break;
    case 2:
    {
    ui->GMCPGB->setEnabled(true);
    }
        break;
    default:
        break;
    }
}

void ConfigForm::enableGB(bool flag)
{
    ui->GMCPGB->setEnabled(flag);
}


void ConfigForm::on_buffCB_stateChanged(int arg1)
{
    /*switch (arg1) {
    case 0:
    {}
        break;
    case 2:
    {}
        break;
    default:
        break;
    }*/
}


void ConfigForm::on_moveCB_stateChanged(int arg1)
{
    /*switch (arg1) {
    case 0:
    {}
        break;
    case 2:
    {}
        break;
    default:
        break;
    }*/
}


void ConfigForm::on_combatCB_stateChanged(int arg1)
{
    /*switch (arg1) {
    case 0:
    {}
        break;
    case 2:
    {}
        break;
    default:
        break;
    }*/
}


void ConfigForm::on_statusCB_stateChanged(int arg1)
{
    /*switch (arg1) {
    case 0:
    {}
        break;
    case 2:
    {}
        break;
    default:
        break;
    }*/
}


void ConfigForm::on_messageCB_stateChanged(int arg1)
{
    /*switch (arg1) {
    case 0:
    {}
        break;
    case 2:
    {}
        break;
    default:
        break;
    }*/
}


void ConfigForm::on_jisuan_clicked()
{
    QVector<int> backvec;
    QDateTime asdf=QDateTime::currentDateTime();
    MapToMapManage::GetInstance()->findLujing(ui->begin->text().toInt(), ui->end->text().toInt(), backvec);
    qDebug()<<"ConfigForm::on_jisuan_clicked--"<<backvec<<" msec--"<<asdf.msecsTo(QDateTime::currentDateTime());
    ui->begin->clear();
    ui->end->clear();
}

