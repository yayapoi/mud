#ifndef MAPCREATEROOMITEM_H
#define MAPCREATEROOMITEM_H

#include "mapCreateWindow/mapcreatrecitem.h"
#include <QGraphicsObject>
#include <QObject>

struct ItemColor
{
    QColor outLineColor = QColor(1,118,246);
    QColor textColor = QColor(0,0,0);
    QColor fillColor = QColor(241,241,241);
};

class MapCreateLineItem;

class MapCreateRoomItem : public QGraphicsObject
{
    Q_OBJECT
public:
    enum { Type = UserType + 100 };
    int type() const override
    {
        return Type;
    }
    enum itemState{
        NO_STATE = 0,       //没有状态
        NORMAL_STATE = 1,   //正常状态
        SHOW_STATE = 2,     //显示状态
        HIGHLIGHT_STATE = 3,//高亮状态
        SELECTED_STATE = 4, //选中状态
        ABNORMAL_STATE = 5, //异常状态
        OPERATION_STATE = 6,//运行状态
        UPDATED_STATE = 7,  //已被更新状态
        REMOVED_STATE = 8   //已被删除状态
    };

    enum IOposition{
        UP = 0,       //上面
        DOWN = 1,   //下面
        LEFT = 2,     //左边
        RIGHT = 3//右边
    };
    enum IOO{
        IN = 0,       //上面
        OUT = 1   //下面
    };

    explicit MapCreateRoomItem(QGraphicsItem *parent = nullptr);
    ~MapCreateRoomItem();
    QRectF boundingRect() const override;
    friend bool operator<(const QPoint &s1, const QPoint &s2);

    ///房间号，初始化时候赋值
    int roomNum=0;
    ///房间名字
    QString roomName;
    int itemWidth=70;
    int itemHeight=70;
    qreal itemRadius = 2;

    ///鼠标悬浮在关闭按钮
    bool itemDeleteHover=false;
    /**@brief 记录叠加的状态，true：应用显示状态。显示状态，即显示的时候中间和右边显示，禁止删除*/
    bool itemSHOW_STATE = false;
    /**@brief 记录叠加的状态，true：应用选中状态。*/
    bool itemSELECTED_STATE = false;
    /**@brief 记录互相覆盖的状态，最后的数字是最后的状态，目前互相覆盖状态为正常状态、异常状态、运行状态、已被更新状态、已被删除状态*/
    itemState itemStatus=itemState::NO_STATE;

    MapCreatRecItem *upItem;
    MapCreatRecItem *LeftItem;
    MapCreatRecItem *rightItem;
    MapCreatRecItem *downItem;

    /** @brief 修改控件状态 */
    void changeItemState(itemState state);

    QPointF getPointF(IOposition, IOO);
    void addItem(IOposition, IOO, MapCreateLineItem*);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    /*void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;*/

    /**@brief 将两种颜色混合*/
    QColor getNewColor(QColor backgroundColor, QColor foregroundColor);
    float calculateRGBAValue(float fTranslucent1, float fTranslucent2, float RGBVlue1, float RGBVlue2);

private:

    ItemColor NORMALSTATE;
    ItemColor SHOWSTATE;
    ItemColor HIGHLIGHTSTATE;
    ItemColor SELECTEDSTATE;
    ItemColor ABNORMALSTATE;
    ItemColor OPERATIONSTATE;
    ItemColor UPDATEDSTATE;
    ItemColor REMOVEDSTATE;
};

#endif // MAPCREATEROOMITEM_H
