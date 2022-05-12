#ifndef TCPPROTOCOLTRANS_H
#define TCPPROTOCOLTRANS_H

#include <QString>

class TcpProtocolTrans
{
public:
    TcpProtocolTrans();

    /* @brief 将触发信息组装成tcp信息发出 类 名字 触发信息 每条结果*/
    bool regStrToTcp(QByteArray&, QString& lei, QString& name);

    /* @brief 将tcp信息转化为命令*/
    QString tcpToRegStr(QByteArray&);
private:
    /* @brief 存未完的字符串*/
    QByteArray moreStr;
    /* @brief 字符串最大值*/
    int allStrSize=0;
    /* @brief 已获得长度*/
    int nowStrSize=0;
    /* @brief 当为true时，向数组中填充*/
    bool strStart=false;
};

#endif // TCPPROTOCOLTRANS_H
