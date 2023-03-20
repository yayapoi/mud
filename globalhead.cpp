#include "globalhead.h"
#include <zconf.h>

bool showGmcpAllBool=false;
bool buffBool=false;
bool moveBool=false;
bool combatBool=false;
bool statusBool=false;
bool messageBool=false;
killnpc killNpc=nullptr;
bool longOrShortTime=false;
bool errorTime=true;

bool mapcreateGetMessage=false;
QString outChange(QString cmd)
{
    if(cmd=="north" || cmd=="n")
    {
        return "s";
    }
    else if(cmd=="nw" || cmd=="northwest")
    {
        return "se";
    }
    else if(cmd=="ne" || cmd=="northeast")
    {
        return "sw";
    }
    else if(cmd=="nu" || cmd=="northup")
    {
        return "sd";
    }
    else if(cmd=="nd" || cmd=="northdown")
    {
        return "su";
    }
    else if(cmd=="south" || cmd=="s")
    {
        return "n";
    }
    else if(cmd=="su" || cmd=="southup")
    {
        return "nd";
    }
    else if(cmd=="sd" || cmd=="southdown")
    {
        return "nu";
    }
    else if(cmd=="sw" || cmd=="southwest")
    {
        return "ne";
    }
    else if(cmd=="se" || cmd=="southeast")
    {
        return "nw";
    }
    else if(cmd=="west" || cmd=="w")
    {
        return "e";
    }
    else if(cmd=="wu" || cmd=="westup")
    {
        return "ed";
    }
    else if(cmd=="wd" || cmd=="westdown")
    {
        return "eu";
    }
    else if(cmd=="east" || cmd=="e")
    {
        return "w";
    }
    else if(cmd=="eu" || cmd=="eastup")
    {
        return "wd";
    }
    else if(cmd=="ed" || cmd=="eastdown")
    {
        return "wu";
    }
    else if(cmd=="enter")
    {
        return "out";
    }
    else if(cmd=="out")
    {
        return "enter";
    }
    else if(cmd=="up" || cmd=="u")
    {
        return "d";
    }
    else if(cmd=="down" || cmd=="d")
    {
        return "u";
    }
    return "特殊方向";
}

QString outjianhua(QString cmd)
{
    if(cmd.count()==1)
    {
        return cmd;
    }
    else
    {
        if(cmd=="north" || cmd=="n")
        {
            return "n";
        }
        else if(cmd=="nw" || cmd=="northwest")
        {
            return "nw";
        }
        else if(cmd=="ne" || cmd=="northeast")
        {
            return "ne";
        }
        else if(cmd=="nu" || cmd=="northup")
        {
            return "nu";
        }
        else if(cmd=="nd" || cmd=="northdown")
        {
            return "nd";
        }
        else if(cmd=="south" || cmd=="s")
        {
            return "s";
        }
        else if(cmd=="su" || cmd=="southup")
        {
            return "su";
        }
        else if(cmd=="sd" || cmd=="southdown")
        {
            return "sd";
        }
        else if(cmd=="sw" || cmd=="southwest")
        {
            return "sw";
        }
        else if(cmd=="se" || cmd=="southeast")
        {
            return "se";
        }
        else if(cmd=="west" || cmd=="w")
        {
            return "w";
        }
        else if(cmd=="wu" || cmd=="westup")
        {
            return "wu";
        }
        else if(cmd=="wd" || cmd=="westdown")
        {
            return "wd";
        }
        else if(cmd=="east" || cmd=="e")
        {
            return "e";
        }
        else if(cmd=="eu" || cmd=="eastup")
        {
            return "eu";
        }
        else if(cmd=="ed" || cmd=="eastdown")
        {
            return "ed";
        }
        else if(cmd=="enter")
        {
            return "enter";
        }
        else if(cmd=="out")
        {
            return "out";
        }
        else if(cmd=="up" || cmd=="u")
        {
            return "u";
        }
        else if(cmd=="down" || cmd=="d")
        {
            return "d";
        }
    }
    return "特殊方向";
}

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

void globalCheck::int2Bytes(int i, QByteArray &backArray, int off)
{
    backArray[0 + off] = (Byte) (i >> 16 & 0xFF);
    backArray[1 + off] = (Byte) (i >> 8 & 0xFF);
    backArray[2 + off] = (Byte) (i & 0xFF);
}

int globalCheck::bytes2Int(QByteArray &backArray, int off)
{
    int b0 = backArray[0 + off] & 0xFF;
    int b1 = backArray[1 + off] & 0xFF;
    int b2 = backArray[2 + off] & 0xFF;
    return (b0 << 16) | (b1 << 8) | b2;
}

bool globalCheck::checkTimer(QString &instr)
{
    bool flag=false;
    int index=instr.indexOf("#Timer(");
    if(index==0)
    {
        flag=true;
    }
    return flag;
}

bool globalCheck::checkPritf(QString &instr)
{
    bool flag=false;
    int index=instr.indexOf("#Pritf(");
    if(index==0)
    {
        flag=true;
    }
    return flag;
}

bool globalCheck::checkPath(QString &instr)
{
    bool flag=false;
    int index=instr.indexOf("#path(");
    if(index==0)
    {
        flag=true;
    }
    return flag;
}

bool globalCheck::checkPause(QString &instr)
{
    bool flag=false;
    int index=instr.indexOf("#pause");
    if(index==0)
    {
        flag=true;
    }
    return flag;
}

bool globalCheck::checkMoveRoom(QString &instr)
{
    bool flag=false;
    int index=instr.indexOf("#mr(");
    if(index==0)
    {
        flag=true;
    }
    return flag;
}

bool globalCheck::checkMoveGMCP(QString &instr)
{
    bool flag=false;
    int index=instr.indexOf("#mg(");
    if(index==0)
    {
        flag=true;
    }
    return flag;
}
