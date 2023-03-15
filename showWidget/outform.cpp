#include "outform.h"
#include "ui_outform.h"
#include <QDebug>

OutForm::OutForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OutForm)
{
    ui->setupUi(this);
}

OutForm::~OutForm()
{
    //qDebug()<<"OutForm::~OutForm()";
    delete ui;
}

void OutForm::initWidget(QString comeRoom, QString roomName, QString outLe, QString cmdLe)
{
    ui->comeRoom->setText(comeRoom);
    ui->roomName->setText(roomName);
    ui->out->setText(outLe);
    ui->cmd->setText(cmdLe);
}

void OutForm::getWidget(QString &comeRoom, QString &roomName, QString &outLe, QString &cmdLe)
{
    comeRoom=ui->comeRoom->text();
    roomName=ui->roomName->text();
    outLe=ui->out->text();
    cmdLe=ui->cmd->text();
}
