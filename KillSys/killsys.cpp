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
    //qDebug()<<"KillSys::killNpcStart  str--"<<str;
    int lastint=str.lastIndexOf(")");
    if(lastint!=1)
    {
        QString wantkill=str.mid(9,lastint-9).toLower();
        npcList(wantkill);
        killSysGetMes=true;
        iwantkill=true;
        wangkillNum=0;
        QString cmd;
        if(WorkSys::GetInstance()->working)//行走中需停止
        {
            walkingStop=true;
            cmd="#pause;";
        }
        if(wantkillList.isEmpty())//空的全喊
        {
            //qDebug()<<"KillSys::killNpcStart  杀光他们--";
            cmd=cmd+"yun qi;yun powerup;killall;";
        }
        else//不空就看一个个喊还是
        {
            cmd=cmd+"yun qi;yun powerup;";
            if(killOnce)//一个一个
            {
                //qDebug()<<"KillSys::killNpcStart  个个来--";
                cmd=cmd+"kill "+wantkillList[wangkillNum]+";";
                wangkillNum++;
            }
            else//一起
            {
                //qDebug()<<"KillSys::killNpcStart  一起来吧--";
                int npcnum=0;
                for(;npcnum<wantkillList.size();npcnum++)
                {
                    cmd=cmd+"kill "+wantkillList[npcnum]+";";
                }
                wangkillNum=npcnum;
            }
        }
        //qDebug()<<"KillSys::killNpcStart  cmd--"<<cmd;
        emit sysCmd(cmd);
    }
}

void KillSys::killmeStart(QString zhName, QString id)//被动叫杀不会触发，要之无用
{
    //qDebug()<<"KillSys::killmeStart  zhName--"<<zhName<<"   id--"<<id;
    /*int beginint=id.indexOf("#");
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
    }*/
}

void KillSys::fightCheck(QString zhName, QString id)
{
    //qDebug()<<"KillSys::fightCheck  zhName--"<<zhName<<"   id--"<<id;
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
        //qDebug()<<"KillSys::fightCheck  没找到--";
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
    else
    {
        //qDebug()<<"KillSys::fightCheck  已经在名单里了--";
    }
}

void KillSys::fightting(QString status)
{
    if(status=="false")//处于不战斗状态，看是清空走人还是查询继续战斗
    {
        //qDebug()<<"KillSys::fightting  怎么停手了--";
        mingdanORwantkill();
    }
    else//突然进入战斗状态、不触发gmcp，停止行走
    {
        //qDebug()<<"KillSys::fightting  打起来啦--";
        killSysGetMes=true;//需要战斗信息
        mingdanchonghan=false;//只要战斗 战斗名单必须从头开始
        iwantchonghan=false;//只要战斗想杀名单必须从头开始
        if(WorkSys::GetInstance()->working)
        {
            walkingStop=true;
            emit sysCmd("#pause");
        }
    }
}

void KillSys::nokillNpc()
{
    //qDebug()<<"KillSys::npcList  没人让我杀哎--";
    if(mingdanchonghan)//正在重新喊杀
    {
        //qDebug()<<"KillSys::fightting  杀了一个了--"<<npcname[0].id;
        npcname.removeFirst();
    }
    mingdanORwantkill();
}

void KillSys::npcdie(QString name)
{
    /*for(int numnum=0;numnum<npcname.size();numnum++)
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
    }*/
}

void KillSys::npcList(QString &name)
{
    wantkillList.clear();
    int namebegin=0;
    int num=0;
    for(;num<name.size();num++)
    {
        if(name[num]==';')//已经一个名字了或者为空
        {
            QString namename=name.mid(namebegin,num-namebegin);
            namebegin=num+1;
            //qDebug()<<"namename--"<<namename;
            if(!namename.isEmpty())
            {
                wantkillList.append(namename);
            }
        }
    }
    if(namebegin!=num)
    {
        QString namename=name.mid(namebegin,num-namebegin);
        //qDebug()<<"namename22--"<<namename;
        if(!namename.isEmpty())
        {
            wantkillList.append(namename);
        }
    }
    //qDebug()<<"KillSys::npcList  这些人都得死--"<<wantkillList;
}

