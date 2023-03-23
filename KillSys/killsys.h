#ifndef KILLSYS_H
#define KILLSYS_H

#include <QObject>

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

    ///要杀的npc名字
    QString npcname;

    ///#killmpc()  初始化(停行走，开触发，buff，喊杀)
    void killNpcStart(QString);
    ///没这个npc 开始走路
    void nokillNpc(QString);
    ///打完了  再打一个
    void againkillNpc(QString);
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
