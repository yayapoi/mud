#ifndef WORKSYS_H
#define WORKSYS_H

#include "qdatetime.h"
#include "qregularexpression.h"
#include "qtimer.h"
#include <QObject>

struct roomStruct{
    QString roomNameZH;
    int roomnum=-1;
    //假如此房间这步停过，就不需要再停
    int stopnum=-1;
    QString roomNameEN;
    QString fZH;
    QString sZH;
    QString srdZH;
    QString cmd;
    QStringList releaseCmd;
    void clear()
    {
        roomNameZH="";
        roomnum=-1;
        roomNameEN="";
        fZH="";
        sZH="";
        srdZH="";
        cmd="";
        releaseCmd.clear();
    };
};

class WorkSys : public QObject
{
    Q_OBJECT
public:
    static WorkSys* GetInstance()
    {
        if (m_pipe_rw == NULL)
        {
            if (m_pipe_rw == NULL)
                m_pipe_rw = new WorkSys();
        }
        return m_pipe_rw;
    }

    /*行走系统
#go 地点 yz|dls //去目的地  重复名字按房间号排序 显示查看
#qu yz //去目的区域中心
#qu1 yz //去目的区域边缘不进区域
#use 11   //去指定地点
#see 11      //查看描述和周边房间
#pause    //停止
#walk     //接着走
#back     //返回到停止的出发点或者最近出发点
#get 地点 区域|区域 //获取去目的地路径  重复名字按房间号排序 显示查看
#get1 区域 //获取去目的区域中心路径
#get2 区域 //获取去目的区域边缘不进区域路径
#dingwei   //尝试先查询定位，再尝试看周围定位，再尝试随机走路定位
#pathcheck   //带房间的可校验路径，会根据系统函数来添加
#path   //使用没有房间定位的路径来解析，会根据系统函数来添加
*/
    ///路径list
    QList<roomStruct> pathList;
    ///定时器
    QTimer walktimer;
    ///最近一次方向时间
    QTime lastTime;
    //流程是否暂停 true:不暂停
    bool working=false;
    ///全部走完，正常结束：true, 还没走完:false
    bool workend=true;
    int listnow=-1;
    int cmdnum=-1;
    ///是否busy，true:busy中，false：不busy
    bool busy=false;
    ///是否移动成功，true:移动成功，false：移动失败
    bool moveSuccess=true;
    ///是否方向命令发出后发来结果，true:发来了，false：还没发来
    bool getmoveStatus=true;
    //一处执行，其它调用本函数不用执行 true:已执行 可能不需要 可sleep测试
    bool mux=false;
    QRegularExpression pathRegStr{"^#path\\(([\\s\\S]+?)\\)$"};
    QRegularExpression GmcpRegStr{"^#mg\\(([\\s\\S]+?)\\)$"};

    ///开始走路
    void startWalk();
    /// 继续走路
    void Walk();
    /// 暂停走路
    void stopWalk();
    /// move成功失败
    void moveStatus(bool flag);
    /// buy状态
    void busyStatus(bool flag);
    /// 清空路径
    void clearOldPath();
    ///键值对路径   测试试试:#killnpc(wei zheng:);say 1;#Timer(3000,\"()sa:y( 1;say 2;say 3)\");say 3 &yz_qsdd_1:e(:&)
    void releasepareCmd(QString pathAll,bool addCmd=true);
    ///纯路径    #killnpc(wei zheng:);say 1;#Timer(3000,\"()sa:y( 1;say 2;say 3)\");say 3 ;yz_qsdd_1;
    void releaseCmd(QString pathAll,bool addCmd=true);
    /**
     * @brief releaseList 解析队列
     * @param addCmd true:解析时遇见系统函数添加上下文，false:用户已经拼好了，我不用拼系统函数上下文
     */
    void releaseList(bool addCmd);
    ///从命令中分析出所有带分号的命令,nownum:现在已经解析到第几个房间了.  true:解析时遇见系统函数添加上下文
    void appendMessage(QString inStr, QStringList &backList, int &nownum, bool addCmd);
    /* @brief 检查是否括号匹配，例如#T(1,"c;#T(1,"c");c");,有完整句子返回句子尾端,没有完整句子返回-1*/
    int backStringIndex(QString &instr, int &from, int &kuohaoend);
    /* @brief 检查是否存在宏，并将宏要替代的东西替换*/
    bool getMessageFrom(QString& inStr, QString& backStr);
    /* @brief 检查是否存在系统函数，killNpc,enterBoat,enterChe，并将函数周围要替换的替换.nownum:现在已经解析到第几个房间了*/
    bool getfunFrom(QString& inStr, QString& backStr, int &nownum);
    /* @brief 删除最前方空格*/
    void clearBlok(QString &instr);
    /* @brief 查找最外层括号，比如aa(c(d)())x()   formnum为0返回begin=2 end=9  fromNum为2依旧2 9，formnum为3返回begin=11 end=12*/
    bool findkuohao(QString &instr,int fromNum,int &begin,int &end);
    /* @brief 路径是否已经到底了*/
    bool endpathList(int listNum);
    /* @brief room中命令是否已经到底了*/
    bool endproomList(int listNum, int cmdNum);
    /* @brief 开始初始化变量走路 特殊情况不用计时  true:计时*/
    void dowork(bool jishi);
    /* @brief 移动校验 gmcp校验*/
    bool moveGmcp(QString &instr);
    /* @brief 移动校验 room校验*/
    void moveroom(QString &instr);
signals:
    ///发向命令执行器的命令
    void cmdroom(QString room, QString cmd);
    ///行走系统打印
    void workPritf(QString str);
    ///继续走路
    void continueWalk();
private:
    explicit WorkSys(QObject *parent = nullptr);
    class GC
    {
    public:
        GC()
        {
        }
        ~GC()
        {
            if (m_pipe_rw != NULL)
            {
                delete m_pipe_rw;
                m_pipe_rw = NULL;
            }
        }
    };
    static GC gc;
    static WorkSys* m_pipe_rw;
};

#endif // WORKSYS_H
