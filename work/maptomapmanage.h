#ifndef MAPTOMAPMANAGE_H
#define MAPTOMAPMANAGE_H

#include <QObject>
#include <unordered_map>
#include <QMap>

struct lujing{
    ///int是JsonInter的首值
    int qidian;
    ///int是JsonInter的首值
    int zhongdian;
    ///int是JsonInter的首值     路径有可能空的
    QVector<int> roomList;
    int time;
};

struct quyu{
    ///中文
    QString fn;
    QString sn;
    QString srdn;
    ///本区域全部的房间  int是JsonInter的首值
    QList<int> allroom;
    ///本区域全部的出入口房间   int是JsonInter的首值
    QList<int> IOroom;
    ///本区域所房间的权值  前两个int是JsonInter的首值  第三个是权值
    std::unordered_map<int, std::unordered_map<int, int>> itemPointMap;
    ///本区域内所有出入口之间最短路径   路径有可能空的
    QList<lujing> lujingList;
};

class MapToMapManage : public QObject
{
    Q_OBJECT
public:
    static MapToMapManage* GetInstance()
    {
        if (m_pipe_rw == NULL)
        {
            if (m_pipe_rw == NULL)
                m_pipe_rw = new MapToMapManage();
        }
        return m_pipe_rw;
    }

    ///所有点的权值 初始化必须在调用lujingListquyu()之后 前两个int是JsonInter的首值  第三个是权值或者路径最大值
    std::unordered_map<int, std::unordered_map<int, int>> itemPointMap;
    ///存着每个区域都有哪些房间
    QList<quyu> quyuList;

    ///初始化所有的区域,为初始化各区域做准备
    void initallquyu();
    ///初始化本区域的所有路径
    void lujingListquyu();
    ///寻找本区域是否已经存在 存在返回在第几个list,不存在返回-1
    int quyuInquyuMap(QString& fN,QString& sn,QString& srdn);
    ///统计本路径使用时间(还有限制，步数多但是时间短的不一定时间最少)须填
    int addTime(QVector<int> &vecvec);
    ///统计某区域内某路径使用时间(还有限制，步数多但是时间短的不一定时间最少)须填
    int addTimeInMap(QVector<int> &vecvec, std::unordered_map<int, std::unordered_map<int, int>> &vertices);

    ///初始化EASY区域，可以减少计算
    void initEasy();

    ///找到两点间最短路径  有问题返回false
    bool findLujing(int begin, int end, QVector<int>&backlujing);

    ///打印而已，不要慌
    void printf();
    ///打印而已，不要慌
    void printfitemPointMap(std::unordered_map<int, std::unordered_map<int, int>>& sadf);
    ///寻找最短路径  注意，最后一个点一定要存在与第一个int中,否则查不出路径
    QVector<int> shortest_path(int start, int finish, std::unordered_map<int, std::unordered_map<int, int>> &vertices);
signals:
private:
    explicit MapToMapManage(QObject *parent = nullptr);

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
    static MapToMapManage* m_pipe_rw;
};

#endif // MAPTOMAPMANAGE_H
