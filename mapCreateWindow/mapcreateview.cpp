#include "mapcreateview.h"
#include "mapCreateWindow/mapcreateroomitem.h"
#include "qapplication.h"
#include "qdebug.h"
#include "qevent.h"
#include <qmath.h>
#include <QScrollBar>
#include <mapCreateWindow/mapcreatelineitem.h>
#include "flowjson/jsoninter.h"
#include "qjsonarray.h"

MapCreateView::MapCreateView(QWidget *parent):QGraphicsView(parent)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    setDragMode(QGraphicsView::RubberBandDrag);

    initRightMenu();
    viewportMoveTimer.setInterval(50);
    connect(&viewportMoveTimer,&QTimer::timeout,this,&MapCreateView::viewportMoveTimerOut);
    QGraphicsScene* testScene=new QGraphicsScene;
    testScene->setSceneRect(-10000,-10000,20000,20000);
    setScene(testScene);
    connect(testScene,&QGraphicsScene::selectionChanged,this,[this](){
        //qDebug()<<"QGraphicsScene::selectionChanged----";
        /*QList<QGraphicsItem*> allList=items();
        for(int num=0;num<allList.size();num++)
        {
            if(allList[num]->type()==MapCreateRoomItem::Type)
            {
                if(((MapCreateRoomItem*)allList[num])->itemSELECTED_STATE)
                {
                    ((MapCreateRoomItem*)allList[num])->itemSELECTED_STATE=false;
                    ((MapCreateRoomItem*)allList[num])->update();
                }
            }
        }*/
        for(int num=0;num<seletitem.size();num++)
        {
            if(seletitem[num]->type()==MapCreateRoomItem::Type)
            {
                ((MapCreateRoomItem*)seletitem[num])->itemSELECTED_STATE=false;
                ((MapCreateRoomItem*)seletitem[num])->update();
            }
        }
        seletitem.clear();
        QList<QGraphicsItem*> selelist=scene()->selectedItems();
        for(int num=0;num<selelist.size();num++)
        {
            if(selelist[num]->type()==MapCreateRoomItem::Type)
            {
                //qDebug()<<"QGraphicsScene::selectionChanged----111";
                ((MapCreateRoomItem*)selelist[num])->itemSELECTED_STATE=true;
                ((MapCreateRoomItem*)selelist[num])->update();
                seletitem.append(((MapCreateRoomItem*)selelist[num]));
            }
        }
    });
    /*connect(this,&MapCreateView::rubberBandChanged,[&](QRect rubberBandRect, QPointF fromScenePoint, QPointF toScenePoint){
        //qDebug()<<"rubberBandRect--"<<rubberBandRect<<"   fromScenePoint--"<<fromScenePoint<<"  toScenePoint--"<<toScenePoint;
        if(rubberBandRect.isEmpty())
        {
            //当橡皮筋停止时，告诉所有的控件不可改变，此值变为false
            foreach(auto oneItem,((QGraphicsScene*)scene())->items())
            {
                if(oneItem->type()==MapCreateRoomItem::Type)
                {
                    ((MapCreateRoomItem*)oneItem)->setSelectEnable(false);
                }
            }
            setItemSelectOnce=false;
        }
        else
        {
            if(setItemSelectOnce==false)
            {
                foreach(auto oneItem,((QGraphicsScene*)scene())->items())
                {
                    if(oneItem->type()==MapCreateRoomItem::Type)
                    {
                        ((MapCreateRoomItem*)oneItem)->setSelectEnable(true);
                        ((MapCreateRoomItem*)oneItem)->itemSELECTED_STATE=false;
                        oneItem->setSelected(false);
                        //oneItem->update();
                    }
                }
                //当橡皮筋拖拉时，告诉所有的控件应当接收选择改变并且只告诉一次，此值变为true
                setItemSelectOnce=true;
            }
        }
    });*/
}

void MapCreateView::initRoom()
{
    auto mapiter=JsonInter::GetInstance()->roomMap.begin();
    while (mapiter!=JsonInter::GetInstance()->roomMap.end()) {
        MapCreateRoomItem* testroom=new MapCreateRoomItem;
        testroom->setPos(mapiter.value().first->roomPoint);
        testroom->roomNum=mapiter.key();
        testroom->roomName=mapiter->first->roomZH;
        scene()->addItem(testroom);
        mapiter.value().second=testroom;
        mapiter++;
    }
    //连线
    mapiter=JsonInter::GetInstance()->roomMap.begin();
    while (mapiter!=JsonInter::GetInstance()->roomMap.end()) {
        QList<OutInfo> outInfoList=mapiter.value().first->outInfo;
        for(int roomnum=0; roomnum<outInfoList.size(); roomnum++)
        {
            auto endIter=JsonInter::GetInstance()->roomMap.find(outInfoList[roomnum].room);
            if(!checkLine(mapiter.value().second, endIter.value().second, outInfoList[roomnum].outcmd))
            {
                addLine(mapiter.value().second, endIter.value().second, outInfoList[roomnum].outcmd);
            }
        }
        mapiter++;
    }
    setsomeClike();
}

void MapCreateView::clearView()
{
    ///放大倍数
    m_scalingOffset=1.0;
    _zoom_factor_base = 1.0015;
    ///滚动次数
    wheelNum=0;
    isMousePressed=false;

    viewportMoveTimer.stop();
    eventpos = QPoint(0,0);
    mouseHoverPos = QPoint(0,0);

    clickItem=nullptr;
    heBingItem=nullptr;

    scene()->clear();
}

void MapCreateView::setsomeClike()
{
    qDebug()<<"QGraphicsScene::setsomeClike----";
    if(clickItem!=nullptr)
    {
        clickItem->itemSHOW_STATE=false;
        clickItem->itemSELECTED_STATE=false;
        clickItem->update();
    }
    if(!JsonInter::GetInstance()->roomMap.isEmpty())
    {
        clickItem=JsonInter::GetInstance()->roomMap.begin()->second;
        clickItem->itemSHOW_STATE=true;
        emit itemeclick(clickItem);
    }
}

