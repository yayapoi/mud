#ifndef INIMANARGE_H
#define INIMANARGE_H

#include <globalhead.h>
#include <QSettings>

class INIManarge
{
public:
    static INIManarge* GetInstance()
    {
        if (m_pipe_rw == NULL)
        {
            if (m_pipe_rw == NULL)
                m_pipe_rw = new INIManarge();
        }
        return m_pipe_rw;
    }

    ~INIManarge();

    ///外部获取用户中英文名
    void getUserNameGmcp(UserNameGmcp& back);
    ///外部存用户中英文名
    void setUserNameGmcp(UserNameGmcp& back);
private:
    QSettings *settings;//申明一个QSetting类函数

    INIManarge();
    INIManarge& operator=(const INIManarge&);

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
    static	INIManarge* m_pipe_rw;
};

#endif // INIMANARGE_H
