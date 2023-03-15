#include "jsoninter.h"
#include "qdebug.h"
#include <QJsonArray>
#include <QFile>
#include <QJsonParseError>
#include "mapCreateWindow/mapcreatelineitem.h"

JsonInter* JsonInter::m_pipe_rw = nullptr;
JsonInter::GC JsonInter::gc;

JsonInter::JsonInter(QObject *parent)
    : QObject{parent}
{
    setnewRoomInJson(1);
}

JsonInter::~JsonInter()
{
    //
}

void JsonInter::setnewRoomInJson(int roomNum1, QString fZH, QString fEN, QString SZH, QString SEN, QString SrdZH, QString SrdEn)
{
    QJsonObject oneroomJson;//初始化空控件

    QJsonObject outListJson;
    oneroomJson.insert("outList",outListJson);
    QJsonObject npcListJson;
    oneroomJson.insert("npcList",npcListJson);
    oneroomJson.insert("FqZH",fZH);
    oneroomJson.insert("FqEN",fEN);
    oneroomJson.insert("sqZH",SZH);
    oneroomJson.insert("sqEN",SEN);
    oneroomJson.insert("sthqZH",SrdZH);
    oneroomJson.insert("sthqEN",SrdEn);
    oneroomJson.insert("roomZH","");
    oneroomJson.insert("roomEN","");
    oneroomJson.insert("roomColor","");
    oneroomJson.insert("out","");
    oneroomJson.insert("outnow","");
    oneroomJson.insert("roomDes","");
    oneroomJson.insert("chongfuNum",0);

    //控件坐标
    QJsonArray roomCoordinate;
    roomCoordinate.append(0);
    roomCoordinate.append(0);
    oneroomJson.insert("coordinate_data",roomCoordinate);

    //出去房间
    QJsonArray toroom;
    oneroomJson.insert("child_items",toroom);

    //出去房间
    QJsonArray fromroom;
    oneroomJson.insert("parent_items",fromroom);

    allDoc.insert(QString::number(roomNum1),oneroomJson);
    roomNumList.append(roomNum1);

    roomInfo* tempInfo=new roomInfo;
    tempInfo->roomNum=roomNum1;
    tempInfo->FqZH=fZH;
    tempInfo->FqEN=fEN;
    tempInfo->sqZH=SZH;
    tempInfo->sqEN=SEN;
    tempInfo->sthqZH=SrdZH;
    tempInfo->sthqEN=SrdEn;
    roomMap.insert(roomNum1,QPair<roomInfo*,MapCreateRoomItem*>{tempInfo,nullptr});
}

