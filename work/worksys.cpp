#include "worksys.h"
#include "qdebug.h"
#include <globalhead.h>
#include <QTime>

WorkSys* WorkSys::m_pipe_rw = nullptr;
WorkSys::GC WorkSys::gc;

void WorkSys::startWalk()
{
    workend=false;
    working=true;
    emit workPritf("----开始行走----");
    walktimer.start(170);
    dowork();
}

void WorkSys::Walk()
{
    //qDebug()<<QTime::currentTime().toString("mm:ss zzz:")<<"WorkSys::moveStatus Walk--";
    emit workPritf("----继续行走----");
    if(workend)
    {
        emit workPritf("----没有路径可执行----");
    }
    else
    {
        working=true;
        walktimer.start(170);
        dowork();
    }
}

void WorkSys::stopWalk()
{
    //qDebug()<<QTime::currentTime().toString("mm:ss zzz:")<<"WorkSys::moveStatus stopWalk--";
    if(workend)
    {
        emit workPritf("----没有行走中路径----");
    }
    else
    {
        working=false;
        walktimer.stop();
        emit workPritf("----停止行走----");
    }
}

void WorkSys::moveStatus(bool flag)
{
    //qDebug()<<QTime::currentTime().toString("mm:ss zzz:")<<"WorkSys::moveStatus flag--"<<flag;
    moveSuccess=flag;
    //失败马上重走本房间命令;
    if(!flag)
    {
        cmdnum=cmdnum-1;
        walktimer.stop();
        dowork();
    }
    else
    {
        if(!workend && working && !walktimer.isActive())
        {
            walktimer.start(170);
        }
    }
}

void WorkSys::busyStatus(bool flag)
{
    //暂时不管busy的事
    //qDebug()<<QTime::currentTime().toString("mm:ss zzz:")<<"WorkSys::busyStatus flag--"<<flag;
    busy=flag;
    if(!flag && !workend && working && !walktimer.isActive())
    {
        //qDebug()<<QTime::currentTime().toString("mm:ss zzz:")<<"busyed--";
        walktimer.start(170);
        dowork();
    }
}

void WorkSys::clearOldPath()
{
    pathList.clear();
    walktimer.stop();
    working=true;
    workend=true;
    listnow=-1;
    cmdnum=-1;
    busy=false;
    moveSuccess=true;
    emit workPritf("----清空上次路径----");
}

void WorkSys::releasepareCmd(QString pathAll, bool addCmd)
{
    emit workPritf("----解析房间对路径----");
    pathList.clear();
    int beginNum=0;
    roomStruct newstructr;
    int num=0;
    bool find=false;
    int beginLeft=0,endleft=0;
    bool kouhaoExit=findkuohao(pathAll,num,beginLeft,endleft);
    for(; num<pathAll.size(); num++)
    {
        if(kouhaoExit && num>=beginLeft)
        {
            num=endleft;
            kouhaoExit=findkuohao(pathAll,num+1,beginLeft,endleft);
        }
        if(pathAll[num]==":")
        {
            newstructr.clear();
            newstructr.roomNameZH=pathAll.mid(beginNum,num-beginNum);
            //qDebug()<<"roomNameZH--"<<newstructr.roomNameZH<<" beginNum--"<<beginNum<<" num-beginNum--"<<num-beginNum;
            beginNum=num+1;
            find=true;
        }
        if(pathAll[num]=="&")
        {
            if(find)
            {
                newstructr.cmd=pathAll.mid(beginNum,num-beginNum);
                //qDebug()<<"roomNameZH--"<<newstructr.roomNameZH<<" beginNum--"<<beginNum<<" num-beginNum--"<<num-beginNum;
                beginNum=num+1;
                pathList.append(newstructr);
                find=false;
            }
        }
    }
    if(beginNum<pathAll.size() && find)
    {
        newstructr.cmd=pathAll.mid(beginNum,num-beginNum);
        beginNum=num+1;
        pathList.append(newstructr);
        find=false;
    }
    /*for(int num=0; num<pathList.size(); num++)
    {
//qDebug()<<"roomNameZH--"<<pathList[num].roomNameZH<<" list--"<<pathList[num].cmd;
    }*/
    releaseList(addCmd);
    startWalk();
}

