#include "mapcreateroomitem.h"
#include "qdebug.h"
#include "qpainter.h"
#include <QGraphicsSceneMouseEvent>
#include "mapCreateWindow/mapcreatelineitem.h"
#include <QDebug>

MapCreateRoomItem::MapCreateRoomItem(QGraphicsItem *parent):QGraphicsObject(parent)
{
    //正常状态
    NORMALSTATE.outLineColor = QColor(1, 118, 246);
    NORMALSTATE.textColor = QColor(7, 33, 62);
    NORMALSTATE.fillColor = QColor(241,241,241);
    //显示状态
    SHOWSTATE.outLineColor = QColor(1,118,246);
    SHOWSTATE.textColor = QColor(255,255,255);
    SHOWSTATE.fillColor = QColor(1,118,246);

    HIGHLIGHTSTATE.outLineColor = QColor(250,174,19);
    HIGHLIGHTSTATE.textColor = QColor(255,255,255);
    HIGHLIGHTSTATE.fillColor = QColor(250,174,19);
    //选中状态
    SELECTEDSTATE.outLineColor = QColor(1,118,246);
    SELECTEDSTATE.textColor = QColor(7, 33, 62);
    SELECTEDSTATE.fillColor = QColor(1,118,246,50);
    //异常状态
    ABNORMALSTATE.outLineColor = QColor(255, 59, 48);
    ABNORMALSTATE.textColor = QColor(255, 59, 48);
    ABNORMALSTATE.fillColor = QColor(241,241,241);
    //运行状态
    OPERATIONSTATE.outLineColor = QColor(82, 196, 26);
    OPERATIONSTATE.textColor = QColor(82, 196, 26);
    OPERATIONSTATE.fillColor = QColor(241,241,241);
    //已被更新状态
    UPDATEDSTATE.outLineColor = QColor(124, 145, 191);
    UPDATEDSTATE.textColor = QColor(124, 145, 191);
    UPDATEDSTATE.fillColor = QColor(241,241,241);
    //已被删除状态
    REMOVEDSTATE.outLineColor = QColor(66, 66, 66);
    REMOVEDSTATE.textColor = QColor(66, 66, 66);
    REMOVEDSTATE.fillColor = QColor(241,241,241);


    setAcceptHoverEvents(true);
    setZValue(50);
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemSendsGeometryChanges);

    upItem=new MapCreatRecItem(this);
    upItem->setMyModel(MapCreatRecItem::itemState::h);
    upItem->moveBy(20,0);

    LeftItem=new MapCreatRecItem(this);
    LeftItem->moveBy(0,20);

    rightItem=new MapCreatRecItem(this);
    rightItem->moveBy(itemWidth-rightItem->itemWidth,20);

    downItem=new MapCreatRecItem(this);
    downItem->setMyModel(MapCreatRecItem::itemState::h);
    //qDebug()<<"MapCreateRoomItem   itemHeight---"<<itemHeight<<"   rightItem->itemHeight---"<<rightItem->itemHeight;
    downItem->moveBy(20,itemHeight-downItem->itemHeight);

    //setAcceptHoverEvents(true);
}

MapCreateRoomItem::~MapCreateRoomItem()
{
    qDebug()<<"MapCreateRoomItem::~MapCreateRoomItem()";
}

QRectF MapCreateRoomItem::boundingRect() const
{
    return QRectF(0-5, 0-5, itemWidth + 5, itemHeight + 5); //矩形大小
}

void MapCreateRoomItem::changeItemState(itemState state)
{
    switch (state){
    case NORMAL_STATE:
        itemStatus=NORMAL_STATE;
        break;
    case SHOW_STATE:
        itemSHOW_STATE = true;
        break;
    case SELECTED_STATE:
        itemSELECTED_STATE = true;
        break;
    case ABNORMAL_STATE:
        itemStatus=ABNORMAL_STATE;
        break;
    case OPERATION_STATE:
        itemStatus=OPERATION_STATE;
        break;
    case UPDATED_STATE:
        itemStatus=UPDATED_STATE;
        break;
    case REMOVED_STATE:
        itemStatus=REMOVED_STATE;
        break;
    }
}