void KillSys::roomMessage(QByteArray roomMess)
{
    while (roomMess.size()>0) {//循环截取出要打印的字符串  一行的那种
        QByteArray oneStr;
        getOneStrFromArray(roomMess, oneStr);//截取出要打印的字符串  一行的那种
        //只有房间名以外的才需要去除颜色
        removeColorFromArray(oneStr);
        /*QRegularExpressionMatch npcdieREGmatch=npcdieREG.match(oneStr);
        if(npcdieREGmatch.hasMatch())
        {
            //qDebug()<<"MapMainWindow::roomMessage--  npcdie"<<npcdieREGmatch.captured(1);
            npcdie(npcdieREGmatch.captured(1));
        }
        else
        {*/
        QRegularExpressionMatch nokillNpcREGmatch=nokillNpcREG.match(oneStr);
        if(nokillNpcREGmatch.hasMatch())
        {
            //qDebug()<<"MapMainWindow::roomMessage--  nokillNpc";
            nokillNpc();
        }
        else
        {
            QRegularExpressionMatch killAllCDREGmatch=killAllCDREG.match(oneStr);
            if(killAllCDREGmatch.hasMatch())
            {
                //killall时 有CD
                QTimer::singleShot(1000, this, [this]()
                    {
                        emit sysCmd("killall");
                    });
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

void KillSys::mingdanORwantkill()
{
    if(!mingdanchonghan && !npcname.isEmpty())
    {
        //qDebug()<<"KillSys::mingdanORwantkill  刚才谁喊杀我，开始清算了--";
        mingdanchonghan=true;
    }
    if(mingdanchonghan)//重喊战斗名单
    {
        if(!npcname.isEmpty())
        {
            //qDebug()<<"KillSys::mingdanORwantkill  死了没--"<<npcname[0].enName<<"  id--"<<npcname[0].id;
            emit sysCmd("kill "+npcname[0].enName);
        }
        else//战斗名单已经空了 就走下面
        {
            //qDebug()<<"KillSys::mingdanORwantkill  现在战斗名单空了哎--";
            mingdanchonghan=false;
            mingdanORwantkill();
        }
    }
    else//看想杀名单是否完事
    {
        if(wangkillNum+1>=wantkillList.size())//已经喊杀到满了 重喊想杀名单  或者开溜
        {
            if(iwantchonghan)//想杀重喊过了，并且喊杀到满了 重置傻系统并开溜
            {
                //qDebug()<<"KillSys::mingdanORwantkill  我想杀的人都没了啊--";
                killSysGetMes=false;
                wantkillList.clear();
                npcname.clear();
                wangkillNum=-1;
                killOnce=false;
                iwantkill=false;
                mingdanchonghan=false;
                iwantchonghan=false;
                if(walkingStop)//行走时停了
                {
                    walkingStop=false;
                    emit sysCmd("#walk");
                }
            }
            else
            {
                wangkillNum=-1;//从头喊杀
                iwantchonghan=true;
                if(wantkillList.isEmpty())//没名单的想全杀
                {
                    if(iwantkill)
                    {
                        //qDebug()<<"KillSys::mingdanORwantkill  一起上吧，我想杀的人--";
                        emit sysCmd("killall ");
                    }
                    else
                    {
                        //qDebug()<<"KillSys::mingdanORwantkill  是不知名的战斗吗--";
                        killSysGetMes=false;
                        wantkillList.clear();
                        npcname.clear();
                        wangkillNum=-1;
                        killOnce=false;
                        iwantkill=false;
                        mingdanchonghan=false;
                        iwantchonghan=false;
                        if(walkingStop)//行走时停了
                        {
                            walkingStop=false;
                            emit sysCmd("#walk");
                        }
                    }
                }
                else//有名单的
                {
                    //qDebug()<<"KillSys::mingdanORwantkill  迎接清算吧，我想杀的人--";
                    mingdanORwantkill();
                }
            }
        }
        else//没喊杀完，继续喊杀
        {
            wangkillNum++;
            //qDebug()<<"KillSys::mingdanORwantkill  受死吧，我想杀的人--"<<wantkillList[wangkillNum]<<"  wangkillNum--"<<wangkillNum;
            emit sysCmd("kill "+wantkillList[wangkillNum]);
        }
    }
}
