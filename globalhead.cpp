#include "globalhead.h"
#include <zconf.h>

bool showGmcpAllBool=false;
bool buffBool=false;
bool moveBool=false;
bool combatBool=false;
bool statusBool=false;
bool messageBool=false;

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
