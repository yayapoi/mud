#ifndef MAPCREATRECITEM_H
#define MAPCREATRECITEM_H

#include <QGraphicsObject>
#include <QObject>

class MapCreateLineItem;

inline bool operator<(const QPoint &s1, const QPoint &s2)
{
    return (s1.x() + 9999) * 100000 + s1.y() + 9999 < (s2.x() + 9999) * 100000 + s2.y() + 9999;
}

class MapCreatRecItem : public QGraphicsObject
{
    Q_OBJECT
public:
    enum { Type = UserType + 101 };
    int type() const override
    {
        return Type;
    }
    enum itemState{
        v = 0,       //垂直模式
        h = 1   //水平模式
    };
    enum IOO{
        IN = 0,       //上面
        OUT = 1   //下面
    };

    explicit MapCreatRecItem(QGraphicsItem *parent = nullptr);

    ///设置水平还是垂直模式
    void setMyModel(itemState=itemState::v);
    QRectF boundingRect() const override;
    friend bool operator<(const QPoint &s1, const QPoint &s2);


    itemState nowState=itemState::v;
    int itemWidth=6;
    int itemHeight=30;
    qreal itemRadius = 2;

    QList<MapCreateLineItem*> inLineItem;
    QList<MapCreateLineItem*> outLineItem;

    QPointF getMyPoint(IOO);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // MAPCREATRECITEM_H