void JsonInter::saveRoomInFile(QString fillname)
{
    QFile testfile{fillname};
    if(testfile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        /*auto oneroom=roomMap.begin();
        QJsonObject allJson;
        while(oneroom!=roomMap.end())
        {
            QJsonObject npcListJson;
            QJsonObject outListJson;
            QJsonObject oneroomJson;

            roomInfo* roomPtr=oneroom.value().first;
            //npc
            QList<npcInfo> aaa=roomPtr->npcInfo;
            for(int num=0;num<aaa.size();num++)
            {
                QJsonObject npcJson;
                npcJson.insert("nameZH",aaa[num].nameZH);
                npcJson.insert("nameEN",aaa[num].nameEN);
                npcJson.insert("title",aaa[num].title);
                npcListJson.insert(QString::number(num),npcJson);
            }

            //room
            QList<outInfo> bbb=roomPtr->outInfo;
            for(int num=0;num<bbb.size();num++)
            {
                QJsonObject roomJson;
                roomJson.insert("outcmd",bbb[num].outcmd);
                roomJson.insert("outCmdNow",bbb[num].outCmdNow);
                roomJson.insert("time",bbb[num].time);
                roomJson.insert("room",bbb[num].room);
                outListJson.insert(QString::number(num),roomJson);
            }

            oneroomJson.insert("outList",outListJson);
            oneroomJson.insert("npcList",npcListJson);
            oneroomJson.insert("FqZH",roomPtr->FqZH);
            oneroomJson.insert("FqEN",roomPtr->FqEN);
            oneroomJson.insert("sqZH",roomPtr->sqZH);
            oneroomJson.insert("sqEN",roomPtr->sqEN);
            oneroomJson.insert("sthqZH",roomPtr->sthqZH);
            oneroomJson.insert("sthqEN",roomPtr->sthqEN);
            oneroomJson.insert("roomZH",roomPtr->roomZH);
            oneroomJson.insert("roomEN",roomPtr->roomEN);
            oneroomJson.insert("roomColor",roomPtr->roomColor);
            oneroomJson.insert("out",roomPtr->out);
            oneroomJson.insert("outnow",roomPtr->outnow);
            oneroomJson.insert("roomDes",roomPtr->roomDes);
            oneroomJson.insert("chongfuNum",roomPtr->chongfuNum);

            //控件坐标
            QJsonArray roomCoordinate;
            roomCoordinate.append(roomPtr->roomPoint.x());
            roomCoordinate.append(roomPtr->roomPoint.y());
            oneroomJson.insert("coordinate_data",roomCoordinate);

            //出去房间
            QJsonArray toroom;
            foreach(auto oneINT,roomPtr->toRoomList)
                toroom.append(oneINT);
            oneroomJson.insert("child_items",toroom);

            //出去房间
            QJsonArray fromroom;
            foreach(auto oneINT,roomPtr->fromRoomList)
                fromroom.append(oneINT);
            oneroomJson.insert("parent_items",fromroom);

            allJson.insert(QString::number(oneroom.key()),oneroomJson);
            oneroom++;
        }*/
        testfile.write(QJsonDocument(allDoc).toJson());
        testfile.flush();
        testfile.close();
    }
}

bool JsonInter::getRoomInFile(QString fillname)
{
    clearMap();
    clearList();
    bool backBool=false;
    QFile filename{fillname};
    if(filename.open(QIODevice::ReadOnly))
    {
        QByteArray allData = filename.readAll();
        filename.close(); //关闭文件
        QJsonParseError json_error;  //报告 JSON 处理过程中出现的错误
        QJsonDocument allDocd = QJsonDocument::fromJson(allData, &json_error); //关联json文件
        if(json_error.error==QJsonParseError::NoError)
        {
            allDoc=allDocd.object();
            auto objJsonIter=allDoc.begin();
            while(objJsonIter!=allDoc.end())
            {
                int roomNum1=objJsonIter.key().toInt();
                //qDebug()<<"JsonInter::getRoomInFile(QString fillname)   roomNum1--"<<roomNum1;
                QJsonObject oneRoomObj=objJsonIter.value().toObject();
                roomInfo* oneRoonInfo=new roomInfo;

                QJsonArray coordinate_data=oneRoomObj.value("coordinate_data").toArray();
                oneRoonInfo->roomPoint.setX(coordinate_data[0].toInt());
                oneRoonInfo->roomPoint.setY(coordinate_data[1].toInt());

                QJsonArray child_items=oneRoomObj.value("child_items").toArray();
                foreach(auto oneitem,child_items)
                {
                    oneRoonInfo->toRoomList.append(oneitem.toInt());
                }

                QJsonArray parent_items=oneRoomObj.value("parent_items").toArray();
                foreach(auto oneitem,parent_items)
                {
                    oneRoonInfo->fromRoomList.append(oneitem.toInt());
                }

                oneRoonInfo->FqZH=oneRoomObj.value("FqZH").toString();
                oneRoonInfo->FqEN=oneRoomObj.value("FqEN").toString();
                oneRoonInfo->sqZH=oneRoomObj.value("sqZH").toString();
                oneRoonInfo->sqEN=oneRoomObj.value("sqEN").toString();
                oneRoonInfo->sthqZH=oneRoomObj.value("sthqZH").toString();
                oneRoonInfo->sthqEN=oneRoomObj.value("sthqEN").toString();
                oneRoonInfo->roomZH=oneRoomObj.value("roomZH").toString();
                oneRoonInfo->roomEN=oneRoomObj.value("roomEN").toString();
                oneRoonInfo->roomColor=oneRoomObj.value("roomColor").toString();
                oneRoonInfo->out=oneRoomObj.value("out").toString();
                oneRoonInfo->outnow=oneRoomObj.value("outnow").toString();
                oneRoonInfo->roomDes=oneRoomObj.value("roomDes").toString();
                oneRoonInfo->chongfuNum=oneRoomObj.value("chongfuNum").toInt();
                oneRoonInfo->roomNum=roomNum1;


                QJsonObject npcObj=oneRoomObj.value("npcList").toObject();
                for(int num=0; num<npcObj.keys().size(); num++)
                {
                    QJsonObject oneNpcObj=npcObj.value(QString::number(num)).toObject();
                    NpcInfo oneNpc;
                    oneNpc.nameZH=oneNpcObj.value("nameZH").toString();
                    oneNpc.nameEN=oneNpcObj.value("nameEN").toString();
                    oneNpc.title=oneNpcObj.value("title").toString();
                    oneRoonInfo->npcInfo.append(oneNpc);
                }

                QJsonObject outObj=oneRoomObj.value("outList").toObject();
                for(int num=0; num<outObj.keys().size(); num++)
                {
                    QJsonObject oneOutObj=outObj.value(QString::number(num)).toObject();
                    OutInfo oneOut;
                    oneOut.outcmd=oneOutObj.value("outcmd").toString();
                    oneOut.outCmdNow=oneOutObj.value("outCmdNow").toString();
                    oneOut.time=oneOutObj.value("time").toInt();
                    oneOut.room=oneOutObj.value("room").toInt();
                    oneRoonInfo->outInfo.append(oneOut);
                }

                roomMap.insert(roomNum1,QPair<roomInfo*,MapCreateRoomItem*>{oneRoonInfo,nullptr});
                roomNumList.append(roomNum1);
                objJsonIter++;
            }

            backBool=true;
        }
    }
    return backBool;
}

