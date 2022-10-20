#include "tcpprotocoltrans.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <globalhead.h>

TcpProtocolTrans::TcpProtocolTrans()
{
}

bool TcpProtocolTrans::regStrToTcp(QByteArray &backArray, QString &lei, QString &name, QStringList &inMatch)
{
    bool flag=false;
    QJsonObject sendObj;
    sendObj.insert("Class",lei);
    sendObj.insert("Name",name);
    sendObj.insert("RegStr",inMatch[0]);
    sendObj.insert("ArraySize",inMatch.size()-1);
    QJsonArray strListArray;
    int Num=1;
    while (Num<inMatch.size()) {
        strListArray.append(inMatch[Num]);
        Num++;
        flag=true;
    }
    sendObj.insert("RegStrList",strListArray);
    QJsonDocument backdocu(sendObj);

    backArray.append('B');
    backArray.append('e');
    backArray.append('G');
    backArray.append('i');
    backArray.append('N');
    backArray.append('0');
    backArray.append('0');
    backArray.append('0');
    backArray.append(backdocu.toJson(QJsonDocument::Compact));
    globalCheck::int2Bytes(backArray.size()-8, backArray,5);
    return flag;
}


bool TcpProtocolTrans::tcpToRegStr(QByteArray &inStr, QList<QString>& backStr)
{
    bool flag=true;
    int Num=0;
    while (Num<inStr.size()) {
        //判断还剩多少字符需要拿到
        if(allStrSize-nowStrSize==0)//已经完整了一个
        {
            if(!strStart)
            {
                moreStr.append(inStr[Num]);
                if(moreStr.size()==8 && moreStr[0]=='B' && moreStr[1]=='e' && moreStr[2]=='G' && moreStr[3]=='i' && moreStr[4]=='N')
                {
                    strStart=true;
                    nowStrSize=0;
                    allStrSize=globalCheck::bytes2Int(moreStr,5);
                    moreStr.clear();
                }
                else
                {
                    flag=false;
                }
            }
        }
        else
        {
            moreStr.append(inStr[Num]);
            nowStrSize++;
            if(allStrSize-nowStrSize==0)//已经完整了一个
            {
                if(strStart)
                {
                    //将获得的数组解析 须填
                    backStr.push_back(moreStr);
                    //清空
                    moreStr.clear();
                    strStart=false;
                }
            }
        }
        Num++;
    }
    return flag;
}