void MapCreateView::setsomeClike(int roomnum)
{
    qDebug()<<"QGraphicsScene::setsomeClike(int roomnum)----";
    if(clickItem!=nullptr)
    {
        clickItem->itemSHOW_STATE=false;
        clickItem->itemSELECTED_STATE=false;
        clickItem->update();
    }
    if(!JsonInter::GetInstance()->roomMap.isEmpty())
    {
        auto mapiter=JsonInter::GetInstance()->roomMap.find(roomnum);
        if(mapiter!=JsonInter::GetInstance()->roomMap.end())
        {
            clickItem=mapiter->second;
            clickItem->itemSHOW_STATE=true;
            clickItem->update();
            emit itemeclick(clickItem);
        }
    }
}

bool MapCreateView::checkLine(MapCreateRoomItem *beginitem, MapCreateRoomItem *endItem, QString cmd)
{
    bool findbool=false;
    if(cmd=="w" || cmd=="west" || cmd=="wd" || cmd=="westdown" || cmd=="wu" || cmd=="westup")
    {
        foreach(auto oneLine,beginitem->LeftItem->outLineItem)
        {
            if(oneLine->EndItem==endItem)
            {
                findbool=true;
                break;
            }
        }
    }
    else if(cmd=="north"|| cmd=="n" || cmd=="nu" || cmd=="nd" || cmd=="ne" || cmd=="nw" || cmd=="northup" || cmd=="northdown" || cmd=="northeast" || cmd=="northwest")
    {
        foreach(auto oneLine,beginitem->upItem->outLineItem)
        {
            if(oneLine->EndItem==endItem)
            {
                findbool=true;
                break;
            }
        }
    }
    else if(cmd=="south" || cmd=="s" || cmd=="su" || cmd=="sd" || cmd=="se" || cmd=="sw" || cmd=="southup" || cmd=="southdown" || cmd=="southeast" || cmd=="southwest")
    {
        foreach(auto oneLine,beginitem->downItem->outLineItem)
        {
            if(oneLine->EndItem==endItem)
            {
                findbool=true;
                break;
            }
        }
    }
    else if(cmd=="e" || cmd=="east" || cmd=="eu" || cmd=="ed" || cmd=="eastup" || cmd=="eastdown")
    {
        foreach(auto oneLine,beginitem->rightItem->outLineItem)
        {
            if(oneLine->EndItem==endItem)
            {
                findbool=true;
                break;
            }
        }
    }
    else if(cmd=="enter" || cmd=="out"|| cmd=="up" || cmd=="down" || cmd=="u" || cmd=="d"|| cmd=="特殊方向")
    {
        findbool=checkLine(beginitem,endItem);
    }
    return findbool;
}

bool MapCreateView::checkLine(MapCreateRoomItem *beginitem, MapCreateRoomItem *endItem)
{
    bool findbool=false;
    foreach(auto oneLine,beginitem->LeftItem->outLineItem)
    {
        if(oneLine->EndItem==endItem)
        {
            findbool=true;
            break;
        }
    }
    if(!findbool)
    {
        foreach(auto oneLine,beginitem->rightItem->outLineItem)
        {
            if(oneLine->EndItem==endItem)
            {
                findbool=true;
                break;
            }
        }
    }
    if(!findbool)
    {
        foreach(auto oneLine,beginitem->upItem->outLineItem)
        {
            if(oneLine->EndItem==endItem)
            {
                findbool=true;
                break;
            }
        }
    }
    if(!findbool)
    {
        foreach(auto oneLine,beginitem->downItem->outLineItem)
        {
            if(oneLine->EndItem==endItem)
            {
                findbool=true;
                break;
            }
        }
    }
    return findbool;
}

void MapCreateView::flushOutItem(MapCreateRoomItem *beginitem)
{
    auto mapiter=JsonInter::GetInstance()->roomMap.begin();
    while (mapiter!=JsonInter::GetInstance()->roomMap.end()) {
        bool findBool=false;
        if(mapiter.value().second==beginitem)
        {
            flushOutItem(mapiter.key());
            findBool=true;
        }
        if(findBool)
        {
            break;
        }
        mapiter++;
    }
}

