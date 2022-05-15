#ifndef TCPCONNECT_H
#define TCPCONNECT_H

#include <QObject>
#include <QTcpSocket>
#include "tcpprotocoltrans.h"

class TcpConnect : public QObject
{
    Q_OBJECT
public:
    explicit TcpConnect(qintptr socketDescriptor,QObject *parent = nullptr);
    ~TcpConnect();

    QHostAddress peerAddress();
    QString peerName();
    quint16 peerPort();
    qintptr socketDescriptor();
public slots:
    /* @brief 要发的内容*/
    void sendMessage(int socketPort,QString lei, QString name, QStringList regList);
    /* @brief 线程开始后开始建立socket*/
    void connectToHost();
signals:
    /* @brief 从tcp中获取命令*/
    void getMessage(QList<QString>);
    void sockDisConnect(const int ,const QString &,const quint16 );//断开连接的用户信息
private:
    TcpProtocolTrans* privateTrans=nullptr;
    QTcpSocket* tcpSocket=nullptr;
    qintptr socketDescriptor11;//保存id，== tcpSocket->socketDescriptor()；但是tcpSocket->socketDescriptor()客户端断开会被释放，
    //断开信号用this->socketDescriptor()得不到正确值
    int thisPort=0;
};

#endif // TCPCONNECT_H
