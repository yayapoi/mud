#include "cmdcontrol.h"
#include <QDebug>
#include <globalhead.h>

CmdControl::CmdControl(QObject *parent)
    : QObject{parent}
{
    connect(&cmdTimer,&QTimer::timeout,[&](){
        sendmessage++;
        if(sendmessage>360000)
        {
            queueList.enqueue("say 2");
        }
        doqueueList();
    });
    cmdTimer.start(5);
}

void CmdControl::appendMessage(QString inStr)//须填 ;;->;
{
    //qDebug()<<"CmdControl::appendMessage  inStr--"<<inStr;
    int oldindex=0;
    int index=0;
    ///现在句子里有很多括号，要知道现在括号已经到哪里了
    int kuohaoend=0;
    while (index<inStr.length()) {
        //系统使用了 ";"，用户使用 ";"时自动替换为";;"
        index=backStringIndex(inStr,oldindex,kuohaoend);
        if(index!=-1)
        {
            QString appendStr=inStr.mid(oldindex,index-oldindex);
            //qDebug()<<"index!=-1  --"<<appendStr;
            QString backStr;
            bool flag=getMessageFrom(appendStr, backStr);
            if(flag==true)
            {
                appendMessage(backStr);
            }
            else
            {
                //去除最前方空格
                clearBlok(appendStr);
                queueList.enqueue(appendStr);
                doqueueList();
            }
        }
        else
        {
            QString appendStr=inStr.mid(oldindex);
            //qDebug()<<"index==-1 --"<<appendStr;
            QString backStr;
            bool flag=getMessageFrom(appendStr, backStr);
            if(flag==true)
            {
                appendMessage(backStr);
            }
            else
            {
                //去除最前方空格
                clearBlok(appendStr);
                queueList.enqueue(appendStr);
                doqueueList();
            }
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
    doqueueList();
    //qDebug()<<"CmdControl::appendMessageFront  queueList--"<<queueList;
}

void CmdControl::appendMessage(QString inStr, QStringList &backList)
{
    int oldindex=0;
    int index=0;
    ///现在句子里有很多括号，要知道现在括号已经到哪里了
    int kuohaoend=0;
    while (index<inStr.length()) {
        //index=inStr.indexOf(";",oldindex);//系统使用了 ";"，用户使用 ";"时自动替换为";;"
        index=backStringIndex(inStr,oldindex,kuohaoend);
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
            {
                //去除最前方空格
                clearBlok(appendStr);
                backList.append(appendStr);
            }
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
            {
                //去除最前方空格
                clearBlok(appendStr);
                backList.append(appendStr);
            }
            index=inStr.length();
        }
        oldindex=index=index+1;
    }
}

bool CmdControl::getMessageFrom(QString& inStr, QString& backStr)//须填  宏定义
{
    bool flag=false;
    /*if(inStr=="123")
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
    }*/
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
    //qDebug()<<"CmdControl::checkMessage--"<<instr;
    int flag=-1;
    if(globalCheck::checkTimer(instr))
    {
        flag=1;
        queueList.dequeue();
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
    if(flag==-1)
    {
        if(globalCheck::checkPause(instr))
        {
            flag=0;
        }
    }
    if(flag==-1)
    {
        if(globalCheck::checkMoveRoom(instr))
        {
            flag=0;
        }
    }
    if(flag==-1)
    {
        if(globalCheck::checkMoveGMCP(instr))
        {
            flag=0;
        }
    }
    if(flag==-1)
    {
        if(globalCheck::checkKillNpc(instr))
        {
            flag=0;
        }
    }
    if(flag==-1)
    {
        if(globalCheck::checkPritf(instr))
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
        if(globalCheck::checkDeleteReg(instr))
        {
            flag=0;
        }
    }
    if(flag==-1)
    {
        if(globalCheck::checkNewReg(instr))
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
        if(globalCheck::checkPath(instr))
        {
            flag=0;
        }
    }
    if(flag==-1)
    {
        if(globalCheck::checkWalk(instr))
        {
            flag=0;
        }
    }
    return flag;
}

int CmdControl::backStringIndex(QString &instr, int &from, int &kuohaoend)
{
    //#Timer(3000,"say 1;say 2;say 3");
    //#Timer(2000,"say 1;#Timer(3000,"say 1;say 2;say 3");say 3");
    int backint=-1;
    //左括号还有几个没匹配,发现一个右括号，此值减一。一个左括号，此值加一
    int kuohaovalue=0;
    //qDebug()<<"kuohaoend---"<<kuohaoend;
    int kuohaocunzai=instr.indexOf("(",kuohaoend);
    if(kuohaocunzai!=-1)
    {
        kuohaovalue++;
        backint=instr.indexOf(";",from);
        //比较左括号是否在;之前之后
        if(kuohaocunzai<backint)//左括号在;之前
        {
            kuohaoend=kuohaocunzai+1;
            //qDebug()<<"reset kuohaoend---"<<kuohaoend;
            for(;kuohaoend<instr.length(); kuohaoend++)
            {
                //qDebug()<<"kuohaovalue--"<<kuohaoend<<"   .at(kuohaovalue)---"<<instr.at(kuohaoend);
                if(kuohaovalue==0)
                {
                    break;
                }
                else
                {
                    if(instr.at(kuohaoend)=="(")
                    {
                        kuohaovalue++;
                    }
                    else if(instr.at(kuohaoend)==")")
                    {
                        kuohaovalue--;
                    }
                }
            }
            backint=instr.indexOf(";",kuohaoend);
        }
        //左括号在;之后,那backint就正常返回
    }
    else
    {
        kuohaoend=instr.length();
        //就没有左括号，那就直接查句子
        backint=instr.indexOf(";",from);
    }
    return backint;
}

void CmdControl::clearBlok(QString &instr)
{
    for(int num=0; num<instr.size(); num++)
    {
        if(instr[num]!=' ')
        {
            if(num!=0)
            {
                instr.remove(0,num);
            }
            break;
        }
    }
}

void CmdControl::doqueueList()
{
    if(!queueList.isEmpty())
    {
        sendmessage=0;
        QQueue<QString> backMessageList;
        messageToList(backMessageList);
        //qDebug()<<"backMessageList--"<<backMessageList;
        if(!backMessageList.isEmpty())
        {
            emit newMessage(backMessageList);
        }
    }
}

void CmdControl::appendMessage(QStringList inlist)
{
    while(!inlist.isEmpty()){
        appendMessage(inlist.first());
        inlist.pop_front();
    }
}