void MapCreateView::flushOutItem(int beginitemnum)
{
    auto mapiter=JsonInter::GetInstance()->roomMap.find(beginitemnum);
    if(mapiter!=JsonInter::GetInstance()->roomMap.end())
    {
        QList<OutInfo> outList=mapiter->first->outInfo;
        QList<MapCreateLineItem*> ItemList;
        for(int num=0; num<mapiter->second->upItem->outLineItem.size(); num++)
        {
            bool findbool=false;
            foreach(auto oneOut,outList)
            {
                if((mapiter->second->upItem->outLineItem)[num]->EndItem->roomNum==oneOut.room)
                {
                    findbool=true;
                    break;
                }
            }
            if(!findbool)
            {
                ItemList.append((mapiter->second->upItem->outLineItem)[num]);
            }
        }
        //一、删除view中连线，二、更新json,三、更新map中信息
        foreach(auto item,ItemList)
        {
            //更新json
            //获取json
            QJsonObject allObj=JsonInter::GetInstance()->allDoc;
            QJsonObject roomobj=allObj.value(QString::number(item->EndItem->roomNum)).toObject();
            QJsonArray inArray=roomobj.value("parent_items").toArray();
            //获取数据
            for(int num=0; num<inArray.count(); num++)
            {
                if(inArray[num]==beginitemnum)
                {
                    inArray.removeAt(num);
                    break;
                }
            }
            //插入json
            roomobj.insert("parent_items",inArray);
            allObj.insert(QString::number(item->EndItem->roomNum),roomobj);
            JsonInter::GetInstance()->allDoc=allObj;


            //更新map中信息
            auto nowmapiter=JsonInter::GetInstance()->roomMap.find(item->EndItem->roomNum);
            if(nowmapiter!=JsonInter::GetInstance()->roomMap.end())
            {
                nowmapiter->first->fromRoomList.removeOne(beginitemnum);
            }

            //删除view中连线
            item->EndItem->downItem->inLineItem.removeOne(item);
            mapiter->second->upItem->outLineItem.removeOne(item);
            scene()->removeItem(item);
            item->deleteLater();
        }




        ItemList.clear();
        for(int num=0; num<mapiter->second->downItem->outLineItem.size(); num++)
        {
            bool findbool=false;
            foreach(auto oneOut,outList)
            {
                if((mapiter->second->downItem->outLineItem)[num]->EndItem->roomNum==oneOut.room)
                {
                    findbool=true;
                    break;
                }
            }
            if(!findbool)
            {
                ItemList.append((mapiter->second->downItem->outLineItem)[num]);
            }
        }
        //删除list中连线，并更新json
        foreach(auto item,ItemList)
        {
            //更新json
            //获取json
            QJsonObject allObj=JsonInter::GetInstance()->allDoc;
            QJsonObject roomobj=allObj.value(QString::number(item->EndItem->roomNum)).toObject();
            QJsonArray inArray=roomobj.value("parent_items").toArray();
            //获取数据
            for(int num=0; num<inArray.count(); num++)
            {
                if(inArray[num]==beginitemnum)
                {
                    inArray.removeAt(num);
                    break;
                }
            }
            //插入json
            roomobj.insert("parent_items",inArray);
            allObj.insert(QString::number(item->EndItem->roomNum),roomobj);
            JsonInter::GetInstance()->allDoc=allObj;


            //更新map中信息
            auto nowmapiter=JsonInter::GetInstance()->roomMap.find(item->EndItem->roomNum);
            if(nowmapiter!=JsonInter::GetInstance()->roomMap.end())
            {
                nowmapiter->first->fromRoomList.removeOne(beginitemnum);
            }

            //删除view中连线
            item->EndItem->upItem->inLineItem.removeOne(item);
            mapiter->second->downItem->outLineItem.removeOne(item);
            scene()->removeItem(item);
            item->deleteLater();
        }





        ItemList.clear();
        for(int num=0; num<mapiter->second->LeftItem->outLineItem.size(); num++)
        {
            bool findbool=false;
            foreach(auto oneOut,outList)
            {
                if((mapiter->second->LeftItem->outLineItem)[num]->EndItem->roomNum==oneOut.room)
                {
                    findbool=true;
                    break;
                }
            }
            if(!findbool)
            {
                ItemList.append((mapiter->second->LeftItem->outLineItem)[num]);
            }
        }
        //删除list中连线，并更新json
        foreach(auto item,ItemList)
        {
            //更新json
            //获取json
            QJsonObject allObj=JsonInter::GetInstance()->allDoc;
            QJsonObject roomobj=allObj.value(QString::number(item->EndItem->roomNum)).toObject();
            QJsonArray inArray=roomobj.value("parent_items").toArray();
            //获取数据
            for(int num=0; num<inArray.count(); num++)
            {
                if(inArray[num]==beginitemnum)
                {
                    inArray.removeAt(num);
                    break;
                }
            }
            //插入json
            roomobj.insert("parent_items",inArray);
            allObj.insert(QString::number(item->EndItem->roomNum),roomobj);
            JsonInter::GetInstance()->allDoc=allObj;


            //更新map中信息
            auto nowmapiter=JsonInter::GetInstance()->roomMap.find(item->EndItem->roomNum);
            if(nowmapiter!=JsonInter::GetInstance()->roomMap.end())
            {
                nowmapiter->first->fromRoomList.removeOne(beginitemnum);
            }

            //删除view中连线
            item->EndItem->rightItem->inLineItem.removeOne(item);
            mapiter->second->LeftItem->outLineItem.removeOne(item);
            scene()->removeItem(item);
            item->deleteLater();
        }





        ItemList.clear();
        for(int num=0; num<mapiter->second->rightItem->outLineItem.size(); num++)
        {
            bool findbool=false;
            foreach(auto oneOut,outList)
            {
                if((mapiter->second->rightItem->outLineItem)[num]->EndItem->roomNum==oneOut.room)
                {
                    findbool=true;
                    break;
                }
            }
            if(!findbool)
            {
                ItemList.append((mapiter->second->rightItem->outLineItem)[num]);
            }
        }
        //删除list中连线，并更新json
        foreach(auto item,ItemList)
        {
            //更新json
            //获取json
            QJsonObject allObj=JsonInter::GetInstance()->allDoc;
            QJsonObject roomobj=allObj.value(QString::number(item->EndItem->roomNum)).toObject();
            QJsonArray inArray=roomobj.value("parent_items").toArray();
            //获取数据
            for(int num=0; num<inArray.count(); num++)
            {
                if(inArray[num]==beginitemnum)
                {
                    inArray.removeAt(num);
                    break;
                }
            }
            //插入json
            roomobj.insert("parent_items",inArray);
            allObj.insert(QString::number(item->EndItem->roomNum),roomobj);
            JsonInter::GetInstance()->allDoc=allObj;


            //更新map中信息
            auto nowmapiter=JsonInter::GetInstance()->roomMap.find(item->EndItem->roomNum);
            if(nowmapiter!=JsonInter::GetInstance()->roomMap.end())
            {
                nowmapiter->first->fromRoomList.removeOne(beginitemnum);
            }

            //删除view中连线
            item->EndItem->LeftItem->inLineItem.removeOne(item);
            mapiter->second->rightItem->outLineItem.removeOne(item);
            scene()->removeItem(item);
            item->deleteLater();
        }


        //
        //增加连线
        //
        //QList<outInfo> outList=mapiter->first->outInfo;
        QList<int> waitnewLineList;
        foreach(auto oneOut,outList)
        {
            bool findbool=false;
            for(int num=0; num<mapiter->second->upItem->outLineItem.size(); num++)
                if((mapiter->second->upItem->outLineItem)[num]->EndItem->roomNum==oneOut.room)
                {
                    findbool=true;
                    break;
                }
            if(!findbool)
            {
                for(int num=0; num<mapiter->second->downItem->outLineItem.size(); num++)
                    if((mapiter->second->downItem->outLineItem)[num]->EndItem->roomNum==oneOut.room)
                    {
                        findbool=true;
                        break;
                    }
            }
            if(!findbool)
            {
                for(int num=0; num<mapiter->second->LeftItem->outLineItem.size(); num++)
                    if((mapiter->second->LeftItem->outLineItem)[num]->EndItem->roomNum==oneOut.room)
                    {
                        findbool=true;
                        break;
                    }
            }
            if(!findbool)
            {
                for(int num=0; num<mapiter->second->rightItem->outLineItem.size(); num++)
                    if((mapiter->second->rightItem->outLineItem)[num]->EndItem->roomNum==oneOut.room)
                    {
                        findbool=true;
                        break;
                    }
            }
            if(!findbool)
            {
                //一、增加view中连线，二、更新json,三、更新map中信息
                auto endmapiter=JsonInter::GetInstance()->roomMap.find(oneOut.room);
                if(endmapiter!=JsonInter::GetInstance()->roomMap.end())
                {
                    addLine(mapiter->second, endmapiter->second, oneOut.outcmd);

                    //更新map中信息
                    endmapiter->first->fromRoomList.append(beginitemnum);
                }

                //更新json
                //获取json
                QJsonObject allObj=JsonInter::GetInstance()->allDoc;
                QJsonObject roomobj=allObj.value(QString::number(oneOut.room)).toObject();
                QJsonArray inArray=roomobj.value("parent_items").toArray();
                //获取数据
                inArray.append(beginitemnum);
                //插入json
                roomobj.insert("parent_items",inArray);
                allObj.insert(QString::number(oneOut.room),roomobj);
                JsonInter::GetInstance()->allDoc=allObj;
            }
        }
    }
}