void WorkSys::releaseCmd(QString pathAll,bool addCmd)
{
    emit workPritf("----解析无房间路径----");
    QRegularExpressionMatch regularmatch=pathRegStr.match(pathAll);
    if(regularmatch.hasMatch())
    {
        QStringList backList=regularmatch.capturedTexts();
        if(backList.size()>=2)
        {
            pathList.clear();
            roomStruct newstructr;
            newstructr.roomNameZH="测试试试";
            newstructr.cmd=backList[1];
            pathList.append(newstructr);
            releaseList(addCmd);
            startWalk();
        }
    }
    else
    {
        emit workPritf("----解析无房间路径失败----");
    }
}

void WorkSys::releaseList(bool addCmd)
{
    for(int num=0; num<pathList.size(); num++)
    {
        pathList[num].cmd.split(";");
        pathList[num].releaseCmd.clear();
        appendMessage(pathList[num].cmd, pathList[num].releaseCmd, num, addCmd);
    }
    for(int num=0; num<pathList.size(); num++)
    {
        //qDebug()<<"num--"<<QString::number(num)<<" list--"<<pathList[num].releaseCmd;
    }
}

void WorkSys::appendMessage(QString inStr, QStringList &backList, int &nownum, bool addCmd)
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
                appendMessage(backStr, backList, nownum, addCmd);
            }
            else
            {
                if(addCmd)
                {
                    QString backfunStr;
                    bool flag=getfunFrom(appendStr, backfunStr, nownum);
                    if(flag==true)
                    {
                        appendMessage(backfunStr, backList, nownum, false);
                    }
                    else
                    {
                        //去除最前方空格
                        clearBlok(appendStr);
                        if(appendStr.size()>0)
                        {
                            backList.append(appendStr);
                        }
                    }
                }
                else
                {
                    //去除最前方空格
                    clearBlok(appendStr);
                    if(appendStr.size()>0)
                    {
                        backList.append(appendStr);
                    }
                }
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
                appendMessage(backStr, backList, nownum, addCmd);
            }
            else
            {
                if(addCmd)
                {
                    QString backfunStr;
                    bool flag=getfunFrom(appendStr, backfunStr, nownum);
                    if(flag==true)
                    {
                        appendMessage(backfunStr, backList, nownum, false);
                    }
                    else
                    {
                        //去除最前方空格
                        clearBlok(appendStr);
                        if(appendStr.size()>0)
                        {
                            backList.append(appendStr);
                        }
                    }
                }
                else
                {
                    //去除最前方空格
                    clearBlok(appendStr);
                    if(appendStr.size()>0)
                    {
                        backList.append(appendStr);
                    }
                }
            }
            index=inStr.length();
        }
        oldindex=index=index+1;
    }
}

int WorkSys::backStringIndex(QString &instr, int &from, int &kuohaoend)
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

bool WorkSys::getMessageFrom(QString &inStr, QString &backStr)//须填  宏定义
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

bool WorkSys::getfunFrom(QString &inStr, QString &backStr, int &nownum)
{
    bool flag=false;
    if(inStr.indexOf("#killNpc(")!=-1)
    {
        if(killNpc!=nullptr)
        {
            char* beginchar=(char *)malloc(1000*sizeof(char));
            char* endchar=(char *)malloc(1000*sizeof(char));
            bool backBool=killNpc(pathList[nownum].roomNameZH.toUtf8().data(), beginchar, endchar);
            if(backBool)
            {
                if(strlen(beginchar)>0)
                {
                    backStr=QString::fromUtf8(beginchar)+";";
                }
                backStr=backStr+inStr+";";
                if(strlen(endchar)>0)
                {
                    backStr=backStr+QString::fromUtf8(endchar)+";";
                }
                flag=true;
                //qDebug()<<"backBool--"<<backBool;
                //qDebug()<<"beginchar leg--"<<strlen(beginchar);
                //qDebug()<<"fromUtf8--"<<QString::fromUtf8(beginchar);
                //qDebug()<<"fromLatin1--"<<QString::fromLatin1(beginchar);
                //qDebug()<<"endchar leg--"<<strlen(endchar);
                //qDebug()<<"fromUtf8--"<<QString::fromUtf8(endchar);
                //qDebug()<<"fromLatin1--"<<QString::fromLatin1(endchar);
                //qDebug()<<"backStr--"<<backStr;
            }
        }
        else
        {
            //qDebug()<<"WorkSys::getfunFrom   killNpc==nullptr";
        }
    }
    return flag;
}

void WorkSys::clearBlok(QString &instr)
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