void MapCreateRoomItem::fluseLine()
{
    if(upItem->inLineItem.size()!=0)
    {
        QPointF beginP=getPointF(MapCreateRoomItem::UP,MapCreateRoomItem::IN);
        foreach(MapCreateLineItem* oneitem,upItem->inLineItem)
        {
            //qDebug()<<"MapCreateLineItem::addMyLine oneitem--"<<oneitem;
            oneitem->setLine(oneitem->line().x1(),oneitem->line().y1(),beginP.x(),beginP.y());
        }
    }
    if(upItem->outLineItem.size()!=0)
    {
        QPointF beginP=getPointF(MapCreateRoomItem::UP,MapCreateRoomItem::OUT);
        foreach(MapCreateLineItem* oneitem,upItem->outLineItem)
        {
            oneitem->setLine(beginP.x(),beginP.y(),oneitem->line().x2(),oneitem->line().y2());
        }
    }
    if(downItem->inLineItem.size()!=0)
    {
        QPointF beginP=getPointF(MapCreateRoomItem::DOWN,MapCreateRoomItem::IN);
        foreach(MapCreateLineItem* oneitem,downItem->inLineItem)
        {
            oneitem->setLine(oneitem->line().x1(),oneitem->line().y1(),beginP.x(),beginP.y());
        }
    }
    if(downItem->outLineItem.size()!=0)
    {
        QPointF beginP=getPointF(MapCreateRoomItem::DOWN,MapCreateRoomItem::OUT);
        foreach(MapCreateLineItem* oneitem,downItem->outLineItem)
        {
            oneitem->setLine(beginP.x(),beginP.y(),oneitem->line().x2(),oneitem->line().y2());
        }
    }
    if(LeftItem->inLineItem.size()!=0)
    {
        QPointF beginP=getPointF(MapCreateRoomItem::LEFT,MapCreateRoomItem::IN);
        foreach(MapCreateLineItem* oneitem,LeftItem->inLineItem)
        {
            oneitem->setLine(oneitem->line().x1(),oneitem->line().y1(),beginP.x(),beginP.y());
        }
    }
    if(LeftItem->outLineItem.size()!=0)
    {
        QPointF beginP=getPointF(MapCreateRoomItem::LEFT,MapCreateRoomItem::OUT);
        foreach(MapCreateLineItem* oneitem,LeftItem->outLineItem)
        {
            oneitem->setLine(beginP.x(),beginP.y(),oneitem->line().x2(),oneitem->line().y2());
        }
    }
    if(rightItem->inLineItem.size()!=0)
    {
        QPointF beginP=getPointF(MapCreateRoomItem::RIGHT,MapCreateRoomItem::IN);
        foreach(MapCreateLineItem* oneitem,rightItem->inLineItem)
        {
            oneitem->setLine(oneitem->line().x1(),oneitem->line().y1(),beginP.x(),beginP.y());
        }
    }
    if(rightItem->outLineItem.size()!=0)
    {
        QPointF beginP=getPointF(MapCreateRoomItem::RIGHT,MapCreateRoomItem::OUT);
        foreach(MapCreateLineItem* oneitem,rightItem->outLineItem)
        {
            oneitem->setLine(beginP.x(),beginP.y(),oneitem->line().x2(),oneitem->line().y2());
        }
    }
}

