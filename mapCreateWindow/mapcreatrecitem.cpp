#include "mapcreatrecitem.h"
#include "qpainter.h"
#include "mapCreateWindow/mapcreatelineitem.h"

MapCreatRecItem::MapCreatRecItem(QGraphicsItem *parent):QGraphicsObject(parent)
{

}

void MapCreatRecItem::setMyModel(itemState  a)
{
    switch (a) {
    case itemState::v:
    {
        nowState=itemState::v;
        itemWidth=6;
        itemHeight=30;
    }
        break;
    case itemState::h:
    {
        nowState=itemState::h;
        itemHeight=6;
        itemWidth=30;
    }
        break;
    default:
        break;
    }
}

QRectF MapCreatRecItem::boundingRect() const
{
    return QRectF(0-5, 0-5, itemWidth + 5, itemHeight + 5); //矩形大小
}

QPointF MapCreatRecItem::getMyPoint(IOO io)
{
    QPointF backPoin{0,0};
    switch (io) {
    case IOO::IN:
    {
        switch (nowState) {
        case itemState::v:
        {
            backPoin=mapToParent({static_cast<qreal>(itemWidth/2), static_cast<qreal>(itemHeight/4)});
        }
            break;
        case itemState::h:
        {
            backPoin=mapToParent({static_cast<qreal>(itemWidth/4), static_cast<qreal>(itemHeight/2)});
        }
            break;
        default:
            break;
        }
    }
        break;
    case IOO::OUT:
    {
        switch (nowState) {
        case itemState::v:
        {
            backPoin=mapToParent({static_cast<qreal>(itemWidth/2), static_cast<qreal>(itemHeight/4*3)});
        }
            break;
        case itemState::h:
        {
            backPoin=mapToParent({static_cast<qreal>(itemWidth/4*3), static_cast<qreal>(itemHeight/2)});
        }
            break;
        default:
            break;
        }
    }
        break;
    default:
        break;
    }
    return backPoin;
}

void MapCreatRecItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    //外边框颜色
    QColor outLineColor = QColor(1,118,246);
    //字体颜色
    QColor textColor = QColor(0,0,0);
    //内部底色
    QColor fillColor = QColor(241,241,241);
    //qDebug()<<"FlowGraphicsItem::paint  fillColor--"<<fillColor<<"  itemStatus--"<<itemStatus;
    painter->save();
    //大小
    QRect itemOutline(0, 0, itemWidth, itemHeight);
    // 底色
    painter->fillRect(itemOutline,fillColor);
    // 外边框
    QPen pen;
    pen.setColor(outLineColor);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawRoundedRect(itemOutline, itemRadius, itemRadius);//外边框圆角
    pen.setWidth(1);
    painter->setPen(pen);
    // 圆点
    switch (nowState) {
    case itemState::v:
    {
        pen.setColor(Qt::black);
        painter->setPen(pen);
        painter->setBrush(Qt::black);
        painter->drawEllipse(itemWidth/2-1, itemHeight/4-1,2,2);
        pen.setColor(Qt::red);
        painter->setPen(pen);
        painter->setBrush(Qt::red);
        painter->drawEllipse(itemWidth/2-1, itemHeight/4*3-1,2,2);
    }
        break;
    case itemState::h:
    {
        pen.setColor(Qt::black);
        painter->setPen(pen);
        painter->setBrush(Qt::black);
        painter->drawEllipse(itemWidth/4-1, itemHeight/2-1,2,2);
        pen.setColor(Qt::red);
        painter->setPen(pen);
        painter->setBrush(Qt::red);
        painter->drawEllipse(itemWidth/4*3-1, itemHeight/2-1,2,2);
    }
        break;
    default:
        break;
    }
    painter->restore();
}
