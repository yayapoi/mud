#include "lurenui.h"
#include "ui_lurenui.h"

lurenUI::lurenUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lurenUI)
{
    ui->setupUi(this);
}

lurenUI::~lurenUI()
{
    delete ui;
}

void lurenUI::name(QString value)
{
    ui->mingzi->setText(value);
}

void lurenUI::nannv(QString value)
{
    ui->nannv->setText(value);
}

void lurenUI::nianling(QString value)
{
    ui->nianling->setText(value);
}

void lurenUI::gaodi(QString value)
{
    ui->gaoai->setText(value);
}

void lurenUI::feishou(QString value)
{
    ui->pangshou->setText(value);
}

void lurenUI::yifu(QString value)
{
    ui->yifu->setText(value);
}

void lurenUI::yifuyanse(QString value)
{
    ui->yifuyanse->setText(value);
}

void lurenUI::xiezi(QString value)
{
    ui->xiezi->setText(value);
}

void lurenUI::xieziyanse(QString value)
{
    ui->xieziyanse->setText(value);
}

void lurenUI::zhengci(QString value)
{
    ui->zhengci->setText(value);
}

void lurenUI::zhengjv(QString value)
{
    ui->zhengjv1->setText(value);
}

void lurenUI::alltext(QString value)
{
    ui->allText->setText(value);
}
