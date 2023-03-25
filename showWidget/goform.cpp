#include "goform.h"
#include "ui_goform.h"
#include <QDebug>

GoForm::GoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GoForm)
{
    ui->setupUi(this);
    ui->outCombox->addItem("w");
    ui->outCombox->addItem("wu");
    ui->outCombox->addItem("wd");
    ui->outCombox->addItem("n");
    ui->outCombox->addItem("nu");
    ui->outCombox->addItem("nd");
    ui->outCombox->addItem("nw");
    ui->outCombox->addItem("ne");
    ui->outCombox->addItem("s");
    ui->outCombox->addItem("su");
    ui->outCombox->addItem("sd");
    ui->outCombox->addItem("sw");
    ui->outCombox->addItem("se");
    ui->outCombox->addItem("e");
    ui->outCombox->addItem("eu");
    ui->outCombox->addItem("ed");
    ui->outCombox->addItem("u");
    ui->outCombox->addItem("d");
    ui->outCombox->addItem("enter");
    ui->outCombox->addItem("out");
    ui->outCombox->addItem("特殊方向");
}

GoForm::~GoForm()
{
    //qDebug()<<"GoForm::~GoForm()";
    delete ui;
}

void GoForm::initWidget(QString outCB, QString cmd, QString time, QString room, bool longtime)
{
    if(cmd=="")
    {
        ui->outCombox->setCurrentText(outCB);
        ui->time->setText(time);
        ui->room->setText(room);
        ui->longtimeCB->setChecked(longtime);
    }
    else
    {
        ui->outCombox->setCurrentText(outCB);
        ui->cmd->setText(cmd);
        ui->time->setText(time);
        ui->room->setText(room);
        ui->longtimeCB->setChecked(longtime);
    }
}

void GoForm::getWidget(QString &outCB, QString &cmd, QString &time, QString &room, bool &longtime)
{
    cmd=ui->cmd->text();
    outCB=ui->outCombox->currentText();
    time=ui->time->text();
    room=ui->room->text();
    longtime=ui->longtimeCB->isChecked();
}

void GoForm::setRoomWidget(QString room2)
{
    ui->room->setText(room2);
}

void GoForm::setRoomTime(QString time1)
{
    ui->time->setText(time1);
}

void GoForm::on_deleteRoom_clicked()
{
    emit deleteGo(this);
}


void GoForm::on_go_clicked()
{
    emit GoFormGo(this);
}


void GoForm::on_outCombox_currentTextChanged(const QString &arg1)
{
    ui->cmd->setText(arg1);
}

