#include "configform.h"
#include "ui_configform.h"

ConfigForm::ConfigForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigForm)
{
    ui->setupUi(this);
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
    emit closeWidget();
    close();
}

