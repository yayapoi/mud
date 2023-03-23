#ifndef GLOBALHEAD_H
#define GLOBALHEAD_H

#include <QObject>
#include <QDebug>
#include "qpoint.h"
#include <QString>
#include <QList>

typedef bool (*killnpc)(char *roomName, char *backStr, char *backEnd);
typedef bool (*boatin)(char *roomName, char *&backStr);
typedef bool (*chein)(char* roomName, char* cmd, char* &backStr);

//下面几个是gmcp显示设置的
extern bool showGmcpAllBool;
extern bool buffBool;
extern bool moveBool;
extern bool combatBool;
extern bool statusBool;
extern bool messageBool;
///编辑模式
extern bool mapCreaterShow;
extern killnpc killNpc;
extern boatin boatIn;
extern chein cheIn;
///地图编辑器需要传入数据，地图编辑器获取完置为false;true:需要传数据
extern bool mapcreateGetMessage;
///使用最长或者最短时间，配置里选  true:最长，
extern bool longOrShortTime;
///网络延时过长时 同时用户确认只需要很短时间时  使用虚假时间，配置里选  true:使用虚假时间，
extern bool errorTime;

struct NpcInfo{
    QString nameZH;//中文名
    QString nameEN;//英文名
    QString title;//之前的称号
};

struct OutInfo{
    QString outcmd;//输出方向
    QString outCmdNow;//输出方向的命令
    int room=-1;//房间数字
    int time=1;//走路耗时，最小值为1
};

struct roomInfo{
    QPoint roomPoint;//房间在画布位置
    int roomNum=1;//最初值为1，且递增，删除后应该补上新行
    int chongfuNum=0;//最初值为0，同区域有相同名字的房间
    QList<int> fromRoomList;//父房间
    QList<int> toRoomList;//子房间
    QString FqZH;//第一区域
    QString FqEN;//第一区域
    QString sqZH;//第二区域
    QString sqEN;//第二区域
    QString sthqZH;//第三区域
    QString sthqEN;//第三区域
    QString roomZH;//房间名
    QString roomEN;//房间名
    QString roomColor;//房间名颜色
    QString out;//描述的出口
    QString outnow;//实际的出口
    QString roomDes;//房间描述
    QList<NpcInfo> npcInfo;
    QList<OutInfo> outInfo;
};

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
              font_blue,
              font_magenta,//【谣言】
              font_cyan,//【闲聊】【本地】
              font_white,//【求助】【江湖】【北侠QQ群】
              back_darkgray = 40,
              back_red,
              back_green,
              back_yellow,
              back_blue,
              back_magenta,
              back_cyan,
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
    QString parent="默认分组";//名字唯一
    QString regName="";//组内唯一
    QString regStr="";//触发正则
    int row=1;//这个触发器用户想让他匹配几行
    bool oneStrOneReg=true;//一行仅触发一次
    bool enable=true;//是否开启
    bool sysOrUser=true;//用户类则使用端口，系统类则使用sysStr
    int port=8080;//用户类触发后发送给哪个tcp端口
    QString sysStr="";//系统类触发后执行的命令
    bool serverText=false;//颜色触发

    int coldTime=0;//冷却时间？
};

/* @brief 记录一个触发器，有触发器的已经触发行，开始点，和长度*/
struct RegPtr
{
    RegStr oneReg;
    int row=0;//这个触发器在第几行已经触发过了
    int beginPoint=-1;//在第几号位触发了
    int strLength=-1;//触发长度
};

/* @brief ini文件中的设置用户中文英文名，同时设置的时候也改变这个值*/
struct UserNameGmcp
{
    QString userName;
    QString userEnName;
};
/* @brief ini文件中的用户设置回显*/
struct showGmcpCheck
{
    bool showGmcpAll;
    bool buff;
    bool move;
    bool combat;
    bool status;
    bool message;
};

enum GMCPType{
    none,
    combat,
    status,
    move,
    buff,
    message
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
const uchar TYPE   = 24; // 终端类型
const uchar NAWS   = 31; // RFC1073, implemented

// Types (MUD-specific)
const uchar MSDP   = 69;
const uchar MXP    = 91;
const uchar MCCP1  = 85;
const uchar MCCP2  = 86;
const uchar MSP    = 90;
const uchar GMCP   = 201;

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
/* @brief 系统函数定时器，是则使用并返回true*/
bool checkTimer(QString &instr);
/* @brief 系统显示并触发，不发送服务器，是则使用并返回true*/
bool checkPritf(QString &instr);

/* @brief 行走系统解析无房间路径并行走，不发送服务器，是则使用并返回true*/
bool checkPath(QString &instr);
/* @brief 行走系统停止行走函数，不发送服务器，是则使用并返回true*/
bool checkPause(QString &instr);
/* @brief 行走系统继续行走函数，不发送服务器，是则使用并返回true*/
bool checkWalk(QString &instr);
/* @brief 行走系统房间值，不发送服务器，直接传入字符串“中央广场” 例 中央广场 - 或者中央广场 -星，是则使用并返回true*/
bool checkMoveRoom(QString &instr);
/* @brief 行走系统房间值，不发送服务器，直接传入gmcp的move值，是则使用并返回true*/
bool checkMoveGMCP(QString &instr);

/* @brief 在数组中指定位置插入指定数字，该数字必定占3字节*/
void int2Bytes(int i, QByteArray& backArray, int off);
/* @brief 从数组中指定位置读取数字，该数字必定占3字节*/
int bytes2Int(QByteArray& backArray, int off);
}

///传入一个方向，返回相反方向
QString outChange(QString cmd);

///传入一个方向，返回简拼方向
QString outjianhua(QString cmd);

#endif // GLOBALHEAD_H
