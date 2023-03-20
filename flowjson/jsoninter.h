#ifndef JSONINTER_H
#define JSONINTER_H

#include <QObject>
#include <qjsondocument.h>
#include <QJsonObject>
#include <globalhead.h>
#include <QMap>
#include "mapCreateWindow/mapcreateroomitem.h"
#include <QPair>

class JsonInter : public QObject
{
    Q_OBJECT
public:
    static JsonInter* GetInstance()
    {
        if (m_pipe_rw == NULL)
        {
            if (m_pipe_rw == NULL)
                m_pipe_rw = new JsonInter();
        }
        return m_pipe_rw;
    }

    ~JsonInter();

    QJsonObject allDoc;
    QList<int> roomNumList;//存放房间数字，可递增
    QMap<int,QPair<roomInfo*,MapCreateRoomItem*>> roomMap;//存放房间的map

    ///插入新房间信息  doc填入  map填入  list填入
    void setnewRoomInJson(int roomNum1, QString fZH="", QString fEN="", QString SZH="", QString SEN="", QString SrdZH="", QString SrdEn="");

    ///保存至文件
    void saveRoomInFile(QString fillname);
    ///获取所有内容,成功返回true
    bool getRoomInFile(QString fillname);

    ///清空map
    void clearMap();
    ///清空房间list
    void clearList();

    ///删除房间 更新json,更新map,删除房间数字列表
    void deleteRoom(int roomNum);

    ///json中的出队和进队删除目标
    void deletejsonList(MapCreatRecItem* item, int roosnum);
    ///map中的出队和进队删除目标
    void deletemapList(MapCreatRecItem* item, int roosnum);

    ///合并两个控件的输入输出，map,json
    void itemMarge(MapCreateRoomItem* beginitem, MapCreateRoomItem* endItem);

    //计算地图中控件占用最大最小值，画布也要变化
    double minX=9999999.0;
    double maxX=-9999999.0;
    double minY=9999999.0;
    double maxY=-9999999.0;
    ///统计地图中全部控件占用面积大小
    void valueMerge(double& x, double& y);
signals:
private:
    explicit JsonInter(QObject *parent = nullptr);
    JsonInter& operator=(const JsonInter&);

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
    static	JsonInter* m_pipe_rw;
};

#endif // JSONINTER_H
