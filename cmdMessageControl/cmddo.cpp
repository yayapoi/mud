#include "cmddo.h"

CmdDo::CmdDo(QObject *parent)
    : QObject{parent}
{

}

void CmdDo::newMessage(QQueue<QString> inList)
{
    while (!inList.isEmpty()) {
        QString messageStr=inList.dequeue();
        if(checkMessage(messageStr))
        {
            //不是系统函数，则发送给tcp 须填
        }
    }
}

bool CmdDo::checkMessage(QString &instr)
{
    //须填
    return false;
}
