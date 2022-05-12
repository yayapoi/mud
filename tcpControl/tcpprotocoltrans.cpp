#include "tcpprotocoltrans.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

TcpProtocolTrans::TcpProtocolTrans()
{
    moreStr.append('B');
    moreStr.append('e');
    moreStr.append('G');
    moreStr.append('i');
    moreStr.append('N');
    moreStr.append('0');
    moreStr.append('0');
    qDebug()<<""<<moreStr;
}

bool TcpProtocolTrans::regStrToTcp(QByteArray &backArray, QString &lei, QString &name)
{
    bool flag=false;
    QJsonObject sendObj;
    sendObj.insert("Class",lei);
    sendObj.insert("Name",name);
    sendObj.insert("RegStr",name);
    sendObj.insert("ArraySize",3);
    QJsonArray strListArray;
    while (true) {
        strListArray.append("");
        flag=true;
    }
    sendObj.insert("",strListArray);
    QJsonDocument backdocu(sendObj);
    backArray=backdocu.toJson(QJsonDocument::Compact);
    return flag;
}

QString TcpProtocolTrans::tcpToRegStr(QByteArray &inStr)
{
    //判断还剩多少字符需要拿到
    /*if(allStrSize-nowStrSize==0)//已经完整了一个
    {
        //将最开始的
    }
    else
    {
        d
    }*/
}
