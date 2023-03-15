#ifndef MAPCREATELINEITEM_H
#define MAPCREATELINEITEM_H

#include "mapCreateWindow/mapcreateroomitem.h"
#include <QGraphicsLineItem>
#include <QObject>

class MapCreateRoomItem;

class MapCreateLineItem : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    enum { Type = UserType + 102 };
    int type() const override
    {
        return Type;
    }

    MapCreateLineItem();
    ~MapCreateLineItem();

    QRectF boundingRect() const override;
    friend bool operator<(const QPoint &s1, const QPoint &s2);

    void addMyLine(MapCreateRoomItem* beginItem,MapCreateRoomItem::IOposition,
                   MapCreateRoomItem* endItem,MapCreateRoomItem::IOposition);

    void deleteThis();
    MapCreateRoomItem* BeginItem=nullptr;
    MapCreateRoomItem* EndItem=nullptr;
};

#endif // MAPCREATELINEITEM_H