void MapCreateView::addLine(MapCreateRoomItem *beginitem, MapCreateRoomItem *endItem, QString cmd)
{
    MapCreateLineItem* asdf=new MapCreateLineItem;
    scene()->addItem(asdf);
    if(cmd=="w" || cmd=="west" || cmd=="wd" || cmd=="westdown" || cmd=="wu" || cmd=="westup")
    {
        asdf->addMyLine(beginitem,MapCreateRoomItem::LEFT, endItem,MapCreateRoomItem::RIGHT);
    }
    else if(cmd=="north"|| cmd=="n" || cmd=="nu" || cmd=="nd" || cmd=="ne" || cmd=="nw" || cmd=="northup" || cmd=="northdown" || cmd=="northeast" || cmd=="northwest")
    {
        asdf->addMyLine(beginitem,MapCreateRoomItem::UP, endItem,MapCreateRoomItem::DOWN);
    }
    else if(cmd=="south" || cmd=="s" || cmd=="su" || cmd=="sd" || cmd=="se" || cmd=="sw" || cmd=="southup" || cmd=="southdown" || cmd=="southeast" || cmd=="southwest")
    {
        asdf->addMyLine(beginitem,MapCreateRoomItem::DOWN, endItem,MapCreateRoomItem::UP);
    }
    else if(cmd=="e" || cmd=="east" || cmd=="eu" || cmd=="ed" || cmd=="eastup" || cmd=="eastdown")
    {
        asdf->addMyLine(beginitem,MapCreateRoomItem::RIGHT, endItem,MapCreateRoomItem::LEFT);
    }
    else if(cmd=="enter" || cmd=="out"|| cmd=="up" || cmd=="down" || cmd=="u" || cmd=="d"|| cmd=="特殊方向")
    {
        int endEnterx=endItem->pos().x()+endItem->itemWidth/2;
        int endEntery=endItem->pos().y()+endItem->itemHeight/2;
        if(endEntery>beginitem->pos().y()+beginitem->itemHeight)
        {
            asdf->addMyLine(beginitem,MapCreateRoomItem::DOWN, endItem,MapCreateRoomItem::UP);
        }
        else if(endEntery<beginitem->pos().y())
        {
            asdf->addMyLine(beginitem,MapCreateRoomItem::UP, endItem,MapCreateRoomItem::DOWN);
        }
        else if(endEnterx>beginitem->pos().x())
        {
            asdf->addMyLine(beginitem,MapCreateRoomItem::RIGHT, endItem,MapCreateRoomItem::LEFT);
        }
        else
        {
            asdf->addMyLine(beginitem,MapCreateRoomItem::LEFT, endItem,MapCreateRoomItem::RIGHT);
        }
    }
}

void MapCreateView::addnewItem(int roomNum, MapCreateRoomItem *beginitem, QString cmd)
{
    auto roomiter=JsonInter::GetInstance()->roomMap.find(roomNum);
    if(roomiter!=JsonInter::GetInstance()->roomMap.end())
    {
        QPointF nene=beginitem->pos();
        if(cmd=="w" || cmd=="west" || cmd=="wd" || cmd=="westdown" || cmd=="wu" || cmd=="westup")
        {
            nene.setX(nene.x()-beginitem->itemWidth*2);
        }
        else if(cmd=="north"|| cmd=="n" || cmd=="nu" || cmd=="nd" || cmd=="ne" || cmd=="nw" || cmd=="northup" || cmd=="northdown" || cmd=="northeast" || cmd=="northwest")
        {
            nene.setY(nene.y()-beginitem->itemHeight*2);
        }
        else if(cmd=="south" || cmd=="s" || cmd=="su" || cmd=="sd" || cmd=="se" || cmd=="sw" || cmd=="southup" || cmd=="southdown" || cmd=="southeast" || cmd=="southwest")
        {
            nene.setY(nene.y()+beginitem->itemHeight*2);
        }
        else if(cmd=="e" || cmd=="east" || cmd=="eu" || cmd=="ed" || cmd=="eastup" || cmd=="eastdown")
        {
            nene.setX(nene.x()+beginitem->itemWidth*2);
        }
        else if(cmd=="enter" || cmd=="out"|| cmd=="up" || cmd=="down" || cmd=="u" || cmd=="d"|| cmd=="特殊方向")
        {
            nene.setY(nene.y()-beginitem->itemHeight*2);
        }
        MapCreateRoomItem* newItem=new MapCreateRoomItem;
        scene()->addItem(newItem);
        newItem->setPos(nene);
        newItem->roomNum=roomNum;
        roomiter->second=newItem;
    }
}

