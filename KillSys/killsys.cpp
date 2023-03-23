#include "killsys.h"
#include "globalhead.h"

KillSys* KillSys::m_pipe_rw = nullptr;
KillSys::GC KillSys::gc;

KillSys::KillSys(QObject *parent)
    : QObject{parent}
{

}

void KillSys::killNpcStart(QString str)
{
    qDebug()<<"#killmpc()--";
    int lastint=str.lastIndexOf(")");
    if(lastint!=1)
    {
        npcname=str.mid(9,lastint-9).toLower();
        emit sysCmd("#pause;#enableReg(\"默认分组\",\"fight\",1);yun qi;yun powerup;kill "+npcname);
    }
}

void KillSys::nokillNpc(QString)
{
    emit sysCmd("#enableReg(\"默认分组\",\"fight\",1);#walk");
}

void KillSys::againkillNpc(QString)
{
    emit sysCmd("kill "+npcname);
}
