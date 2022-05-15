#include "tcpconnect.h"
#include <QHostAddress>
#include <QThread>

TcpConnect::TcpConnect(qintptr Descriptor, QObject *parent)
    : QObject{parent}, socketDescriptor11{Descriptor}
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

void TcpConnect::connectToHost()
{
    privateTrans=new TcpProtocolTrans();

    tcpSocket=new QTcpSocket(this);
    tcpSocket->setSocketDescriptor(socketDescriptor11);

    qDebug() << tcpSocket->socketDescriptor() << " " << tcpSocket->peerAddress().toString()
             << " " << tcpSocket->peerPort() << "myTcpSocket::myTcpSocket thread is " <<QThread::currentThreadId();

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
    {emit sockDisConnect(socketDescriptor11,"",thisPort);});
    thisPort=tcpSocket->peerPort();
}

QHostAddress TcpConnect::peerAddress()
{
    return tcpSocket->peerAddress();
}

QString TcpConnect::peerName()
{
    return tcpSocket->peerName();
}

quint16 TcpConnect::peerPort()
{
    return thisPort;
}

qintptr TcpConnect::socketDescriptor()
{
    return socketDescriptor11;
}

void TcpConnect::sendMessage(int socketPort, QString lei, QString name, QStringList regList)
{
    if(socketPort==thisPort)
    {
        QByteArray backStr;
        privateTrans->regStrToTcp(backStr, lei, name, regList);
        tcpSocket->write(backStr);
        tcpSocket->flush();
    }
}
