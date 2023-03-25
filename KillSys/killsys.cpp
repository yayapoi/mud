#include "killsys.h"
#include "ZHToEN/zhtopy.h"
#include "globalhead.h"
#include "work/worksys.h"

KillSys* KillSys::m_pipe_rw = nullptr;
KillSys::GC KillSys::gc;

KillSys::KillSys(QObject *parent)
    : QObject{parent}
{

}

void KillSys::killNpcStart(QString str)
{
    //qDebug()<<"#killnpc()--";
    int lastint=str.lastIndexOf(")");
    if(lastint!=1)
    {
        wantkill=str.mid(9,lastint-9).toLower();
        killSysGetMes=true;
        wangkillNum=true;
        if(WorkSys::GetInstance()->working)
        {
            walkingStop=true;
            emit sysCmd("#pause;yun qi;yun powerup;killall "+wantkill);
        }
        else
        {
            emit sysCmd("yun qi;yun powerup;killall "+wantkill);
        }
    }
}

void KillSys::killmeStart(QString zhName, QString id)
{
    //qDebug()<<"KillSys::killmeStart  zhName--"<<zhName<<"   id--"<<id;
    int beginint=id.indexOf("#");
    if(beginint!=1)
    {
        QString ehname=id.mid(0,beginint).toLower();

        killnpcstruct asf;
        asf.enName=ehname;
        asf.zhName=zhName;
        asf.id=id;
        asf.fightStart=true;
        npcname.append(asf);
        killSysGetMes=true;
        if(ehname==wantkill)
        {
            //进入战斗，等会他死了还要叫杀一次，防止同名
            wangkillNum=false;
        }
        if(WorkSys::GetInstance()->working)
        {
            walkingStop=true;
            emit sysCmd("#pause");
        }
        else
        {
            emit sysCmd("");
        }
    }
}

void KillSys::fightCheck(QString zhName, QString id)
{
    bool findnpc=false;
    int numnum=0;
    for(;numnum<npcname.size();numnum++)
    {
        if(npcname[numnum].id==id)
        {
            findnpc=true;
            break;
        }
    }
    if(!findnpc)//没找到战斗中npc
    {
        int beginint=id.indexOf("#");
        if(beginint!=1)
        {
            QString ehname=id.mid(0,beginint).toLower();
            killnpcstruct asf;
            asf.enName=ehname;
            asf.zhName=zhName;
            asf.id=id;
            asf.fightStart=true;
            npcname.append(asf);
        }
    }
}

void KillSys::fightting(QString status)
{
    if(status=="false")
    {
        npcname.clear();
    }
    else//突然进入战斗状态、不触发gmcp，停止行走
    {
        if(WorkSys::GetInstance()->working)
        {
            walkingStop=true;
            emit sysCmd("#pause");
        }
    }
}

void KillSys::nokillNpc()
{
    if(wangkillNum)
    {
        killSysGetMes=false;
        if(walkingStop)
        {
            walkingStop=false;
            emit sysCmd("#walk");
        }
        else
        {
            emit sysCmd("");
        }
    }
    else
    {
        wangkillNum=true;
        emit sysCmd("killall "+wantkill);
    }
    wantkill.clear();
}

void KillSys::npcdie(QString name)
{
    for(int numnum=0;numnum<npcname.size();numnum++)
    {
        if(npcname[numnum].zhName==name)
        {
            npcname.removeAt(numnum);
            break;
        }
    }
    if(npcname.size()==0)
    {
        if(wantkill.isEmpty())//假如是有自己想杀的人，再叫杀一次
        {
            if(walkingStop)
            {
                walkingStop=false;
                emit sysCmd("#walk");
            }
            else
            {
                emit sysCmd("");
            }
        }
        else
        {
            //重复叫杀目标，如果已经true;而且返回没人，那就代表没目标了
            wangkillNum=true;
            //qDebug()<<"MapMainWindow::roomMessage--  npcdie";
            emit sysCmd("killall "+wantkill);
        }
    }
}

void KillSys::roomMessage(QByteArray roomMess)
{
    while (roomMess.size()>0) {//循环截取出要打印的字符串  一行的那种
        QByteArray oneStr;
        getOneStrFromArray(roomMess, oneStr);//截取出要打印的字符串  一行的那种
        //只有房间名以外的才需要去除颜色
        removeColorFromArray(oneStr);
        QRegularExpressionMatch npcdieREGmatch=npcdieREG.match(oneStr);
        if(npcdieREGmatch.hasMatch())
        {
            //qDebug()<<"MapMainWindow::roomMessage--  npcdie"<<npcdieREGmatch.captured(1);
            npcdie(npcdieREGmatch.captured(1));
        }
        else
        {
            QRegularExpressionMatch nokillNpcREGmatch=nokillNpcREG.match(oneStr);
            if(nokillNpcREGmatch.hasMatch())
            {
                //qDebug()<<"MapMainWindow::roomMessage--  nokillNpc";
                nokillNpc();
            }
        }
    }
}

void KillSys::getOneStrFromArray(QByteArray &inArray, QByteArray &outArray)
{
    bool findStr=false;//找到回车换行
    int charNum=0;//没找到回车换行，但是到尾部了
    for(; charNum<inArray.size()-1; charNum++)
    {
        if(uchar(inArray[charNum])==0x0D && uchar(inArray[charNum+1])==0x0A)
        {
            findStr=true;
            charNum++;
            break;
        }
    }

    if(findStr)//找到回车换行
    {
        outArray=inArray.mid(0, charNum+1);
        inArray=inArray.mid(charNum+1);
        //qDebug()<<"outArray--"<<QString(outArray)<<"  backArray--"<<QString(backArray);
    }
    else
    {
        if(charNum+1 == inArray.size())//没找到回车换行，但是到尾部了
        {
            outArray=inArray;
            inArray=inArray.mid(charNum+1);
            //qDebug()<<"outArray--"<<QString(outArray)<<"  backArray--"<<QString(backArray);
        }
        else
        {
            //qDebug()<<"error  backArray--"<<QString(backArray);
        }
    }
}

bool KillSys::removeColorFromArray(QByteArray &inArray)
{
    bool found=false;
    int Num=0;
    while(Num<inArray.size()-1)
    {
        if(inArray[Num]=='\x1B')
        {
            int key=Num+1;
            if(key<inArray.size() && inArray[key]=='[')//\x1B 后必是 [
            {
                key++;
                while(key<inArray.size())
                {
                    if(inArray[key]==';' || ('0'<=inArray[key] && inArray[key]<='9') || inArray[key]=='m')
                    {
                        if(inArray[key]=='m')//M结尾
                        {
                            found=true;
                            break;
                        }
                    }
                    else
                    {
                        found=false;
                        break;
                    }
                    key++;
                }
            }
            if(found)//数组中移除
            {
                inArray.remove(Num,key-Num+1);
                Num--;
            }
        }
        Num++;
    }
    return found;
}
