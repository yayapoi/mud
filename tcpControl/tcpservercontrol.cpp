#include "tcpservercontrol.h"
#include <QThread>

TcpServerControl::TcpServerControl(QObject *parent)
    : QTcpServer{parent}
{

}

TcpServerControl::~TcpServerControl()
{

}

void TcpServerControl::sockDisConnectSlot(int handle, QString ip, quint16 prot)
{
    tcpClient.remove(prot);
    emit sockDisConnect(handle, ip, prot);
}

void TcpServerControl::getSendMessage(int port, QString lei, QString name, QStringList regList)
{
    emit sendMessage(port, lei, name, regList);
}

void TcpServerControl::incomingConnection(qintptr socketDescriptor)
{
    TcpConnect * tcpTemp = new TcpConnect(socketDescriptor);
    QThread * thread = new QThread();//把线程的父类设为连接的，防止内存泄漏
    //可以信号连接信号的，我要捕捉线程ID就独立出来函数了，使用中还是直接连接信号效率应该有优势
    connect(tcpTemp,&TcpConnect::getMessage,this,&TcpServerControl::getMessage);//接受到数据
    connect(tcpTemp,&TcpConnect::sockDisConnect,this,&TcpServerControl::sockDisConnectSlot);//断开连接的处理，从列表移除，并释放断开的Tcpsocket
    connect(tcpTemp,&TcpConnect::sockDisConnect,thread,&QThread::quit);//断开连接时线程退出
    connect(this,&TcpServerControl::sendMessage,tcpTemp,&TcpConnect::sendMessage);//发送数据
    connect(thread,&QThread::finished,tcpTemp,&QObject::deleteLater);
    connect(thread,&QThread::started,tcpTemp,&TcpConnect::connectToHost);
    tcpTemp->moveToThread(thread);//把tcp类移动到新的线程
    thread->start();//线程开始运行

    tcpClient.insert(tcpTemp->peerPort(),tcpTemp);//插入到连接信息中
    //qDebug() <<"incomingConnection THREAD IS：" <<QThread::currentThreadId();
    //发送连接信号
    emit connectClient(tcpTemp->socketDescriptor(),tcpTemp->peerAddress().toString(),tcpTemp->peerPort());
}
