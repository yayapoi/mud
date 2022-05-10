#include "cmdcontrol.h"
#include <QDebug>
#include <globalhead.h>

CmdControl::CmdControl(QObject *parent)
    : QObject{parent}
{
    connect(&cmdTimer,&QTimer::timeout,[&](){
        if(!queueList.isEmpty())
        {
            QQueue<QString> backMessageList;
            messageToList(backMessageList);
            //qDebug()<<"backMessageList--"<<backMessageList;
            emit newMessage(backMessageList);
        }
    });
    cmdTimer.start(20);
}

void CmdControl::appendMessage(QString inStr)//须填 ;;->;
{
    int oldindex=0;
    int index=0;
    while (index<inStr.length()) {
        index=inStr.indexOf(";",oldindex);//系统使用了 ";"，用户使用 ";"时自动替换为";;"
        if(index!=-1)
        {
            QString appendStr=inStr.mid(oldindex,index-oldindex);
            //qDebug()<<"--"<<appendStr;
            QString backStr;
            bool flag=getMessageFrom(appendStr, backStr);
            if(flag==true)
            {
                appendMessage(backStr);
            }
            else
                queueList.enqueue(appendStr);
        }
        else
        {
            QString appendStr=inStr.mid(oldindex);
            //qDebug()<<"--"<<appendStr;
            QString backStr;
            bool flag=getMessageFrom(appendStr, backStr);
            if(flag==true)
            {
                appendMessage(backStr);
            }
            else
                queueList.enqueue(appendStr);
            index=inStr.length();
        }
        oldindex=index=index+1;
    }
}

void CmdControl::appendMessage(QByteArray inarray)
{
    appendMessage(QString(inarray));
}

bool CmdControl::getMessageFrom(QString& inStr, QString& backStr)//须填  宏定义
{
    bool flag=false;
    if(inStr=="123")
    {
        backStr="12 12 12;12 12 12";
        flag=true;
    }
    else if(inStr=="456")
    {
        backStr="000";
        flag=true;
    }
    else if(inStr=="12 12 12")
    {
        backStr="13 13 13";
        flag=true;
    }
    return flag;
}

void CmdControl::messageToList(QQueue<QString> &backList)
{
    QString backstr=queueList.dequeue();
    backList.append(backstr);
    while (true) {
        if(!queueList.isEmpty())
        {
            QString backstr=queueList.first();
            if(checkMessage(backstr))
            {
                queueList.dequeue();
                backList.append(backstr);
            }
            else
            {
                break;
            }
        }
        else
            break;
    }
}

bool CmdControl::checkMessage(QString &instr)
{
    bool flag=false;
    flag?true:flag=globalCheck::checkNewReg(instr);
    flag?true:flag=globalCheck::checkDeleteReg(instr);
    flag?true:flag=globalCheck::checkEnableRegReg(instr);
    flag?true:flag=globalCheck::checkSetHPBar(instr);
    return flag;
}

void CmdControl::appendMessage(QStringList inlist)
{
    while(!inlist.isEmpty()){
        appendMessage(inlist.first());
        inlist.pop_front();
    }
}
