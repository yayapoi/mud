#ifndef MAPCREATEVIEW_H
#define MAPCREATEVIEW_H

#include "mapCreateWindow/mapcreateroomitem.h"
#include "qmenu.h"
#include "qtimer.h"
#include <QGraphicsView>
#include <QObject>

class MapCreateView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MapCreateView(QWidget *parent = nullptr);

    ///初始化房间
    void initRoom();
    ///清空界面
    void clearView();

    ///设置随机某个控件被点击
    void setsomeClike();

    ///设置随机某个控件被点击
    void setsomeClike(int roomnum);
    ///检查两根线是否存在 true:存在
    bool checkLine(MapCreateRoomItem* beginitem, MapCreateRoomItem* endItem, QString cmd);
    ///检查两根线是否存在 true:存在
    bool checkLine(MapCreateRoomItem* beginitem, MapCreateRoomItem* endItem);

    ///刷新某控件输出线
    void flushOutItem(MapCreateRoomItem* beginitem);
    ///刷新某控件输出线
    void flushOutItem(int beginitemnum);

    ///添加线
    void addLine(MapCreateRoomItem* beginitem, MapCreateRoomItem* endItem, QString cmd);

    ///添加新房间
    void addnewItem(int roomNum, MapCreateRoomItem* beginitem, QString cmd);

    ///删除控件，同时删除线，同时删除其它控件的存档
    void deleteItem(MapCreateRoomItem*);

    ///其它地方收到合并并处理后，调用此函数合并view中房间，并删除item
    void hebingTwoItem();
protected:
    void wheelEvent(QWheelEvent *event) override;//放大缩小图片
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    ///放大倍数
    qreal m_scalingOffset=1.0;
    double _zoom_factor_base = 1.0015;
    QPointF target_scene_pos, target_viewport_pos;
    ///滚动次数
    int wheelNum=0;
    bool isMousePressed=false;

    QTimer viewportMoveTimer;
    QPoint eventpos = QPoint(0,0);
    QPoint mouseHoverPos = QPoint(0,0);
    ///右键菜单时位置
    QPointF rightMenuMouseScenePos = QPointF(0,0);
    QMenu rightMenu;//右键菜单
    QAction deleteAction;
    QAction heBingBeginAction;
    QAction heBingAction;
    QAction quxiaoHeBingAction;

    MapCreateRoomItem* clickItem=nullptr;
    MapCreateRoomItem* heBingItem=nullptr;

    QList<MapCreateRoomItem*> seletitem;
    void gentle_zoom(double factor);
    int mousePosIsLocationAtMove(QPoint mousePos);
    void moveScrollBar(int value);
    bool mouseIsOverFlowItem(QPoint mouseScenePos);
    MapCreateRoomItem* mouseIsOverFlowItem(QPoint mouseScenePos, bool& backFlag);
    void upSelectItem();//通知item不是选中状态 maincontrol
    void initRightMenu();

public slots:
    void viewportMoveTimerOut();
signals:
    ///删除添加控件，刷新io 给IOwidget 需填
    void refreshIO();
    ///删除控件时传递给外界
    void Itemdelete(MapCreateRoomItem*);
    ///当控件被点击时候传递给外界
    void itemeclick(MapCreateRoomItem*);
    void itemeMerge(MapCreateRoomItem* fromItem,MapCreateRoomItem* endItem);
};

#endif // MAPCREATEVIEW_H
