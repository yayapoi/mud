#include "cmdcontrol.h"
#include "qregularexpression.h"
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
            if(!backMessageList.isEmpty())
            {
                emit newMessage(backMessageList);
            }
        }
    });
    cmdTimer.start(30);
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

void CmdControl::appendMessageFront(QString inStr)
{
    QStringList appendList;
    //qDebug()<<"CmdControl::appendMessageFront  inStr--"<<inStr;
    appendMessage(inStr, appendList);
    //qDebug()<<"CmdControl::appendMessageFront  appendList--"<<appendList;
    while(!appendList.isEmpty())
    {
        QString incmd=appendList.takeLast();
        queueList.push_front(incmd);
        //qDebug()<<"CmdControl::appendMessageFront  queueList--"<<queueList;
    }
    //qDebug()<<"CmdControl::appendMessageFront  queueList--"<<queueList;
}

void CmdControl::appendMessage(QString inStr, QStringList &backList)
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
                appendMessage(backStr, backList);
            }
            else
                backList.append(appendStr);
        }
        else
        {
            QString appendStr=inStr.mid(oldindex);
            //qDebug()<<"--"<<appendStr;
            QString backStr;
            bool flag=getMessageFrom(appendStr, backStr);
            if(flag==true)
            {
                appendMessage(backStr, backList);
            }
            else
                backList.append(appendStr);
            index=inStr.length();
        }
        oldindex=index=index+1;
    }
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
    //QString backstr=queueList.dequeue();
    //backList.append(backstr);
    bool firstCmd=true;
    while (true) {
        if(!queueList.isEmpty())
        {
            QString backstr=queueList.first();
            int backInt=checkMessage(backstr);
            bool breakflag=false;
            //qDebug()<<"backInt--"<<backInt;
            switch (backInt) {
            case -1:
            {
                if(firstCmd)
                {
                    queueList.dequeue();
                    backList.append(backstr);
                    firstCmd=false;
                }
                else
                {
                    breakflag=true;
                }
                break;
            }
            case 0:
            {
                queueList.dequeue();
                backList.append(backstr);
                break;
            }
            case 1:
            {
                break;
            }
            }
            if(breakflag)
            {
                //qDebug()<<"break--";
                break;
            }
        }
        else
            break;
    }
}

int CmdControl::checkMessage(QString &instr)
{
    int flag=-1;
    if(globalCheck::checkNewReg(instr))
    {
        flag=0;
    }
    if(flag==-1)
    {
        if(globalCheck::checkDeleteReg(instr))
        {
            flag=0;
        }
    }
    if(flag==-1)
    {
        if(globalCheck::checkEnableRegReg(instr))
        {
            flag=0;
        }
    }
    if(flag==-1)
    {
        if(globalCheck::checkSetHPBar(instr))
        {
            flag=0;
        }
    }
    if(flag==-1)
    {
        if(globalCheck::checkTimer(instr))
        {
            flag=1;
            queueList.dequeue();
            QRegularExpression regStr("^#Timer\\((\\d+),\"([\\s\\S]*)\"\\)$");
            QRegularExpressionMatch regularmatch=regStr.match(instr, 0);
            if(regularmatch.hasMatch())
            {
                int timerInt=regularmatch.captured(1).toInt();
                if(timerInt>20)
                {
                    QTimer* justdo=new QTimer;
                    timerMap.insert(justdo,regularmatch.captured(2));
                    connect(justdo,&QTimer::timeout,this,[&](){
                        //qDebug()<<"sender--"<<sender();
                        QTimer* justdo=(QTimer*)sender();
                        justdo->stop();
                        if(timerMap.find(justdo)!=timerMap.end()){
                            QString backstr=timerMap.value(justdo);
                            //qDebug()<<"backstr--"<<backstr;
                            timerMap.remove(justdo);
                            justdo->deleteLater();
                            appendMessageFront(backstr);
                        }
                    });
                    justdo->start(timerInt);
                }
                else
                {
                    appendMessageFront(regularmatch.captured(2));
                }
                //qDebug()<<"checkStr--";
            }
        }
    }
    return flag;
}

void CmdControl::appendMessage(QStringList inlist)
{
    while(!inlist.isEmpty()){
        appendMessage(inlist.first());
        inlist.pop_front();
    }
}
