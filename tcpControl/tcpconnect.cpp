#include "tcpconnect.h"

TcpConnect::TcpConnect(QObject *parent)
    : QObject{parent}
{

}

TcpConnect::~TcpConnect()
{
    if(tcpSocket!=nullptr)
    {
        //客户端断开连接
        tcpSocket->close();
    }
    if(privateTrans!=nullptr)
    {
        delete privateTrans;
    }
}

void TcpConnect::connectToHost(QHostAddress &address, quint16 port)
{
    privateTrans=new TcpProtocolTrans();
    tcpSocket=new QTcpSocket(this);
    tcpSocket->connectToHost(address,port);
    //连接成功就会触发connected信号
    connect(tcpSocket,&QTcpSocket::connected,[&]()
    {});
    //对方有数据传来就会触发readyRead信号
    connect(tcpSocket,&QTcpSocket::readyRead,[&]()
    {
        QByteArray inStr=tcpSocket->readAll();
        QList<QString> backList;
        privateTrans->tcpToRegStr(inStr, backList);
        if(!backList.empty())
        {
            emit getMessage(backList);
        }
    });
    //双方断开连接后就会触发disconnected信号
    connect(tcpSocket,&QTcpSocket::disconnected,[&]()
    {});
}

void TcpConnect::sendMessage(QString lei, QString name, QStringList regList)
{
    QByteArray backStr;
    privateTrans->regStrToTcp(backStr, lei, name, regList);
    tcpSocket->write(backStr);
    tcpSocket->flush();
}