bool WorkSys::findkuohao(QString &instr, int fromNum, int &begin, int &end)
{
    bool findkuohao=false;
    if(fromNum<instr)
    {
        int num=fromNum;
        int kuohaonum=0;
        for(; num<instr.size(); num++)
        {
            if(instr[num]=="(")
            {
                if(findkuohao==false)
                {
                    begin=num;
                }
                findkuohao=true;
                kuohaonum++;
            }
            if(instr[num]==")")
            {
                kuohaonum--;
            }
            if(findkuohao && kuohaonum==0)
            {
                end=num;
                break;
            }
        }
    }
    return findkuohao;
}

bool WorkSys::endproomList(int listNum, int cmdNum)
{
    bool backbool=true;
    if(pathList.size()>listNum)
    {
        if(pathList[listNum].releaseCmd.size()>cmdNum)
        {
            backbool=false;
        }
    }
    return backbool;
}

void WorkSys::dowork()
{
    int newlistnow=listnow;
    int newcmdnum=cmdnum;
    if(listnow!=-1)
    {
        if(cmdnum!=-1)//不用从头走
        {
            newcmdnum=cmdnum+1;
        }
        else//用从头走
        {
            newcmdnum=0;
        }
    }
    else//路径第一步
    {
        newlistnow=0;
        newcmdnum=0;
    }
    if(endproomList(newlistnow,newcmdnum))//这个房间命令是否到底了
    {
        newlistnow=newlistnow+1;
        newcmdnum=0;
        if(endpathList(newlistnow))//路径也到底了，停止行走
        {
            //qDebug()<<QTime::currentTime().toString("mm:ss zzz:")<<"work end--";
            clearOldPath();
            emit workPritf("----路径完成----");
        }
    }
    if(!workend)//上面可能算出路径走完了
    {
        //执行命令  可能自己打断自己
        for(;newcmdnum<pathList[newlistnow].releaseCmd.size(); newcmdnum++)//一个房间
        {
            if(working)
            {
                listnow=newlistnow;
                cmdnum=newcmdnum;
                //干活
                //qDebug()<<QTime::currentTime().toString("mm:ss zzz:")<<"cmd--"<<pathList[newlistnow].releaseCmd[newcmdnum];
                QString fangxiangback=outjianhua(pathList[newlistnow].releaseCmd[newcmdnum]);
                if(fangxiangback!="特殊方向")//是方向，则暂停
                {
                    moveSuccess=false;
                    if(pathList[newlistnow].stopnum==-1)
                    {
                        //qDebug()<<QTime::currentTime().toString("mm:ss zzz:")<<"stopnum==-1";
                        pathList[newlistnow].stopnum=newcmdnum;
                        emit cmdroom(pathList[newlistnow].roomNameZH, pathList[newlistnow].releaseCmd[newcmdnum]);
                        break;
                    }
                    else
                    {
                        if(pathList[newlistnow].stopnum<=newcmdnum)//
                        {
                            //qDebug()<<QTime::currentTime().toString("mm:ss zzz:")<<"stopnum--"<<pathList[newlistnow].stopnum<<"newcmdnum--"<<newcmdnum;
                            pathList[newlistnow].stopnum=newcmdnum;
                            emit cmdroom(pathList[newlistnow].roomNameZH, pathList[newlistnow].releaseCmd[newcmdnum]);
                            break;
                        }
                    }
                }
                emit cmdroom(pathList[newlistnow].roomNameZH, pathList[newlistnow].releaseCmd[newcmdnum]);
                //假如命令是行走命令，则要下面命令等待  不出意外，一个房间应该命令list执行完毕 须填
                //若没有看出来命令，则本房间命令执行完毕停止
                //qDebug()<<QTime::currentTime().toString("mm:ss zzz:")<<"不等待";
            }
            else
            {
                walktimer.stop();
                break;
            }
        }
    }
}

bool WorkSys::endpathList(int listNum)
{
    bool backbool=true;
    if(pathList.size()>listNum)
    {
        backbool=false;
    }
    return backbool;
}

WorkSys::WorkSys(QObject *parent)
    : QObject{parent}
{
    connect(&walktimer,&QTimer::timeout,this,[this](){
        if(moveSuccess)
        {
            if(busy)//busy中，停止时间，等待busy启动命令
            {
                walktimer.stop();
            }
            else
            {
                if(working)
                {
                    dowork();
                }
                else
                {
                    walktimer.stop();
                }
            }
        }
        else//时间到了但是没有move成功，本房间从上条命令走 没有触发移动失败机制
        {
            /*cmdnum=cmdnum-1;
            if(busy)//busy中，停止时间，等待busy启动命令
            {
                walktimer.stop();
            }
            else
            {
                if(working)
                {
                    dowork();
                }
                else
                {
                    walktimer.stop();
                }
            }*/
        }
    });
}
