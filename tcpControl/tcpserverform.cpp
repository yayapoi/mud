#include "tcpserverform.h"
#include "ui_tcpserverform.h"

TcpServerForm::TcpServerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpServerForm)
{
    ui->setupUi(this);
    ui->listenPortLE->setValidator(new QRegExpValidator(QRegExp("[1-9][0-9]{0,4}"), this));
    ui->listenPortBT->setCheckable(true);
    connect(&tcpServerControl,&TcpServerControl::connectClient,[&](int , QString ip, quint16 newport){
        //qDebug()<<"TcpServerForm::connectClient ip--"<<ip<<"  newport--"<<newport;
        ui->portListWidget->addItem(QString::number(newport));
    });
    connect(&tcpServerControl,&TcpServerControl::sockDisConnect,[&](int , QString ip, quint16 newport){
        //qDebug()<<"TcpServerForm::sockDisConnect ip--"<<ip<<"  newport--"<<newport;
        QList<QListWidgetItem *> asdf=ui->portListWidget->findItems(QString::number(newport),Qt::MatchFixedString);
        for(auto oneItem:asdf)
        {
            ui->portListWidget->removeItemWidget(oneItem);
            delete oneItem;
        }
    });
}

TcpServerForm::~TcpServerForm()
{
    delete ui;
}

void TcpServerForm::on_listenPortBT_clicked(bool checked)
{
    if(checked)
    {
        bool flag=tcpServerControl.listen(QHostAddress::LocalHost,ui->listenPortLE->text().toInt());
        if(!flag)
        {
            ui->listenPortBT->setChecked(false);
        }
    }
    else
    {
        tcpServerControl.close();
    }
}

