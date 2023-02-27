#include "inimanarge.h"
#include <QDebug>

INIManarge* INIManarge::m_pipe_rw = nullptr;
INIManarge::GC INIManarge::gc;

INIManarge::~INIManarge()
{
    delete settings;
}

void INIManarge::getUserNameGmcp(UserNameGmcp &back)
{
    back.userName=settings->value("/GmcpSetting/userName").toString();
    back.userEnName=settings->value("/GmcpSetting/userEnName").toString();
}

void INIManarge::setUserNameGmcp(UserNameGmcp &back)
{
    settings->setValue("/GmcpSetting/userName",back.userName);
    settings->setValue("/GmcpSetting/userEnName",back.userEnName);
}

void INIManarge::getCheckGmcp(showGmcpCheck &back)
{
    back.showGmcpAll=settings->value("/GmcpSetting/showGmcpAll").toBool();
    back.buff=settings->value("/GmcpSetting/buff").toBool();
    back.combat=settings->value("/GmcpSetting/combat").toBool();
    back.message=settings->value("/GmcpSetting/message").toBool();
    back.move=settings->value("/GmcpSetting/move").toBool();
    back.status=settings->value("/GmcpSetting/status").toBool();
}

void INIManarge::setCheckGmcp(showGmcpCheck &back)
{
    settings->setValue("/GmcpSetting/showGmcpAll",back.showGmcpAll);
    settings->setValue("/GmcpSetting/buff",back.buff);
    settings->setValue("/GmcpSetting/combat",back.combat);
    settings->setValue("/GmcpSetting/message",back.message);
    settings->setValue("/GmcpSetting/move",back.move);
    settings->setValue("/GmcpSetting/status",back.status);
    showGmcpAllBool=back.showGmcpAll;
    buffBool=back.buff;
    combatBool=back.combat;
    messageBool=back.message;
    moveBool=back.move;
    statusBool=back.status;
}

INIManarge::INIManarge()
{
    settings = new QSettings ("config.ini", QSettings::IniFormat);//构建函数
    //参数：参数一为配置文件，一般位于项目文件下，参数二表示针对ini文件格式
    settings->setIniCodec("UTF-8");
}

