#include "npcform.h"
#include "ui_npcform.h"
#include <QDebug>

NPCForm::NPCForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NPCForm)
{
    ui->setupUi(this);
}

NPCForm::~NPCForm()
{
    qDebug()<<"NPCForm::~NPCForm()";
    delete ui;
}

void NPCForm::initWidget(QString title, QString nameZH, QString nameEn)
{
    ui->title->setText(title);
    ui->nameZH->setText(nameZH);
    ui->nameEN->setText(nameEn);
}

void NPCForm::getWidget(QString &title, QString &nameZH, QString &nameEn)
{
    title=ui->title->text();
    nameZH=ui->nameZH->text();
    nameEn=ui->nameEN->text();
}

void NPCForm::on_deletBT_clicked()
{
    emit deleteNpc(this);
}

