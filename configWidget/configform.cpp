#include "configform.h"
#include "ui_configform.h"
#include <INI/inimanarge.h>

ConfigForm::ConfigForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigForm)
{
    ui->setupUi(this);
    UserNameGmcp backstruct;
    INIManarge::GetInstance()->getUserNameGmcp(backstruct);
    ui->nameLE->setText(backstruct.userName);
    ui->idLE->setText(backstruct.userEnName);
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
    emit closeWidget();
    close();
}