void MapCreateView::wheelEvent(QWheelEvent *event)
{
    if(QApplication::keyboardModifiers() == Qt::ShiftModifier)
    {
        QScrollBar *pScrollBar = this->verticalScrollBar();
        if(pScrollBar != NULL)
        {
            QPoint sroll = event->angleDelta();
            sroll.y() > 0 ? m_scalingOffset = -40 : m_scalingOffset = 40;
            event->accept();
            pScrollBar->setValue(pScrollBar->value() + m_scalingOffset);
        }
    }
    else if(QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        QScrollBar *pScrollBar = this->horizontalScrollBar();
        if(pScrollBar != NULL)
        {
            QPoint sroll = event->angleDelta();
            sroll.y() > 0 ? m_scalingOffset = 40 : m_scalingOffset = -40;
            event->accept();
            pScrollBar->setValue(pScrollBar->value() + m_scalingOffset);
        }
    }
    //    else
    else if(QApplication::keyboardModifiers() == Qt::NoModifier)
    {
        /*QPoint sroll = event->angleDelta();
            sroll.y() > 0 ? m_scalingOffset = 1.25 : m_scalingOffset = 1/1.25;
            event->accept();
            scale(m_scalingOffset, m_scalingOffset);*/
        if (event->orientation() == Qt::Vertical) {
            double angle = event->angleDelta().y();
            int aa=angle>0?wheelNum+1:wheelNum-1;
            angle=angle>0?120:-120;
            if(aa<=10 && aa>=-13)
            {
                wheelNum=aa;
                double factor = qPow(_zoom_factor_base, angle);
                gentle_zoom(factor);
            }
        }
    }
}

void MapCreateView::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug()<<"MapCreateView::mousePressEvent-----";
    QPointF delta = target_viewport_pos - event->pos();
    if (qAbs(delta.x()) > 5 || qAbs(delta.y()) > 5) {
        target_viewport_pos = event->pos();
        target_scene_pos = mapToScene(event->pos());
    }
    if(event->buttons() == Qt::LeftButton)
    {
        this->eventpos = event->pos();
        if(!viewportMoveTimer.isActive())
        {
            viewportMoveTimer.start();
        }
    }
    QGraphicsView::mouseMoveEvent(event);
}

void MapCreateView::mousePressEvent(QMouseEvent *event)
{
    isMousePressed=true;
    if(event->button() & Qt::LeftButton)
    {
        //qDebug()<<"FlowGraphicsView::mouseReleaseEvent LeftButton";
        QGraphicsItem* asdfasdf=scene()->itemAt(mapToScene(event->pos()),QTransform());
        if(asdfasdf!=nullptr)
        {
            //upSelectItem();
            //qDebug()<<"FlowGraphicsView::mousePressEvent-----";
            if(asdfasdf->type()==MapCreateRoomItem::Type)
            {
                //qDebug()<<"FlowGraphicsView::mousePressEvent   asdfasdf->type()==MapCreateRoomItem::Type"<<asdfasdf;
                if(clickItem!=nullptr)
                {
                    clickItem->itemSHOW_STATE=false;
                    clickItem->itemSELECTED_STATE=false;
                    clickItem->update();
                }
                clickItem=((MapCreateRoomItem*)asdfasdf);
                clickItem->itemSHOW_STATE=true;
                emit itemeclick(clickItem);
                //oneItem->update();
            }
            else if(asdfasdf->parentItem()->type()==MapCreateRoomItem::Type)
            {
                //qDebug()<<"FlowGraphicsView::mousePressEvent   asdfasdf->type()!=MapCreateRoomItem::Type";
                if(clickItem!=nullptr)
                {
                    clickItem->itemSHOW_STATE=false;
                    clickItem->itemSELECTED_STATE=false;
                    clickItem->update();
                }
                clickItem=((MapCreateRoomItem*)(asdfasdf->parentItem()));
                clickItem->itemSHOW_STATE=true;
                emit itemeclick(clickItem);
            }
        }
    }
    QGraphicsView::mousePressEvent(event);
}

