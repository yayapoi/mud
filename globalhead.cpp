#include "globalhead.h"

bool globalCheck::checkNewReg(QString &instr)
{
    bool flag=false;
    int index=instr.indexOf("#newReg(");
    if(index==0)
    {
        flag=true;
    }
    return flag;
}

bool globalCheck::checkDeleteReg(QString &instr)
{
    bool flag=false;
    int index=instr.indexOf("#deleteReg(");
    if(index==0)
    {
        flag=true;
    }
    return flag;
}

bool globalCheck::checkEnableRegReg(QString &instr)
{
    bool flag=false;
    int index=instr.indexOf("#enableReg(");
    if(index==0)
    {
        flag=true;
    }
    return flag;
}

bool globalCheck::checkSetHPBar(QString &instr)
{
    bool flag=false;
    int index=instr.indexOf("#setHpBar(");
    if(index==0)
    {
        flag=true;
    }
    return flag;
}
