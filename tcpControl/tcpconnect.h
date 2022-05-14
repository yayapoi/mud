#ifndef TCPCONNECT_H
#define TCPCONNECT_H

#include <QObject>
#include <QTcpSocket>
#include "tcpprotocoltrans.h"

class TcpConnect : public QObject
{
    Q_OBJECT
public:
    explicit TcpConnect(QObject *parent = nullptr);
    ~TcpConnect();

    void connectToHost(QHostAddress &address, quint16 port);
public slots:
    /* @brief 要发的内容*/
    void sendMessage(QString lei, QString name, QStringList regList);
signals:
    /* @brief 从tcp中获取命令*/
    void getMessage(QList<QString>);
private:
    TcpProtocolTrans* privateTrans=nullptr;
    QTcpSocket* tcpSocket=nullptr;
};

#endif // TCPCONNECT_H
