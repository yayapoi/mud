#include "cmddo.h"
#include <globalhead.h>

CmdDo::CmdDo(QObject *parent)
    : QObject{parent}
{

}

void CmdDo::newMessage(QQueue<QString> inList)
{
    while (!inList.isEmpty()) {
        QString messageStr=inList.dequeue();
        emit cmdShowInWindow("\r\ncmd命令: "+messageStr+"\r\n");
        if(!checkMessage(messageStr))
        {
            //不是系统函数，则发送给tcp
            emit sendToServer(messageStr);
        }
    }
}

bool CmdDo::checkMessage(QString &instr)
{
    bool flag=false;
    if(flag==false)
    {
        flag=globalCheck::checkEnableRegReg(instr);
        if(flag==true)
        {
            emit enableRegStr(instr);
        }
    }
    if(flag==false)
    {
        flag=globalCheck::checkPritf(instr);
        if(flag==true)
        {
            emit pritf(instr);
        }
    }
    if(flag==false)
    {
        flag=globalCheck::checkNewReg(instr);
        if(flag==true)
        {
            emit newRegStr(instr);
        }
    }
    if(flag==false)
    {
        flag=globalCheck::checkMoveRoom(instr);
        if(flag==true)
        {
            emit MoveRoom(instr);
        }
    }
    if(flag==false)
    {
        flag=globalCheck::checkMoveGMCP(instr);
        if(flag==true)
        {
            emit MoveGMCP(instr);
        }
    }
    if(flag==false)
    {
        flag=globalCheck::checkDeleteReg(instr);
        if(flag==true)
        {
            emit deleteRegStr(instr);
        }
    }
    if(flag==false)
    {
        flag=globalCheck::checkSetHPBar(instr);
        if(flag==true)
        {
            emit setHPBar(instr);
        }
    }
    if(flag==false)
    {
        flag=globalCheck::checkPath(instr);
        if(flag==true)
        {
            emit Path(instr);
        }
    }
    if(flag==false)
    {
        flag=globalCheck::checkPause(instr);
        if(flag==true)
        {
            emit Pause(instr);
        }
    }
    return flag;
}
