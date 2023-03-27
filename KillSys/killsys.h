#ifndef KILLSYS_H
#define KILLSYS_H

#include "qregularexpression.h"
#include "qtimer.h"
#include <QObject>

struct killnpcstruct
{
    QString zhName;
    QString enName;
    ///liu mang#930301  mu zhuangzi#1942144
    QString id;
    ///已经开打
    bool fightStart=false;
    ///已经喊杀
    int hansha=0;
};

class KillSys : public QObject
{
    Q_OBJECT
public:
    static KillSys* GetInstance()
    {
        if (m_pipe_rw == NULL)
        {
            if (m_pipe_rw == NULL)
                m_pipe_rw = new KillSys();
        }
        return m_pipe_rw;
    }

    ///进入战斗的npc名字
    QList<killnpcstruct> npcname;
    ///想杀的人，循环杀直到没这个人
    QStringList wantkillList;
    ///已经杀到第几个了
    int wangkillNum=-1;
    ///一起叫杀还是一个个叫杀，外部设置  true:一个一个杀
    bool killOnce=false;
    ///运行的时候停止了  true:是
    bool walkingStop=false;

    ///主动杀  true:是
    bool iwantkill=false;
    ///当不战斗时战斗名单需要重新刷新一边  true:正在重喊战斗名单
    bool mingdanchonghan=false;
    ///当不战斗时战斗名单也已经重喊过了  需要重喊想杀名单  true:正在重喊想杀名单
    bool iwantchonghan=false;

    QRegularExpression npcdieREG{"(?:([\u4e00-\u9fa5]+)死了。)"};
    QRegularExpression nokillNpcREG{"(?:你想攻击谁？)|(?:这里没有这个人。)|(?:这里没有可攻击的对手。)"};
    QRegularExpression killAllCDREG{"(?:你刚刚群体攻击过，还需要一点时间再准备。)"};


    ///#killpc()空为全杀   里面名字可以串联#killnpc(1 1;2 2;a)  初始化(停行走，开触发，buff，喊杀)   英文名
    void killNpcStart(QString);
    ///#killme()  gmcp combat(我喊杀的)  初始化(停行走，开触发，buff，喊杀)   英文名   别人主动喊得不触发
    void killmeStart(QString zhName,QString id);
    ///校验是否在战斗列表  gmcp combat  初始化(停行走，开触发，buff，喊杀)   英文名
    void fightCheck(QString zhName,QString id);
    ///处于战斗状态或者不是
    void fightting(QString status);
    ///没这个npc 开始走路
    void nokillNpc();
    ///死了一个 看列表里有没有 中文
    void npcdie(QString name);
    ///从#killnpc中截取一个个npc
    void npcList(QString &name);

    ///外部通过那个变量决定要不要传入
    void roomMessage(QByteArray roomMess);
    /* @brief 从输入数组中，截取出一行放入输出数组中*/
    void getOneStrFromArray(QByteArray &inArray, QByteArray &outArray);
    /* @brief 从数组中移除颜色结构*/
    bool removeColorFromArray(QByteArray &inArray);

    /* @brief 继续走名单重喊或者想杀名单*/
    void mingdanORwantkill();
signals:
    void sysCmd(QString);
private:
    explicit KillSys(QObject *parent = nullptr);
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
    static KillSys* m_pipe_rw;
};

#endif // KILLSYS_H
