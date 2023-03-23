#include "dlltomapcreate.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

bool killNpc(char *roomName, char *backBegin, char *backEnd)
{
    bool backcha=false;
    char name[15]={"测试试试"};
    if (strcmp(name,roomName)==0 )
    {
        backcha=true;
        strcpy ( backBegin , "#enableReg(\"测试\",\"buce\",1);#Printf(\"到了\"+roomName+\"。要杀人了\");#workStop;" );
        strcpy ( backEnd , "" );
    }
    else
    {
        //
    }
    return backcha;
}

bool boatIn(char *roomName, char *&backStr)
{
    char split[]=";";
    bool backcha=false;
    if (strcmp("zy_hhba",roomName)==0 || strcmp("hz_hhna_1",roomName)==0|| strcmp("111",roomName)==0)
    {
        backcha=true;
        char bdginchar[]="#enableReg(\"ride渡口\",\"到了\",1);ride";
        char endchar[]="#pause;#enableReg(\"ride渡口\",\"到了\",0)";
        backStr=(char *)malloc(( strlen(bdginchar)
                                 +strlen(split)+strlen(endchar) )*sizeof(char));
        strcpy(backStr, bdginchar);
        strcat(backStr, split);
        strcat(backStr, endchar);
    }
    if (strcmp("yz_yzj_1",roomName)==0 || strcmp("yz_zjdk",roomName)==0|| strcmp("111",roomName)==0)
    {
        backcha=true;
        char bdginchar[]="#enableReg(\"yellboat\",\"\",1);yell boat";
        char endchar[]="#pause;#enableReg(\"yellboat\",\"\",0)";
        backStr=(char *)malloc(( strlen(bdginchar)
                                 +strlen(split)+strlen(endchar) )*sizeof(char));
        strcpy(backStr, bdginchar);
        strcat(backStr, split);
        strcat(backStr, endchar);
    }
    else
    {
        //
    }
    return backcha;
}

bool cheIn(char *roomName, char *cmd, char *&backStr)
{
    char split[]=";";
    bool backcha=false;
    if (strcmp("yz_mc",roomName)==0 || strcmp("xy_mc",roomName)==0|| strcmp("111",roomName)==0)
    {
        backcha=true;
        char bdginchar[]="#enableReg(\"坐车\",\"下车\",1)";
        char endchar[]="#pause;#enableReg(\"坐车\",\"下车\",0)";
        backStr=(char *)malloc((1 +strlen(bdginchar)
                                +1+strlen(cmd)
                                +1+strlen(endchar))*sizeof(char));
        strcpy(backStr, bdginchar);
        strcat(backStr, split);
        strcat(backStr, cmd);
        strcat(backStr, split);
        strcat(backStr, endchar);
    }
    else
    {
        //
    }
    return backcha;
}