QPointF MapCreateRoomItem::getPointF(IOposition Ioposition, IOO io)
{
    QPointF backPoin{0,0};
    switch (Ioposition) {
    case IOposition::UP:
    {
        switch (io) {
        case IOO::IN:
        {
            backPoin=upItem->getMyPoint(MapCreatRecItem::IOO::IN);
        }
            break;
        case IOO::OUT:
        {
            backPoin=upItem->getMyPoint(MapCreatRecItem::IOO::OUT);
        }
            break;
        default:
            break;
        }
    }
        break;
    case IOposition::DOWN:
    {
        switch (io) {
        case IOO::IN:
        {
            backPoin=downItem->getMyPoint(MapCreatRecItem::IOO::IN);
        }
            break;
        case IOO::OUT:
        {
            backPoin=downItem->getMyPoint(MapCreatRecItem::IOO::OUT);
        }
            break;
        default:
            break;
        }
    }
        break;
    case IOposition::LEFT:
    {
        switch (io) {
        case IOO::IN:
        {
            backPoin=LeftItem->getMyPoint(MapCreatRecItem::IOO::IN);
        }
            break;
        case IOO::OUT:
        {
            backPoin=LeftItem->getMyPoint(MapCreatRecItem::IOO::OUT);
        }
            break;
        default:
            break;
        }
    }
        break;
    case IOposition::RIGHT:
    {
        switch (io) {
        case IOO::IN:
        {
            backPoin=rightItem->getMyPoint(MapCreatRecItem::IOO::IN);
        }
            break;
        case IOO::OUT:
        {
            backPoin=rightItem->getMyPoint(MapCreatRecItem::IOO::OUT);
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
    //qDebug()<<"backPoin--"<<backPoin<<"  mapToParent(backPoin)---"<<mapToParent(backPoin);

    return mapToParent(backPoin);
    //return backPoin;
}

void MapCreateRoomItem::addItem(IOposition Ioposition, IOO io, MapCreateLineItem *item)
{
    switch (Ioposition) {
    case IOposition::UP:
    {
        switch (io) {
        case IOO::IN:
        {
            upItem->inLineItem.append(item);
        }
            break;
        case IOO::OUT:
        {
            upItem->outLineItem.append(item);
        }
            break;
        default:
            break;
        }
    }
        break;
    case IOposition::DOWN:
    {
        switch (io) {
        case IOO::IN:
        {
            downItem->inLineItem.append(item);
        }
            break;
        case IOO::OUT:
        {
            downItem->outLineItem.append(item);
        }
            break;
        default:
            break;
        }
    }
        break;
    case IOposition::LEFT:
    {
        switch (io) {
        case IOO::IN:
        {
            LeftItem->inLineItem.append(item);
        }
            break;
        case IOO::OUT:
        {
            LeftItem->outLineItem.append(item);
        }
            break;
        default:
            break;
        }
    }
        break;
    case IOposition::RIGHT:
    {
        switch (io) {
        case IOO::IN:
        {
            rightItem->inLineItem.append(item);
        }
            break;
        case IOO::OUT:
        {
            rightItem->outLineItem.append(item);
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
}

void MapCreateRoomItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    //外边框颜色
    QColor outLineColor = NORMALSTATE.outLineColor;
    //字体颜色
    QColor textColor = NORMALSTATE.textColor;
    //内部底色
    QColor fillColor = NORMALSTATE.fillColor;
    // 判断状态
    switch (itemStatus){
    case NORMAL_STATE:
    {
        outLineColor = NORMALSTATE.outLineColor;
        textColor = NORMALSTATE.textColor;
        fillColor = NORMALSTATE.fillColor;
    }
        break;
    case ABNORMAL_STATE:
    {
        outLineColor = ABNORMALSTATE.outLineColor;
        textColor = ABNORMALSTATE.textColor;
        fillColor = ABNORMALSTATE.fillColor;
    }
        break;
    case OPERATION_STATE:
    {
        outLineColor = OPERATIONSTATE.outLineColor;
        textColor = OPERATIONSTATE.textColor;
        fillColor = OPERATIONSTATE.fillColor;
    }
        break;
    case UPDATED_STATE:
    {
        outLineColor = UPDATEDSTATE.outLineColor;
        textColor = UPDATEDSTATE.textColor;
        fillColor = UPDATEDSTATE.fillColor;
    }
        break;
    case REMOVED_STATE:
    {
        outLineColor = REMOVEDSTATE.outLineColor;
        textColor = REMOVEDSTATE.textColor;
        fillColor = REMOVEDSTATE.fillColor;
    }
        break;
    }
    //qDebug()<<"FlowGraphicsItem::paint  outLineColor--"<<outLineColor;
    //qDebug()<<"FlowGraphicsItem::paint  textColor--"<<textColor;
    //qDebug()<<"FlowGraphicsItem::paint  fillColor--"<<fillColor<<"  itemSHOW_STATE--"<<itemSHOW_STATE<<"  itemSELECTED_STATE--"<<itemSELECTED_STATE;
    if(itemSHOW_STATE)
    {
        fillColor = SHOWSTATE.fillColor;
        textColor = SHOWSTATE.textColor;
        //outLineColor = SHOWSTATE.outLineColor;
    }
    //qDebug()<<"FlowGraphicsItem::paint  fillColor--"<<fillColor;
    if(itemSELECTED_STATE)
    {
        //qDebug()<<"FlowGraphicsItem::paint  SELECTEDSTATE.fillColor--"<<SELECTEDSTATE.fillColor;
        if(itemSHOW_STATE)//谨记，因为直接颜色叠加的话，会使用正常状态的白色叠加，导致所有颜色变淡，只能使用此方法
        {
            fillColor = QColor(0, 105, 221);
            //outLineColor = SELECTEDSTATE.outLineColor;
        }
        else
        {
            fillColor = SELECTEDSTATE.fillColor;
            //outLineColor = SELECTEDSTATE.outLineColor;
        }
        //fillColor = getNewColor(Qt::green,fillColor);
    }


    //qDebug()<<"FlowGraphicsItem::paint  fillColor--"<<fillColor<<"  itemStatus--"<<itemStatus;
    painter->save();
    //大小
    QRect itemOutline(0, 0, itemWidth, itemHeight);
    // 底色
    painter->fillRect(itemOutline,fillColor);

    // 外边框
    QPen pen;

    //删除按钮
    /*if(itemDeleteHover)
    {
        pen.setColor(Qt::red);
    }
    else
    {
        pen.setColor(Qt::black);
    }
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawRect(itemWidth-10, 0, 10, 10);
    painter->drawLine(itemWidth-10, 0, itemWidth, 10);
    painter->drawLine(itemWidth-10, 10, itemWidth, 0);*/

    pen.setColor(outLineColor);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawRoundedRect(itemOutline, itemRadius, itemRadius);//外边框圆角


    QPen pen1;
    pen1.setColor(textColor);
    pen1.setWidth(2);
    painter->setPen(pen1);
    QFont font;//设置字体，下面设置字体属性
    font.setPointSize(11);//字体点大小
    painter->setFont(font);
    if(roomName.count()<=4)
    {
        painter->drawText(10,25,roomName);
    }
    else
    {
        painter->drawText(10,20,roomName.mid(0,4));
        painter->drawText(10,35,roomName.mid(4));
    }
    painter->drawText(20,50,QString::number(roomNum));
    painter->restore();
}

void MapCreateRoomItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug()<<"MapCreateRoomItem   mousePressEvent---"<<event->pos();
    this->setZValue(100);
    QGraphicsObject::mousePressEvent(event);
}

void MapCreateRoomItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug()<<"MapCreateRoomItem   mouseMoveEvent---";
    /*if(itemWidth-10<event->pos().x() && event->pos().x()<itemWidth && 0<event->pos().y() && event->pos().y()<10)
    {
//qDebug()<<"MapCreateRoomItem   hoverEnterEvent---delete";
        itemDeleteHover=true;
    }
    else
    {
//qDebug()<<"MapCreateRoomItem   hoverEnterEvent---delete";
        itemDeleteHover=false;
    }*/
    if(upItem->inLineItem.size()!=0)
    {
        QPointF beginP=getPointF(MapCreateRoomItem::UP,MapCreateRoomItem::IN);
        foreach(MapCreateLineItem* oneitem,upItem->inLineItem)
        {
            //qDebug()<<"MapCreateLineItem::addMyLine oneitem--"<<oneitem;
            oneitem->setLine(oneitem->line().x1(),oneitem->line().y1(),beginP.x(),beginP.y());
        }
    }
    if(upItem->outLineItem.size()!=0)
    {
        QPointF beginP=getPointF(MapCreateRoomItem::UP,MapCreateRoomItem::OUT);
        foreach(MapCreateLineItem* oneitem,upItem->outLineItem)
        {
            oneitem->setLine(beginP.x(),beginP.y(),oneitem->line().x2(),oneitem->line().y2());
        }
    }
    if(downItem->inLineItem.size()!=0)
    {
        QPointF beginP=getPointF(MapCreateRoomItem::DOWN,MapCreateRoomItem::IN);
        foreach(MapCreateLineItem* oneitem,downItem->inLineItem)
        {
            oneitem->setLine(oneitem->line().x1(),oneitem->line().y1(),beginP.x(),beginP.y());
        }
    }
    if(downItem->outLineItem.size()!=0)
    {
        QPointF beginP=getPointF(MapCreateRoomItem::DOWN,MapCreateRoomItem::OUT);
        foreach(MapCreateLineItem* oneitem,downItem->outLineItem)
        {
            oneitem->setLine(beginP.x(),beginP.y(),oneitem->line().x2(),oneitem->line().y2());
        }
    }
    if(LeftItem->inLineItem.size()!=0)
    {
        QPointF beginP=getPointF(MapCreateRoomItem::LEFT,MapCreateRoomItem::IN);
        foreach(MapCreateLineItem* oneitem,LeftItem->inLineItem)
        {
            oneitem->setLine(oneitem->line().x1(),oneitem->line().y1(),beginP.x(),beginP.y());
        }
    }
    if(LeftItem->outLineItem.size()!=0)
    {
        QPointF beginP=getPointF(MapCreateRoomItem::LEFT,MapCreateRoomItem::OUT);
        foreach(MapCreateLineItem* oneitem,LeftItem->outLineItem)
        {
            oneitem->setLine(beginP.x(),beginP.y(),oneitem->line().x2(),oneitem->line().y2());
        }
    }
    if(rightItem->inLineItem.size()!=0)
    {
        QPointF beginP=getPointF(MapCreateRoomItem::RIGHT,MapCreateRoomItem::IN);
        foreach(MapCreateLineItem* oneitem,rightItem->inLineItem)
        {
            oneitem->setLine(oneitem->line().x1(),oneitem->line().y1(),beginP.x(),beginP.y());
        }
    }
    if(rightItem->outLineItem.size()!=0)
    {
        QPointF beginP=getPointF(MapCreateRoomItem::RIGHT,MapCreateRoomItem::OUT);
        foreach(MapCreateLineItem* oneitem,rightItem->outLineItem)
        {
            oneitem->setLine(beginP.x(),beginP.y(),oneitem->line().x2(),oneitem->line().y2());
        }
    }
    QGraphicsObject::mouseMoveEvent(event);
}

void MapCreateRoomItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug()<<"MapCreateRoomItem   mouseReleaseEvent---";
    this->setZValue(50);
    QGraphicsObject::mouseReleaseEvent(event);
}

void MapCreateRoomItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug()<<"MapCreateRoomItem   mouseDoubleClickEvent---";
    QGraphicsObject::mouseDoubleClickEvent(event);
}

void MapCreateRoomItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //qDebug()<<"MapCreateRoomItem   honerEnterEvent---"<<this;
    QGraphicsObject::hoverEnterEvent(event);
}

void MapCreateRoomItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    //qDebug()<<"MapCreateRoomItem   hoverLeaveEvent---"<<this;
    QGraphicsObject::hoverLeaveEvent(event);
}

/*void MapCreateRoomItem::focusInEvent(QFocusEvent *event)
{
//qDebug()<<"MapCreateRoomItem   focusInEvent---"<<this;
    //changeItemState(itemState::SELECTED_STATE);
    QGraphicsObject::focusInEvent(event);
}

void MapCreateRoomItem::focusOutEvent(QFocusEvent *event)
{
    //changeItemState(itemState::NORMAL_STATE);
//qDebug()<<"MapCreateRoomItem   focusOutEvent---"<<this;
    QGraphicsObject::focusOutEvent(event);
}*/

QColor MapCreateRoomItem::getNewColor(QColor backgroundColor, QColor foregroundColor)
{
    //处理叠加的RGB和透明度
    //处理两种颜色叠加时透明度a-alpha值
    /*float fTranslucent1 = backgroundColor.alpha() / 255.0;
        float fTranslucent2 = foregroundColor.alpha() / 255.0;
        float fTranslucent = fTranslucent1 + fTranslucent2 - fTranslucent1 * fTranslucent2;
        //计算R-Red值
        float fRed1 = backgroundColor.red() / 255.0;
        float fRed2 = foregroundColor.red() / 255.0;
        float fRed = calculateRGBAValue(fTranslucent1, fTranslucent2, fRed1, fRed2);

        //计算G - Green值
        float fGreen1 = backgroundColor.green() / 255.0;
        float fGreen2 = foregroundColor.green() / 255.0;
        float fGreen = calculateRGBAValue(fTranslucent1, fTranslucent2, fGreen1, fGreen2);

        //计算B - Blue值
        float fBlue1 = backgroundColor.blue() / 255.0;
        float fBlue2 = foregroundColor.blue() / 255.0;
        float fBlue = calculateRGBAValue(fTranslucent1, fTranslucent2, fBlue1, fBlue2);*/
    float fRed1 = backgroundColor.red();
    float fRed2 = foregroundColor.red();
    float fRed = (fRed1+fRed2)/2;

    //计算G - Green值
    float fGreen1 = backgroundColor.green();
    float fGreen2 = foregroundColor.green();
    float fGreen = (fGreen1+fGreen2)/2;

    //计算B - Blue值
    float fBlue1 = backgroundColor.blue();
    float fBlue2 = foregroundColor.blue();
    float fBlue = (fBlue1+fBlue2)/2;
    QColor backcoloe=QColor(fRed, fGreen, fBlue);
    //qDebug()<<"FlowGraphicsItem::getNewColor"<<"  backgroundColor--"<<backgroundColor<<"  foregroundColor--"<<foregroundColor<<"  backcoloe--"<<backcoloe;
    return backcoloe;
}

float MapCreateRoomItem::calculateRGBAValue(float fTranslucent1, float fTranslucent2, float RGBVlue1, float RGBVlue2)
{
    return (RGBVlue1 * fTranslucent1 * (1.0 - fTranslucent2) + RGBVlue2 * fTranslucent2) / (fTranslucent1 + fTranslucent2 - fTranslucent1 * fTranslucent2);  //计算两个叠加后的值
}
