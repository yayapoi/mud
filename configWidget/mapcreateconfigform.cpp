#include "mapcreateconfigform.h"
#include "ui_mapcreateconfigform.h"
#include "globalhead.h"

MapCreateConfigForm::MapCreateConfigForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapCreateConfigForm)
{
    ui->setupUi(this);
}

MapCreateConfigForm::~MapCreateConfigForm()
{
    delete ui;
}

void MapCreateConfigForm::on_timeCB_toggled(bool checked)
{
    longOrShortTime=checked;
}