void JsonInter::clearMap()
{
    foreach(auto oneRoom,roomMap)
    {
        delete oneRoom.first;
    }
    roomMap.clear();
}

void JsonInter::clearList()
{
    roomNumList.clear();
}

void JsonInter::deleteRoom(int roomNum)
{
    //更新json,更新map,删除房间数字列表
    auto deleteroomIter=roomMap.find(roomNum);
    if(deleteroomIter!=roomMap.end())
    {
        //更新json
        deletejsonList(deleteroomIter->second->upItem, roomNum);
        //qDebug()<<"MapForm::GoSuccess()  111--"<<JsonInter::GetInstance()->allDoc;
        deletejsonList(deleteroomIter->second->downItem, roomNum);
        //qDebug()<<"MapForm::GoSuccess()  222--"<<JsonInter::GetInstance()->allDoc;
        deletejsonList(deleteroomIter->second->LeftItem, roomNum);
        //qDebug()<<"MapForm::GoSuccess()  333--"<<JsonInter::GetInstance()->allDoc;
        deletejsonList(deleteroomIter->second->rightItem, roomNum);
        //qDebug()<<"MapForm::GoSuccess()  444--"<<JsonInter::GetInstance()->allDoc;
        allDoc.remove(QString::number(roomNum));
        //qDebug()<<"MapForm::GoSuccess()  555--"<<JsonInter::GetInstance()->allDoc;
        //删除房间数字列表
        roomNumList.removeOne(roomNum);
        //更新map
        deletemapList(deleteroomIter->second->upItem, roomNum);
        deletemapList(deleteroomIter->second->downItem, roomNum);
        deletemapList(deleteroomIter->second->LeftItem, roomNum);
        deletemapList(deleteroomIter->second->rightItem, roomNum);
        auto roommapOter=roomMap.find(roomNum);
        if(roommapOter!=roomMap.end())
        {
            delete roommapOter->first;
            roomMap.remove(roomNum);
        }
    }
}

