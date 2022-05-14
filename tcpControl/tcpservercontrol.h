#ifndef TCPSERVERCONTROL_H
#define TCPSERVERCONTROL_H

#include <QObject>

class TcpServerControl : public QObject
{
    Q_OBJECT
public:
    explicit TcpServerControl(QObject *parent = nullptr);

signals:

};

#endif // TCPSERVERCONTROL_H
