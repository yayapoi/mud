#ifndef TCPSERVERCONTROL_H
#define TCPSERVERCONTROL_H

#include <QTcpServer>
#include <tcpControl/tcpconnect.h>

class TcpServerControl : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServerControl(QObject *parent = nullptr);
    virtual ~TcpServerControl();

signals:
    void connectClient(const int , const QString & ,const quint16 );//发送新用户连接信息
    void sockDisConnect(const int ,const QString &,const quint16 );//断开连接的用户信息
public slots:
    void sockDisConnectSlot(int handle, QString ip, quint16 prot);//断开连接的用户信息
    /* @brief 要发的内容*/
    void getSendMessage(int port, QString lei, QString name, QStringList regList);
signals:
    /* @brief 从tcp中获取命令*/
    void getMessage(QList<QString>);
    /* @brief 要发的内容*/
    void sendMessage(int port, QString lei, QString name, QStringList regList);
protected:
    void incomingConnection(qintptr socketDescriptor) override;//覆盖已获取多线程
private:
    QMap<int, TcpConnect*> tcpClient;
};

#endif // TCPSERVERCONTROL_H