void JsonInter::deletejsonList(MapCreatRecItem *item, int roosnum)
{
    //qDebug()<<"roosnum--"<<roosnum;
    if(item->outLineItem.size()!=0)
    {
        foreach(MapCreateLineItem* oneItem,item->outLineItem)
        {
            //qDebug()<<"EndItem--"<<oneItem->EndItem->roomNum;
            QJsonObject deleteParentObj=allDoc.value(QString::number(oneItem->EndItem->roomNum)).toObject();
            QJsonArray deleteparentAraay=deleteParentObj.value("parent_items").toArray();
            for(int num=0; num<deleteparentAraay.size(); num++)
            {
                if(deleteparentAraay[num].toInt()==roosnum)
                {
                    deleteparentAraay.removeAt(num);
                    break;
                }
            }
            deleteParentObj.insert("parent_items",deleteparentAraay);
            allDoc.insert(QString::number(oneItem->EndItem->roomNum),deleteParentObj);
        }
    }
    if(item->inLineItem.size()!=0)
    {
        foreach(MapCreateLineItem* oneItem,item->inLineItem)
        {
            //qDebug()<<"BeginItem--"<<oneItem->BeginItem->roomNum;
            QJsonObject deletechildObj=allDoc.value(QString::number(oneItem->BeginItem->roomNum)).toObject();
            QJsonArray deletechildAraay=deletechildObj.value("child_items").toArray();
            int num=0;
            for(; num<deletechildAraay.size(); num++)
            {
                if(deletechildAraay[num].toInt()==roosnum)
                {
                    deletechildAraay.removeAt(num);
                    break;
                }
            }
            deletechildObj.insert("child_items",deletechildAraay);

            QList<QJsonObject> jsonList;
            QJsonObject deleteoutListObj=deletechildObj.value("outList").toObject();
            for(int num1=0; num1<deleteoutListObj.size(); num1++)
            {
                QJsonObject aaa=deleteoutListObj.value(QString::number(num1)).toObject();
                jsonList.append(aaa);
            }
            QJsonObject backObj;
            if(jsonList.size()>num)
            {
                jsonList.removeAt(num);
            }
            for(int num2=0; num2<jsonList.size(); num2++)
            {
                backObj.insert(QString::number(num2), jsonList[num2]);
            }
            deletechildObj.insert("outList",backObj);
            allDoc.insert(QString::number(oneItem->BeginItem->roomNum),deletechildObj);
        }
    }
}

void JsonInter::deletemapList(MapCreatRecItem *item, int roosnum)
{
    if(item->outLineItem.size()!=0)
    {
        foreach(MapCreateLineItem* oneItem,item->outLineItem)
        {
            //qDebug()<<"EndItem--"<<oneItem->EndItem->roomNum;
            auto roommapOter=roomMap.find(oneItem->EndItem->roomNum);
            if(roommapOter!=roomMap.end())
            {
                for(int num=0; num<roommapOter->first->fromRoomList.size(); num++)
                {
                    if(roommapOter->first->fromRoomList[num]==roosnum)
                    {
                        roommapOter->first->fromRoomList.removeAt(num);
                        break;
                    }
                }
            }
        }
    }
    if(item->inLineItem.size()!=0)
    {
        foreach(MapCreateLineItem* oneItem,item->inLineItem)
        {
            //qDebug()<<"BeginItem--"<<oneItem->BeginItem->roomNum;
            auto roommapOter=roomMap.find(oneItem->BeginItem->roomNum);
            if(roommapOter!=roomMap.end())
            {
                int num=0;
                for(; num<roommapOter->first->toRoomList.size(); num++)
                {
                    if(roommapOter->first->toRoomList[num]==roosnum)
                    {
                        roommapOter->first->toRoomList.removeAt(num);
                        break;
                    }
                }
                if(roommapOter->first->outInfo.size()>num)
                {
                    if(roommapOter->first->outInfo[num].room==roosnum)
                    {
                        roommapOter->first->outInfo.removeAt(num);
                    }
                }
            }
        }
    }
}

