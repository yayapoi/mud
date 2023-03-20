#include "mapcreatelineitem.h"
#include "qdebug.h"
#include "qpen.h"

MapCreateLineItem::MapCreateLineItem()
{
    setFlag(QGraphicsItem::ItemIsSelectable,false);
    setFlag(QGraphicsItem::ItemIsMovable,false);
    setFlag(QGraphicsItem::ItemIsFocusable,false);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges,false);
}

MapCreateLineItem::~MapCreateLineItem()
{
    qDebug()<<"MapCreateLineItem::~MapCreateLineItem";
}

QRectF MapCreateLineItem::boundingRect() const
{
    return QGraphicsLineItem::boundingRect();
}

void MapCreateLineItem::addMyLine(MapCreateRoomItem *beginItem, MapCreateRoomItem::IOposition Ioposition,
                                  MapCreateRoomItem *endItem, MapCreateRoomItem::IOposition endIoposition)
{
    QPointF beginP=beginItem->getPointF(Ioposition,MapCreateRoomItem::OUT);
    QPointF endP=endItem->getPointF(endIoposition,MapCreateRoomItem::IN);
    //qDebug()<<"beginP--"<<beginP<<"  endP--"<<endP;
    this->setLine(beginP.x(),beginP.y(),endP.x(),endP.y());
    QPen aaa;
    aaa.setColor(Qt::black);
    aaa.setWidth(2);
    this->setPen(aaa);
    this->setZValue(120);

    BeginItem=beginItem;
    EndItem=endItem;
    //qDebug()<<"MapCreateLineItem::addMyLine this--"<<this;
    switch (Ioposition) {
    case MapCreateRoomItem::IOposition::UP:
    {
        beginItem->upItem->outLineItem.append(this);
    }
        break;
    case MapCreateRoomItem::IOposition::DOWN:
    {
        beginItem->downItem->outLineItem.append(this);
    }
        break;
    case MapCreateRoomItem::IOposition::LEFT:
    {
        beginItem->LeftItem->outLineItem.append(this);
    }
        break;
    case MapCreateRoomItem::IOposition::RIGHT:
    {
        beginItem->rightItem->outLineItem.append(this);
    }
        break;
    default:
        break;
    }

    switch (endIoposition) {
    case MapCreateRoomItem::IOposition::UP:
    {
        endItem->upItem->inLineItem.append(this);
    }
        break;
    case MapCreateRoomItem::IOposition::DOWN:
    {
        endItem->downItem->inLineItem.append(this);
    }
        break;
    case MapCreateRoomItem::IOposition::LEFT:
    {
        endItem->LeftItem->inLineItem.append(this);
    }
        break;
    case MapCreateRoomItem::IOposition::RIGHT:
    {
        endItem->rightItem->inLineItem.append(this);
    }
        break;
    default:
        break;
    }
}

void MapCreateLineItem::deleteThis()
{
    if(BeginItem!=nullptr)
    {
        if(BeginItem->upItem->outLineItem.size()!=0)
        {
            BeginItem->upItem->outLineItem.removeOne(this);
        }

        if(BeginItem->downItem->outLineItem.size()!=0)
        {
            BeginItem->downItem->outLineItem.removeOne(this);
        }

        if(BeginItem->LeftItem->outLineItem.size()!=0)
        {
            BeginItem->LeftItem->outLineItem.removeOne(this);
        }

        if(BeginItem->rightItem->outLineItem.size()!=0)
        {
            BeginItem->rightItem->outLineItem.removeOne(this);
        }
    }
    if(EndItem!=nullptr)
    {
        if(EndItem->upItem->inLineItem.size()!=0)
        {
            EndItem->upItem->inLineItem.removeOne(this);
        }

        if(EndItem->downItem->inLineItem.size()!=0)
        {
            EndItem->downItem->inLineItem.removeOne(this);
        }

        if(EndItem->LeftItem->inLineItem.size()!=0)
        {
            EndItem->LeftItem->inLineItem.removeOne(this);
        }

        if(EndItem->rightItem->inLineItem.size()!=0)
        {
            EndItem->rightItem->inLineItem.removeOne(this);
        }
    }
    BeginItem=nullptr;
    EndItem=nullptr;
    this->deleteLater();
}
