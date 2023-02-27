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

INIManarge::INIManarge()
{
    settings = new QSettings ("config.ini", QSettings::IniFormat);//构建函数
    //参数：参数一为配置文件，一般位于项目文件下，参数二表示针对ini文件格式
    settings->setIniCodec("UTF-8");
}