void JsonInter::itemMarge(MapCreateRoomItem *beginitem, MapCreateRoomItem *endItem)
{
    int begimNum=beginitem->roomNum;
    int endNum=endItem->roomNum;
    auto beginItemIter=roomMap.find(begimNum);
    auto endItemIter=roomMap.find(endNum);
    if(beginItemIter!=roomMap.end() && endItemIter!=roomMap.end())
    {
        //遍历begin的parent 和end的parent
        foreach(auto partroomNum,beginItemIter->first->fromRoomList)
        {
            bool findBool=false;
            foreach(auto partroomNum2,endItemIter->first->fromRoomList)
            {
                if(partroomNum==partroomNum2)
                {
                    findBool=true;
                    //有相同的parent，俩房间最大时间给enditem的(json map)
                    auto parentItemIter=roomMap.find(partroomNum2);
                    if(parentItemIter!=roomMap.end())
                    {
                        int num=0;
                        int begimNummm=0,endNummm=0;
                        for(; num<parentItemIter->first->outInfo.size(); num++)
                        {
                            if(parentItemIter->first->outInfo[num].room==begimNum)
                            {
                                begimNummm=num;
                            }
                            if(parentItemIter->first->outInfo[num].room==endNum)
                            {
                                endNummm=num;
                            }
                        }
                        if(parentItemIter->first->outInfo[begimNummm].time>parentItemIter->first->outInfo[endNummm].time)
                        {
                            //更新room,
                            parentItemIter->first->outInfo[endNummm].time=parentItemIter->first->outInfo[begimNummm].time;
                            //更新json
                            QJsonObject parentRoom=allDoc.value(QString::number(partroomNum2)).toObject();
                            QJsonObject parentoutList=parentRoom.value("outList").toObject();
                            QJsonObject parentoneout=parentoutList.value(QString::number(endNummm)).toObject();
                            parentoneout.insert("time",parentItemIter->first->outInfo[begimNummm].time);
                            parentoutList.insert(QString::number(endNummm),parentoneout);
                            parentRoom.insert("outList",parentoutList);
                            allDoc.insert(QString::number(partroomNum2),parentRoom);
                        }
                    }
                }
            }
            if(!findBool)
            {
                //end没有begin的parent,则end的parent加begin的parent (json map),
                //map
                endItemIter->first->fromRoomList.append(partroomNum);
                //json
                QJsonObject endRoom=allDoc.value(QString::number(endItem->roomNum)).toObject();
                QJsonArray endparentList=endRoom.value("parent_items").toArray();
                endparentList.append(partroomNum);
                endRoom.insert("parent_items",endparentList);
                allDoc.insert(QString::number(endItem->roomNum),endRoom);
                //再找parent的outlist,找begin，copy,目标改为enditem,child从这里生成(map),json生成插入out和child
                auto parentItemIter=roomMap.find(partroomNum);
                if(parentItemIter!=roomMap.end())
                {
                    for(int infoNUm=0; infoNUm<parentItemIter->first->outInfo.size(); infoNUm++)
                    {
                        if(parentItemIter->first->outInfo[infoNUm].room==begimNum)
                        {
                            //map
                            OutInfo asdfas=parentItemIter->first->outInfo[infoNUm];
                            asdfas.room=endNum;
                            parentItemIter->first->outInfo.append(asdfas);
                            parentItemIter->first->toRoomList.append(endNum);

                            //json
                            QJsonObject parentRoom=allDoc.value(QString::number(partroomNum)).toObject();
                            //outlist
                            QJsonObject parentoutList=parentRoom.value("outList").toObject();
                            QJsonObject parentoneout=parentoutList.value(QString::number(infoNUm)).toObject();
                            if(parentoneout.value("room").toInt()==begimNum)
                            {
                                parentoneout.insert("room",endNum);
                                parentoutList.insert(QString::number(parentoutList.count()),parentoneout);
                                parentRoom.insert("outList",parentoutList);
                                //child_items
                                QJsonArray childoutList=parentRoom.value("child_items").toArray();
                                childoutList.append(endNum);
                                parentRoom.insert("child_items",childoutList);
                                allDoc.insert(QString::number(partroomNum),parentRoom);
                            }
                        }
                    }
                }
            }
        }

        //遍历begin的roomInfo 和end的roomInfo
        for(int numbegimnn=0; numbegimnn<beginItemIter->first->outInfo.size(); numbegimnn++)
        {
            bool findBool=false;
            for(int numendmnn=0; numendmnn<endItemIter->first->outInfo.size(); numendmnn++)
            {
                if(beginItemIter->first->outInfo[numbegimnn].room==endItemIter->first->outInfo[numendmnn].room)
                {
                    findBool=true;
                    //有相同的roominfo，俩房间最大时间给enditem的(json map)
                    if(beginItemIter->first->outInfo[numbegimnn].time>endItemIter->first->outInfo[numendmnn].time)
                    {
                        //更新room,
                        endItemIter->first->outInfo[numendmnn].time=beginItemIter->first->outInfo[numbegimnn].time;
                        //更新json
                        QJsonObject endRoom=allDoc.value(QString::number(begimNum)).toObject();
                        QJsonObject endoutList=endRoom.value("outList").toObject();
                        QJsonObject endoneout=endoutList.value(QString::number(numendmnn)).toObject();
                        if(endoneout.value("room").toInt()==endItemIter->first->outInfo[numendmnn].room)
                        {
                            endoneout.insert("time",beginItemIter->first->outInfo[numbegimnn].time);
                            endoutList.insert(QString::number(numendmnn),endoneout);
                            endRoom.insert("outList",endoutList);
                            allDoc.insert(QString::number(begimNum),endRoom);
                        }
                    }
                }
            }
            if(!findBool)
            {
                //end没有begin的info,则找输出房间的parent加入end，(json map)
                auto childIter=roomMap.find(beginItemIter->first->outInfo[numbegimnn].room);
                if(childIter!=roomMap.end())
                {
                    //map
                    childIter->first->fromRoomList.append(endNum);
                    //json
                    QJsonObject childRoom=allDoc.value(QString::number(childIter->second->roomNum)).toObject();
                    QJsonArray endparentList=childRoom.value("parent_items").toArray();
                    endparentList.append(endNum);
                    childRoom.insert("parent_items",endparentList);
                    allDoc.insert(QString::number(childIter->second->roomNum),childRoom);

                    //end copy begin的info,child插入输出房间(map),,json生成插入out和child
                    //map
                    endItemIter->first->outInfo.append(beginItemIter->first->outInfo[numbegimnn]);
                    endItemIter->first->toRoomList.append(beginItemIter->first->outInfo[numbegimnn].room);
                    //json
                    QJsonObject endRoom=allDoc.value(QString::number(endNum)).toObject();
                    //outlist
                    QJsonObject endoutList=endRoom.value("outList").toObject();
                    QJsonObject newoneout;
                    newoneout.insert("outcmd",beginItemIter->first->outInfo[numbegimnn].outcmd);
                    newoneout.insert("outCmdNow",beginItemIter->first->outInfo[numbegimnn].outCmdNow);
                    newoneout.insert("time",beginItemIter->first->outInfo[numbegimnn].time);
                    newoneout.insert("room",beginItemIter->first->outInfo[numbegimnn].room);
                    endoutList.insert(QString::number(endoutList.count()),newoneout);
                    endRoom.insert("outList",endoutList);
                    allDoc.insert(QString::number(endNum),endRoom);
                    //child_items
                    QJsonArray childoutList=endRoom.value("child_items").toArray();
                    childoutList.append(beginItemIter->first->outInfo[numbegimnn].room);
                    endRoom.insert("child_items",childoutList);
                    allDoc.insert(QString::number(endNum),endRoom);
                }
            }
        }
    }
}
