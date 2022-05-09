#ifndef GLOBALHEAD_H
#define GLOBALHEAD_H

#include <QObject>
#include <QDebug>

enum Colors { close_all=0,//关闭所有属性
              Bold_Color,//设置高亮度
              underline=4,//下划线
              Italic,//闪烁
              Overline=7,//反白显示
              StrikeOut,//不可见
              font_darkgray = 30,
              font_red,
              font_green,
              font_yellow,//【任务】
              font_cyan,
              font_magenta,//【谣言】
              font_darkgrren,//【闲聊】【本地】
              font_white,//【求助】【江湖】【北侠QQ群】
              back_darkgray = 40,
              back_red,
              back_green,
              back_yellow,
              back_cyan,
              back_magenta,
              back_darkgrren,
              back_white};

enum StrType{
    renWu = 0,
    yaoYan,
    xianLiao,
    qiuZhu,
    jiangHu,
    beiXiaQun
};

/* @brief 用户自定义的触发器*/
struct RegStr
{
    QString regStr="";//触发正则
    int coldTime=0;//冷却时间？
    QString color=0;//颜色触发？
    QString parent="默认分组";//名字唯一
    QString regName="";//组内唯一
    int row=1;//这个触发器用户想让他匹配几行
    bool oneStrOneReg=true;//一行仅触发一次
    bool enable=true;

    bool sysOrUser=true;//用户类则使用端口，系统类则使用关键词
    int port=8080;//用户指定触发成功后发送给哪个tcp端口
    QString sysStr="hp";
};

/* @brief 记录一个触发器，有触发器的已经触发行，开始点，和长度*/
struct RegPtr
{
    RegStr oneReg;
    int row=0;//这个触发器在第几行已经触发过了
    int beginPoint=-1;//在第几号位触发了
    int strLength=-1;//触发长度
};

namespace Common // RFC854
{
// Commands
const uchar CEOF  = 236;
const uchar SUSP  = 237;
const uchar ABORT = 238;

const uchar SE    = 240; // SubnegotiationEnd
const uchar NOP   = 241; // NoOperation
const uchar DM    = 242; // DataMark
const uchar BRK   = 243; // Break
const uchar IP    = 244; // InterruptProcess
const uchar AO    = 245; // AbortOutput
const uchar AYT   = 246; // AreYouThere
const uchar EC    = 247; // EraseCharacter
const uchar EL    = 248; // EraseLine
const uchar GA    = 249; // GoAhead
const uchar SB    = 250; // SubnegotiationBegin

// Negotiation
const uchar WILL  = 251;
const uchar WONT  = 252;
const uchar DO    = 253;
const uchar DONT  = 254;

// Escape
const uchar IAC   = 255;

// Types
const uchar IS     = 0;
const uchar SEND   = 1;
const uchar NAWS   = 31; // RFC1073, implemented

// Types (MUD-specific)
const uchar MSDP   = 69;
const uchar MXP    = 91;
const uchar MCCP1  = 85;
const uchar MCCP2  = 86;
const uchar MSP    = 90;

const uchar DRAW_MAP = 91;
const uchar CLR_MAP  = 92;

// Formatting Command
const uchar FORMAT = 100;
};
//255 250 86 255 240



namespace globalCheck {

/* @brief 系统函数新增Reg，是则使用并返回true*/
bool checkNewReg(QString &instr);

/* @brief 系统函数删除Reg，是则使用并返回true*/
bool checkDeleteReg(QString &instr);

/* @brief 系统函数开关Reg，是则使用并返回true*/
bool checkEnableRegReg(QString &instr);

/* @brief 系统函数设置血条状态，是则使用并返回true*/
bool checkSetHPBar(QString &instr);
}

#endif // GLOBALHEAD_H