void MapCreateView::mouseReleaseEvent(QMouseEvent *event)
{
    isMousePressed=false;
    //qDebug()<<"FlowGraphicsView::mouseReleaseEvent";
    if(event->button() & Qt::RightButton)
    {
        //若是鼠标右键在没有选择的控件上时，弹起其它，没有选择的控件变为选中控件 须填
        //使能菜单 须填
        rightMenuMouseScenePos = event->pos();//粘贴控件需要用到该坐标
        //判断鼠标在不在选中的控件上面它控件上面
        bool backFlag=false;
        //qDebug() << "connect(&deleteAction, &QAction::triggered, [&]()  rightMenuMouseScenePos--"<<rightMenuMouseScenePos;
        MapCreateRoomItem* backItem=mouseIsOverFlowItem(event->pos(),backFlag);
        if(backFlag==true)
        {
            if(!backItem->isSelected())//右键没在选中控件上
            {
                //重置控件状态，设置选中控件
                //qDebug() << "FlowGraphicsView::mouseReleaseEvent  右键没在选中控件上--";
                //用户右键到没选中的控件上，弹起所有的已选中控件，自动选中鼠标右键在的控件
                if(clickItem!=nullptr)
                {
                    clickItem->itemSHOW_STATE=false;
                    clickItem->itemSELECTED_STATE=false;
                    clickItem->update();
                }
            }
            else
            {
                //右键在选中控件上
                //qDebug() << "FlowGraphicsView::mouseReleaseEvent  右键选中控件上--";
            }
            clickItem=backItem;
            clickItem->itemSHOW_STATE=true;
            deleteAction.setEnabled(true);
            emit itemeclick(clickItem);
            if(heBingItem!=nullptr)
            {
                heBingBeginAction.setEnabled(false);
                heBingAction.setEnabled(true);
                quxiaoHeBingAction.setEnabled(true);
            }
            else
            {
                heBingBeginAction.setEnabled(true);
                heBingAction.setEnabled(false);
                quxiaoHeBingAction.setEnabled(false);
            }
        }
        else
        {
            //右键在空白处
            //qDebug() << "FlowGraphicsView::mouseReleaseEvent  右键在空白处--";
            deleteAction.setEnabled(false);
            heBingBeginAction.setEnabled(false);
            heBingAction.setEnabled(false);
            if(heBingItem!=nullptr)
            {
                quxiaoHeBingAction.setEnabled(true);
            }
            else
            {
                quxiaoHeBingAction.setEnabled(false);
            }
        }
        rightMenu.exec(QCursor::pos());
    }
    else
    {
        for(int num=0;num<seletitem.size();num++)
        {
            if(seletitem[num]->type()==MapCreateRoomItem::Type)
            {
                ((MapCreateRoomItem*)seletitem[num])->fluseLine();
            }
        }
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void MapCreateView::gentle_zoom(double factor)
{
    //qDebug()<<"FlowGraphicsView::gentle_zoom  true"<<"  wheelNum--"<<wheelNum;
    scale(factor, factor);
    centerOn(target_scene_pos);
    QPointF delta_viewport_pos = target_viewport_pos - QPointF(viewport()->width() / 2.0,
                                                               viewport()->height() / 2.0);
    QPointF viewport_center = mapFromScene(target_scene_pos) - delta_viewport_pos;
    centerOn(mapToScene(viewport_center.toPoint()));
}

int MapCreateView::mousePosIsLocationAtMove(QPoint mousePos)
{
    int result = 0;
    int padding_left = 80;
    int padding_right = width() - 80;
    int padding_top = 60;
    int padding_bottom = height() - 60;
    int x = mousePos.x();
    int y = mousePos.y();

    if(x<padding_left && y<padding_top)
    {
        result = 1;
    }
    else if(x>padding_left && x<padding_right && y<padding_top)
    {
        result = 2;
    }
    else if(x>padding_right && y<padding_top)
    {
        result  = 3;
    }
    else if(x<padding_left && y>padding_top && y<padding_bottom)
    {
        result = 4;
    }
    else if(x>padding_right && y>padding_top && y<padding_bottom)
    {
        result = 5;
    }
    else if(x<padding_left && y>padding_bottom)
    {
        result = 6;
    }
    else if(x>padding_left && x<padding_right && y>padding_bottom)
    {
        result = 7;
    }
    else if(x>padding_right&& y>padding_bottom)
    {
        result = 8;
    }
    return result;
}

void MapCreateView::moveScrollBar(int value)
{
    int x = 0;
    int y = 0;
    int step_x = 10;
    int step_y = 10;
    switch(value)
    {
    case 1:
    {
        x = -1 * step_x;
        y = -1 * step_y;
        break;
    }
    case 2:
    {
        y = -1 * step_y;
        break;
    }
    case 3:
    {
        x = step_x;
        y = -1 * step_y;
        break;
    }
    case 4:
    {
        x = -1 * step_x;
        y = 0;
        break;
    }
    case 5:
        x = step_x;
        y = 0;
        break;
    case 6:
    {
        x = -1 * step_x;
        y = step_y;
        break;
    }
    case 7:
        x = 0;
        y = step_y;
        break;
    case 8:
    {
        x = step_x;
        y = step_y;
        break;
    }
    default:
        break;
    }
    horizontalScrollBar()->setValue(horizontalScrollBar()->value() + x);
    verticalScrollBar()->setValue(verticalScrollBar()->value() + y);
}

bool MapCreateView::mouseIsOverFlowItem(QPoint mouseScenePos)
{
    bool result = false;
    foreach(QGraphicsItem *item , scene()->items(mapToScene(mouseScenePos)))
    {
        if(item->type() == MapCreateRoomItem::Type)
        {
            result = true;
            break;
        }
    }
    return result;
}

MapCreateRoomItem *MapCreateView::mouseIsOverFlowItem(QPoint mouseScenePos, bool &backFlag)
{
    backFlag = false;
    MapCreateRoomItem *result=nullptr;
    foreach(QGraphicsItem *item , scene()->items(mapToScene(mouseScenePos)))
    {
        //qDebug() << "FlowGraphicsView::mouseIsOverFlowItem  item--"<<item;
        if(item->type() == MapCreateRoomItem::Type)
        {
            result = (MapCreateRoomItem*)item;
            backFlag=true;
            break;
        }
    }
    return result;
}

void MapCreateView::upSelectItem()
{
    //qDebug()<<"FlowGraphicsView::upSelectItem  begin";
    foreach(auto aa, ((QGraphicsScene*)scene())->selectedItems()) //通知item弹起
    {
        if(aa->type()==MapCreateRoomItem::Type)
        {
            //弹起item
            //qDebug()<<"FlowGraphicsView::upSelectItem  aa-----"<<aa;
            ((MapCreateRoomItem*)aa)->setSelected(false);
            ((MapCreateRoomItem*)aa)->update();
        }
    }
}

void MapCreateView::initRightMenu()
{
    deleteAction.setText("删除");
    rightMenu.addAction(&deleteAction);
    deleteAction.setStatusTip(tr("Open an existing file"));
    connect(&deleteAction, &QAction::triggered, this, [this](){
        emit Itemdelete(clickItem);
    });
    deleteAction.setEnabled(false);

    rightMenu.addSeparator();

    heBingBeginAction.setText("开始合并");
    rightMenu.addAction(&heBingBeginAction);
    heBingBeginAction.setStatusTip(tr("Open an existing file"));
    connect(&heBingBeginAction, &QAction::triggered, [&](){
        if(clickItem!=nullptr)
        {
            heBingItem=clickItem;
            heBingBeginAction.setEnabled(false);
            quxiaoHeBingAction.setEnabled(true);
            heBingAction.setEnabled(true);
        }
    });
    heBingBeginAction.setEnabled(false);

    heBingAction.setText("合并到此");
    rightMenu.addAction(&heBingAction);
    heBingAction.setStatusTip(tr("Open an existing file"));
    connect(&heBingAction, &QAction::triggered, [&](){
        if(heBingItem!=nullptr && clickItem!= nullptr && clickItem!=heBingItem)
        {
            //开始合并
            emit itemeMerge(heBingItem, clickItem);
        }
    });
    heBingAction.setEnabled(false);

    quxiaoHeBingAction.setText("取消合并");
    rightMenu.addAction(&quxiaoHeBingAction);
    quxiaoHeBingAction.setStatusTip(tr("Open an existing file"));
    connect(&quxiaoHeBingAction, &QAction::triggered, [&](){
        if(heBingItem!=nullptr)
        {
            heBingItem=nullptr;
            heBingBeginAction.setEnabled(false);
            quxiaoHeBingAction.setEnabled(false);
            heBingAction.setEnabled(false);
        }
    });
    quxiaoHeBingAction.setEnabled(false);
}

void MapCreateView::deleteItem(MapCreateRoomItem *delettt)
{
    if(delettt!=nullptr)
    {
        seletitem.removeAll(delettt);
        if(heBingItem==delettt)
        {
            heBingItem=nullptr;
            heBingBeginAction.setEnabled(false);
            quxiaoHeBingAction.setEnabled(false);
            heBingAction.setEnabled(false);
        }
        if(delettt->upItem->outLineItem.size()!=0)
        {
            foreach(MapCreateLineItem* oneItem,delettt->upItem->outLineItem)
            {
                oneItem->EndItem->downItem->inLineItem.removeOne(oneItem);
                scene()->removeItem(oneItem);
                oneItem->deleteLater();
            }
            delettt->upItem->outLineItem.clear();
        }
        if(delettt->upItem->inLineItem.size()!=0)
        {
            foreach(MapCreateLineItem* oneItem,delettt->upItem->inLineItem)
            {
                oneItem->BeginItem->downItem->outLineItem.removeOne(oneItem);
                scene()->removeItem(oneItem);
                oneItem->deleteLater();
            }
            delettt->upItem->inLineItem.clear();
        }

        if(delettt->downItem->outLineItem.size()!=0)
        {
            foreach(MapCreateLineItem* oneItem,delettt->downItem->outLineItem)
            {
                oneItem->EndItem->upItem->inLineItem.removeOne(oneItem);
                scene()->removeItem(oneItem);
                oneItem->deleteLater();
            }
            delettt->downItem->outLineItem.clear();
        }
        if(delettt->downItem->inLineItem.size()!=0)
        {
            foreach(MapCreateLineItem* oneItem,delettt->downItem->inLineItem)
            {
                oneItem->BeginItem->upItem->outLineItem.removeOne(oneItem);
                scene()->removeItem(oneItem);
                oneItem->deleteLater();
            }
            delettt->downItem->inLineItem.clear();
        }

        if(delettt->LeftItem->outLineItem.size()!=0)
        {
            foreach(MapCreateLineItem* oneItem,delettt->LeftItem->outLineItem)
            {
                oneItem->EndItem->rightItem->inLineItem.removeOne(oneItem);
                scene()->removeItem(oneItem);
                oneItem->deleteLater();
            }
            delettt->LeftItem->outLineItem.clear();
        }
        if(delettt->LeftItem->inLineItem.size()!=0)
        {
            foreach(MapCreateLineItem* oneItem,delettt->LeftItem->inLineItem)
            {
                oneItem->BeginItem->rightItem->outLineItem.removeOne(oneItem);
                scene()->removeItem(oneItem);
                oneItem->deleteLater();
            }
            delettt->LeftItem->inLineItem.clear();
        }

        if(delettt->rightItem->outLineItem.size()!=0)
        {
            foreach(MapCreateLineItem* oneItem,delettt->rightItem->outLineItem)
            {
                oneItem->EndItem->LeftItem->inLineItem.removeOne(oneItem);
                scene()->removeItem(oneItem);
                oneItem->deleteLater();
            }
            delettt->rightItem->outLineItem.clear();
        }
        if(delettt->rightItem->inLineItem.size()!=0)
        {
            foreach(MapCreateLineItem* oneItem,delettt->rightItem->inLineItem)
            {
                oneItem->BeginItem->LeftItem->outLineItem.removeOne(oneItem);
                scene()->removeItem(oneItem);
                oneItem->deleteLater();
            }
            delettt->rightItem->inLineItem.clear();
        }
        delettt->deleteLater();
    }
}

void MapCreateView::hebingTwoItem()
{
    foreach(auto oneItem,heBingItem->upItem->inLineItem)//看上面进来的线，起点一样就没必要加
    {
        bool findBool=false;
        foreach(auto someItem,clickItem->upItem->inLineItem)
        {
            if(someItem->BeginItem==oneItem->BeginItem)
            {
                findBool=true;
                break;
            }
        }
        if(!findBool && oneItem->BeginItem!=clickItem)//起点没有一样的就添加
        {
            MapCreateLineItem* asdf=new MapCreateLineItem;
            scene()->addItem(asdf);
            asdf->addMyLine(oneItem->BeginItem,MapCreateRoomItem::DOWN,clickItem,MapCreateRoomItem::UP);
        }
    }
    foreach(auto oneItem,heBingItem->upItem->outLineItem)//看上面出去的线，终点一样就没必要加
    {
        bool findBool=false;
        foreach(auto someItem,clickItem->upItem->outLineItem)
        {
            if(someItem->EndItem==oneItem->EndItem)
            {
                findBool=true;
                break;
            }
        }
        if(!findBool && oneItem->EndItem!=clickItem)//起点没有一样的就添加
        {
            MapCreateLineItem* asdf=new MapCreateLineItem;
            scene()->addItem(asdf);
            asdf->addMyLine(clickItem,MapCreateRoomItem::UP,oneItem->EndItem,MapCreateRoomItem::DOWN);
        }
    }

    foreach(auto oneItem,heBingItem->downItem->inLineItem)//看下面进来的线，起点一样就没必要加
    {
        bool findBool=false;
        foreach(auto someItem,clickItem->downItem->inLineItem)
        {
            if(someItem->BeginItem==oneItem->BeginItem)
            {
                findBool=true;
                break;
            }
        }
        if(!findBool && oneItem->BeginItem!=clickItem)//起点没有一样的就添加
        {
            MapCreateLineItem* asdf=new MapCreateLineItem;
            scene()->addItem(asdf);
            asdf->addMyLine(oneItem->BeginItem,MapCreateRoomItem::UP,clickItem,MapCreateRoomItem::DOWN);
        }
    }
    foreach(auto oneItem,heBingItem->downItem->outLineItem)//看下面出去的线，终点一样就没必要加
    {
        bool findBool=false;
        foreach(auto someItem,clickItem->downItem->outLineItem)
        {
            if(someItem->EndItem==oneItem->EndItem)
            {
                findBool=true;
                break;
            }
        }
        if(!findBool && oneItem->EndItem!=clickItem)//起点没有一样的就添加
        {
            MapCreateLineItem* asdf=new MapCreateLineItem;
            scene()->addItem(asdf);
            asdf->addMyLine(clickItem,MapCreateRoomItem::DOWN,oneItem->EndItem,MapCreateRoomItem::UP);
        }
    }

    foreach(auto oneItem,heBingItem->LeftItem->inLineItem)//看左面进来的线，起点一样就没必要加
    {
        bool findBool=false;
        foreach(auto someItem,clickItem->LeftItem->inLineItem)
        {
            if(someItem->BeginItem==oneItem->BeginItem)
            {
                findBool=true;
                break;
            }
        }
        if(!findBool && oneItem->BeginItem!=clickItem)//起点没有一样的就添加
        {
            MapCreateLineItem* asdf=new MapCreateLineItem;
            scene()->addItem(asdf);
            asdf->addMyLine(oneItem->BeginItem,MapCreateRoomItem::RIGHT,clickItem,MapCreateRoomItem::LEFT);
        }
    }
    foreach(auto oneItem,heBingItem->LeftItem->outLineItem)//看左面出去的线，终点一样就没必要加
    {
        bool findBool=false;
        foreach(auto someItem,clickItem->LeftItem->outLineItem)
        {
            if(someItem->EndItem==oneItem->EndItem)
            {
                findBool=true;
                break;
            }
        }
        if(!findBool && oneItem->EndItem!=clickItem)//起点没有一样的就添加
        {
            MapCreateLineItem* asdf=new MapCreateLineItem;
            scene()->addItem(asdf);
            asdf->addMyLine(clickItem,MapCreateRoomItem::LEFT,oneItem->EndItem,MapCreateRoomItem::RIGHT);
        }
    }

    foreach(auto oneItem,heBingItem->rightItem->inLineItem)//看右面进来的线，起点一样就没必要加
    {
        bool findBool=false;
        foreach(auto someItem,clickItem->rightItem->inLineItem)
        {
            if(someItem->BeginItem==oneItem->BeginItem)
            {
                findBool=true;
                break;
            }
        }
        if(!findBool && oneItem->BeginItem!=clickItem)//起点没有一样的就添加
        {
            MapCreateLineItem* asdf=new MapCreateLineItem;
            scene()->addItem(asdf);
            asdf->addMyLine(oneItem->BeginItem,MapCreateRoomItem::LEFT,clickItem,MapCreateRoomItem::RIGHT);
        }
    }
    foreach(auto oneItem,heBingItem->rightItem->outLineItem)//看右面出去的线，终点一样就没必要加
    {
        bool findBool=false;
        foreach(auto someItem,clickItem->rightItem->outLineItem)
        {
            if(someItem->EndItem==oneItem->EndItem)
            {
                findBool=true;
                break;
            }
        }
        if(!findBool && oneItem->EndItem!=clickItem)//起点没有一样的就添加
        {
            MapCreateLineItem* asdf=new MapCreateLineItem;
            scene()->addItem(asdf);
            asdf->addMyLine(clickItem,MapCreateRoomItem::RIGHT,oneItem->EndItem,MapCreateRoomItem::LEFT);
        }
    }
    heBingItem=nullptr;
    heBingBeginAction.setEnabled(false);
    quxiaoHeBingAction.setEnabled(false);
    heBingAction.setEnabled(false);
}

void MapCreateView::viewportMoveTimerOut()
{
    viewportMoveTimer.stop();
    viewportMoveTimer.setInterval(50);
    if(isMousePressed)
    {
        int result = mousePosIsLocationAtMove(this->eventpos);
        this->mouseHoverPos = this->eventpos;
        moveScrollBar(result);
        viewportMoveTimer.start();
        //qDebug()<<"myFlowGraphicsView::mouseReleaseEvent      scene()->itemsBoundingRect() : "<<scene()->itemsBoundingRect();
        /*int x = scene()->itemsBoundingRect().x()+scene()->itemsBoundingRect().width();
            int y = scene()->itemsBoundingRect().y()+scene()->itemsBoundingRect().height();
            int w = x>this->width()?x:this->width();
            int h = y>this->height()?y:this->height();
            setSceneRect(scene()->itemsBoundingRect().x()-3000,scene()->itemsBoundingRect().y()-3000,w+6000,h+6000);*/
        //qDebug()<<" FlowGraphicsView::viewportMoveTimerOut"<<"  itemsBoundingRect()--"<<scene()->itemsBoundingRect();
        setSceneRect(scene()->itemsBoundingRect().x()-3000,scene()->itemsBoundingRect().y()-3000,scene()->itemsBoundingRect().width()+6000,scene()->itemsBoundingRect().height()+6000);
    }
    else
    {
        viewportMoveTimer.stop();
    }
}
