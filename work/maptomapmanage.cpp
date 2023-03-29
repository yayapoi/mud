#include "maptomapmanage.h"
#include "flowjson/jsoninter.h"

MapToMapManage* MapToMapManage::m_pipe_rw = nullptr;
MapToMapManage::GC MapToMapManage::gc;

MapToMapManage::MapToMapManage(QObject *parent)
    : QObject{parent}
{

}

void MapToMapManage::initallquyu()
{
    auto roommapite=JsonInter::GetInstance()->roomMap.begin();
    while (roommapite!=JsonInter::GetInstance()->roomMap.end())
    {
        int backint=quyuInquyuMap(roommapite->first->FqZH,roommapite->first->sqZH,roommapite->first->sthqZH);
        if(-1==backint)
        {
            //本区域不存在
            quyu newquyu;
            newquyu.fn=roommapite->first->FqZH;
            newquyu.sn=roommapite->first->sqZH;
            newquyu.srdn=roommapite->first->sthqZH;
            quyuList.append(newquyu);
            backint=quyuList.size()-1;
        }
        quyuList[backint].allroom.append(roommapite.key());
        bool findio=false;
        //只看输出房间，若不同区域，加入iolist,同时初始化本房间map
        std::unordered_map<int, int> nowMap;
        foreach(auto oneOut,roommapite->first->outInfo)
        {
            nowMap.insert(std::unordered_map<int, int>::value_type(oneOut.room,oneOut.time));
            if(findio==false)
            {
                auto endRoomite=JsonInter::GetInstance()->roomMap.find(oneOut.room);
                if(endRoomite!=JsonInter::GetInstance()->roomMap.end())
                {
                    if(endRoomite->first->FqZH!=roommapite->first->FqZH
                            || endRoomite->first->sqZH!=roommapite->first->sqZH
                            || endRoomite->first->sthqZH!=roommapite->first->sthqZH)
                    {
                        findio=true;
                        quyuList[backint].IOroom.append(roommapite.key());
                    }
                }
            }
        }
        if(nowMap.empty())
        {
            nowMap.insert(std::unordered_map<int, int>::value_type(roommapite.key(),0));
        }
        quyuList[backint].itemPointMap.insert(std::unordered_map<int, std::unordered_map<int, int>>::value_type(roommapite.key(), nowMap));
        if(findio==false)//如果输出没找到是不是ioroom,就看输入是不是ioroom
        {
            foreach(auto oneIn,roommapite->first->fromRoomList)
            {
                auto endRoomite=JsonInter::GetInstance()->roomMap.find(oneIn);
                if(endRoomite!=JsonInter::GetInstance()->roomMap.end())
                {
                    if(endRoomite->first->FqZH!=roommapite->first->FqZH
                            || endRoomite->first->sqZH!=roommapite->first->sqZH
                            || endRoomite->first->sthqZH!=roommapite->first->sthqZH)
                    {
                        quyuList[backint].IOroom.append(roommapite.key());
                        break;
                    }
                }
            }
        }
        roommapite++;
    }
    lujingListquyu();
    //printf();
    initEasy();
}

void MapToMapManage::lujingListquyu()
{
    for(int num=0; num<quyuList.size(); num++)
    {
        QList<int> lujinglistlist=quyuList[num].IOroom;
        for(int roombegin=0; roombegin<lujinglistlist.size(); roombegin++)
        {
            for(int roonend=0; roonend<lujinglistlist.size(); roonend++)
            {
                if(roombegin!=roonend)
                {
                    lujing newlujing;
                    newlujing.qidian=lujinglistlist[roombegin];
                    newlujing.zhongdian=lujinglistlist[roonend];
                    newlujing.roomList=shortest_path(lujinglistlist[roombegin], lujinglistlist[roonend], quyuList[num].itemPointMap);
                    newlujing.time=addTimeInMap(newlujing.roomList, quyuList[num].itemPointMap);
                    //qDebug()<<"qidian--"<<lujinglistlist[roombegin]<<"  end--"<<lujinglistlist[roonend]<<"  roomList--"<<newlujing.roomList<<"  time--"<<newlujing.time;
                    if(!newlujing.roomList.isEmpty())
                    {
                        quyuList[num].lujingList.append(newlujing);
                    }
                }
            }
        }
    }
}

int MapToMapManage::quyuInquyuMap(QString &fN, QString &sn, QString &srdn)
{
    int findBool=-1;
    for(int num=0;num<quyuList.size();num++)
    {
        if(quyuList[num].fn==fN && quyuList[num].sn==sn && quyuList[num].srdn==srdn)
        {
            findBool=num;
            break;
        }
    }
    return findBool;
}

int MapToMapManage::addTime(QVector<int> &vecvec)
{
    int alltime=0;
    for(int roonnum=0;roonnum<vecvec.size()-1;roonnum++)
    {
        auto beginroomite=JsonInter::GetInstance()->roomMap.find(vecvec[roonnum]);
        if(beginroomite!=JsonInter::GetInstance()->roomMap.end())
        {
            foreach(auto ontout,beginroomite->first->outInfo)
            {
                if(ontout.room==vecvec[roonnum+1])
                {
                    alltime=alltime+ontout.time;
                }
            }
        }
        else
        {
            alltime=alltime+99999;
        }
    }
    return alltime;
}

int MapToMapManage::addTimeInMap(QVector<int> &vecvec, std::unordered_map<int, std::unordered_map<int, int> > &vertices)
{
    int alltime=0;
    for(int roonnum=0;roonnum<vecvec.size()-1;roonnum++)
    {
        auto beginroomite=vertices.find(vecvec[roonnum]);
        if(beginroomite!=vertices.end())
        {
            auto endroomite=beginroomite->second.find(vecvec[roonnum+1]);
            if(endroomite!=beginroomite->second.end())
            {
                alltime=endroomite->second+alltime;
            }
        }
        else
        {
            alltime=alltime+99999;
        }
    }
    return alltime;
}

void MapToMapManage::initEasy()
{
    foreach(auto onequyu, quyuList)
    {
        foreach(auto oneroom, onequyu.IOroom)
        {
            std::unordered_map<int, int> smap;
            foreach(auto onelujing, onequyu.lujingList)
            {
                if(onelujing.qidian==oneroom)
                    smap.insert(std::unordered_map<int, int>::value_type(onelujing.zhongdian, onelujing.time));
            }
            //查看输出房间，将去往不是本区域的房间记录进map
            auto roommapite=JsonInter::GetInstance()->roomMap.find(oneroom);
            if (roommapite!=JsonInter::GetInstance()->roomMap.end())
            {
                foreach(auto oneOut,roommapite->first->outInfo)
                {
                    auto endRoomite=JsonInter::GetInstance()->roomMap.find(oneOut.room);
                    if(endRoomite!=JsonInter::GetInstance()->roomMap.end())
                    {
                        if(endRoomite->first->FqZH!=roommapite->first->FqZH
                                || endRoomite->first->sqZH!=roommapite->first->sqZH
                                || endRoomite->first->sthqZH!=roommapite->first->sthqZH)
                        {
                            smap.insert(std::unordered_map<int, int>::value_type(oneOut.room, oneOut.time));
                        }
                    }
                }
            }
            if(smap.empty())//不能为空,加空路径进去
            {
                smap.insert(std::unordered_map<int, int>::value_type(oneroom, 0));
            }
            itemPointMap.insert(std::unordered_map<int, std::unordered_map<int, int>>::value_type(oneroom,smap));
        }
    }
}

bool MapToMapManage::findLujing(int begin, int end, QVector<int> &backlujing)
{
    bool findBool=false;
    auto beginite=JsonInter::GetInstance()->roomMap.find(begin);
    if (beginite!=JsonInter::GetInstance()->roomMap.end())
    {
        //qDebug()<<"MapToMapManage::findLujing 11111";
        auto endite=JsonInter::GetInstance()->roomMap.find(end);
        if (endite!=JsonInter::GetInstance()->roomMap.end())
        {
            //qDebug()<<"MapToMapManage::findLujing 222222";
            int timetttt=-1;
            QVector<int> tongyiquyu;
            if(beginite->first->FqZH==endite->first->FqZH
                    && beginite->first->sqZH==endite->first->sqZH
                    && beginite->first->sthqZH==endite->first->sthqZH)
            {
                //qDebug()<<"MapToMapManage::findLujing 在同一区域";
                //在同一区域
                for(int num=0;num<quyuList.size();num++)
                {
                    //qDebug()<<"MapToMapManage::findLujing fn--"<<quyuList[num].fn;
                    if(quyuList[num].fn==endite->first->FqZH
                            && quyuList[num].sn==endite->first->sqZH
                            && quyuList[num].srdn==endite->first->sthqZH)
                    {
                        //qDebug()<<"MapToMapManage::findLujing 在同一区域2222222222";
                        tongyiquyu=shortest_path(begin, end, quyuList[num].itemPointMap);
                        timetttt=addTimeInMap(tongyiquyu,quyuList[num].itemPointMap);
                        break;
                    }
                }
            }
            //qDebug()<<"MapToMapManage::findLujing 不在同一区域";
            //不在同一区域
            //找起点到起点区域各个出口的路径和时间
            //找起点区域各个出口到终点区域各个出口的路径和时间
            //找终点区域各个出口到终点的路径和时间
            int beginquyu=-1;
            int endquyu=-1;
            for(int num=0;num<quyuList.size();num++)
            {
                if(quyuList[num].fn==beginite->first->FqZH
                        && quyuList[num].sn==beginite->first->sqZH
                        && quyuList[num].srdn==beginite->first->sthqZH)
                {
                    beginquyu=num;
                }
                if(quyuList[num].fn==endite->first->FqZH
                        && quyuList[num].sn==endite->first->sqZH
                        && quyuList[num].srdn==endite->first->sthqZH)
                {
                    endquyu=num;
                }
                if(beginquyu!=-1 && endquyu!=-1)
                {
                    break;
                }
            }
            //qDebug()<<"MapToMapManage::findLujing beginquyu--"<<beginquyu<<"    endquyu---"<<endquyu;
            if(beginquyu!=-1 && endquyu!=-1)
            {
                QList<lujing> begintoquyu;
                QList<lujing> quyutoquyu;
                QList<lujing> quyutoend;
                std::unordered_map<int, std::unordered_map<int, int>> vertices;
                std::unordered_map<int, int> newmp;
                foreach(int chukouroon,quyuList[beginquyu].IOroom)//找起点到起点区域各个出口的路径和时间
                {
                    lujing newlujing;
                    newlujing.qidian=begin;
                    newlujing.zhongdian=chukouroon;
                    newlujing.roomList=shortest_path(begin, chukouroon, quyuList[beginquyu].itemPointMap);
                    newlujing.time=addTimeInMap(newlujing.roomList, quyuList[beginquyu].itemPointMap);
                    //qDebug()<<"begin--"<<begin<<"  chukouroon--"<<chukouroon<<"  roomList--"<<newlujing.roomList<<"  time--"<<newlujing.time;
                    if(!newlujing.roomList.isEmpty())
                    {
                        begintoquyu.append(newlujing);
                        newmp.insert(std::unordered_map<int, int>::value_type(chukouroon,newlujing.time));
                    }
                }
                vertices.insert(std::unordered_map<int, std::unordered_map<int, int>>::value_type(begin,newmp));
                //qDebug()<<"MapToMapManage::findLujing beginquyu  vertices1--"<<vertices.size()<<"  begintoquyu--"<<begintoquyu.size();

                //printfitemPointMap(vertices);
                foreach(int beginroon,quyuList[beginquyu].IOroom)//找起点区域各个出口到终点区域各个出口的路径和时间
                {
                    //先找刚才是不是已经添加过了
                    auto aginite=vertices.find(beginroon);
                    if(aginite!=vertices.end())//已经添加过了
                    {
                        newmp=aginite->second;
                        vertices.erase(beginroon);
                    }
                    else
                        newmp.clear();
                    foreach(int endroon,quyuList[endquyu].IOroom)
                    {
                        lujing newlujing;
                        newlujing.qidian=beginroon;
                        newlujing.zhongdian=endroon;
                        newlujing.roomList=shortest_path(beginroon, endroon, itemPointMap);
                        newlujing.time=addTimeInMap(newlujing.roomList, itemPointMap);
                        //qDebug()<<"beginroon--"<<beginroon<<"  endroon--"<<endroon<<"  roomList--"<<newlujing.roomList<<"  time--"<<newlujing.time;
                        if(!newlujing.roomList.isEmpty())
                        {
                            quyutoquyu.append(newlujing);
                            newmp.insert(std::unordered_map<int, int>::value_type(endroon,newlujing.time));
                            //qDebug()<<"size--"<<newmp.size();
                        }
                    }
                    vertices.insert(std::unordered_map<int, std::unordered_map<int, int>>::value_type(beginroon,newmp));
                }
                //qDebug()<<"MapToMapManage::findLujing beginquyu  vertices2--"<<vertices.size()<<"  quyutoquyu--"<<quyutoquyu.size();

                //printfitemPointMap(vertices);
                foreach(int endroon,quyuList[endquyu].IOroom)//找终点区域各个出口到终点的路径和时间
                {
                    //先找刚才是不是已经添加过了
                    auto aginite=vertices.find(endroon);
                    if(aginite!=vertices.end())//已经添加过了
                    {
                        newmp=aginite->second;
                        vertices.erase(endroon);
                    }
                    else
                        newmp.clear();
                    lujing newlujing;
                    newlujing.qidian=endroon;
                    newlujing.zhongdian=end;
                    newlujing.roomList=shortest_path(endroon, end, quyuList[endquyu].itemPointMap);
                    newlujing.time=addTimeInMap(newlujing.roomList, quyuList[endquyu].itemPointMap);
                    //qDebug()<<"endroon--"<<endroon<<"  end--"<<end<<"  roomList--"<<newlujing.roomList<<"  time--"<<newlujing.time;
                    if(!newlujing.roomList.isEmpty())
                    {
                        quyutoend.append(newlujing);
                        newmp.insert(std::unordered_map<int, int>::value_type(end,newlujing.time));
                        vertices.insert(std::unordered_map<int, std::unordered_map<int, int>>::value_type(endroon,newmp));
                    }
                }
                //qDebug()<<"MapToMapManage::findLujing beginquyu  vertices3--"<<vertices.size()<<"  quyutoend--"<<quyutoend.size();

                //注意，最后一个点一定要存在与第一个int中,否则查不出路径
                auto endite=vertices.find(end);
                if(endite==vertices.end())
                {
                    newmp.clear();
                    lujing newlujing;
                    newlujing.qidian=end;
                    newlujing.zhongdian=end;
                    newlujing.roomList=shortest_path(end, end, quyuList[endquyu].itemPointMap);
                    newlujing.time=addTimeInMap(newlujing.roomList, quyuList[endquyu].itemPointMap);
                    //qDebug()<<"end--"<<end<<"  end--"<<end<<"  roomList--"<<newlujing.roomList<<"  time--"<<newlujing.time;
                    newmp.insert(std::unordered_map<int, int>::value_type(end,newlujing.time));
                    vertices.insert(std::unordered_map<int, std::unordered_map<int, int>>::value_type(end,newmp));
                }

                //printfitemPointMap(vertices);
                QVector<int> backvecbec=shortest_path(begin, end, vertices);
                //qDebug()<<"MapToMapManage::findLujing beginquyu  backvecbec--"<<backvecbec;
                int allllltime=-1;
                allllltime=addTimeInMap(backvecbec, vertices);
                if(backvecbec.size()>=2)
                {
                    for(int begin=0;begin<backvecbec.size()-1;begin++)
                    {
                        bool findbool=false;
                        for(int num=0;num<begintoquyu.size();num++)
                        {
                            if(begintoquyu[num].qidian==backvecbec[begin] && begintoquyu[num].zhongdian==backvecbec[begin+1])
                            {
                                findbool=true;
                                for(int beginnum=0; beginnum<begintoquyu[num].roomList.size(); beginnum++)
                                {
                                    if(backlujing.back()!=begintoquyu[num].roomList[beginnum])
                                    {
                                        backlujing.append(begintoquyu[num].roomList[beginnum]);
                                    }
                                }
                                break;
                            }
                        }
                        //qDebug()<<"MapToMapManage::findLujing beginquyu  backlujing--"<<backlujing;
                        if(findbool==false)
                        {
                            for(int num=0;num<quyutoend.size();num++)
                            {
                                if(quyutoend[num].qidian==backvecbec[begin] && quyutoend[num].zhongdian==backvecbec[begin+1])
                                {
                                    findbool=true;
                                    for(int endnum=0; endnum<quyutoend[num].roomList.size(); endnum++)
                                    {
                                        if(backlujing.back()!=begintoquyu[num].roomList[endnum])
                                        {
                                            backlujing.append(quyutoend[num].roomList[endnum]);
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                        //qDebug()<<"MapToMapManage::findLujing beginquyu  backlujing11--"<<backlujing;
                        if(findbool==false)
                        {
                            for(int num=0;num<quyutoquyu.size();num++)
                            {
                                if(quyutoquyu[num].qidian==backvecbec[begin] && quyutoquyu[num].zhongdian==backvecbec[begin+1])
                                {
                                    //qDebug()<<"backvecbec1--"<<backvecbec[begin]<<"  backvecbec2="<<backvecbec[begin+1];
                                    findbool=true;
                                    for(int midnum=0; midnum<quyutoquyu[num].roomList.size()-1; midnum++)
                                    {
                                        //qDebug()<<"begin--"<<quyutoquyu[num].roomList[midnum]<<"  ebd="<<quyutoquyu[num].roomList[1+midnum];
                                        //看房间出口有没有第二个数字，有则表示相邻房间，没有就是同一区域的出口到出口
                                        auto iteerer=JsonInter::GetInstance()->roomMap.find(quyutoquyu[num].roomList[midnum]);
                                        if(iteerer!=JsonInter::GetInstance()->roomMap.end())
                                        {
                                            bool oneoutinfofind=false;
                                            foreach(auto oneoutinfo,iteerer->first->outInfo)
                                            {
                                                if(oneoutinfo.room==quyutoquyu[num].roomList[midnum+1])
                                                {
                                                    oneoutinfofind=true;
                                                    break;
                                                }
                                            }
                                            if(oneoutinfofind)//如果不是相邻的两个房间，则是同一区域的出口到出口
                                            {
                                                //qDebug()<<"this  room="<<quyutoquyu[num].roomList[midnum];
                                                if(backlujing.back()!=quyutoquyu[num].roomList[midnum])
                                                {
                                                    backlujing.append(quyutoquyu[num].roomList[midnum]);
                                                }
                                                backlujing.append(quyutoquyu[num].roomList[midnum+1]);
                                            }
                                            else
                                            {
                                                for(int quyunum=0;quyunum<quyuList.size();quyunum++)
                                                {
                                                    bool brak=false;
                                                    foreach(auto onelujing,quyuList[quyunum].lujingList)
                                                    {
                                                        if(onelujing.qidian==quyutoquyu[num].roomList[midnum] &&
                                                                onelujing.zhongdian==quyutoquyu[num].roomList[midnum+1])
                                                        {
                                                            foreach(auto oneroom,onelujing.roomList)
                                                            {
                                                                //qDebug()<<"lujing="<<quyutoquyu[num].roomList[midnum];
                                                                if(backlujing.back()!=oneroom)
                                                                    backlujing.append(oneroom);
                                                            }
                                                            brak=true;
                                                            break;
                                                        }
                                                    }
                                                    if(brak)
                                                    {
                                                        break;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                        //qDebug()<<"MapToMapManage::findLujing beginquyu  backlujing33--"<<backlujing;
                    }
                }
                if(timetttt!=-1 && allllltime!=-1)
                {
                    if(timetttt<allllltime)
                    {
                        backlujing=tongyiquyu;
                    }
                    else
                    {
                        tongyiquyu=backlujing;
                    }
                }
                //qDebug()<<"MapToMapManage::findLujing beginquyu  backlujingeeeeeend--"<<backlujing;
            }
        }
    }
    return findBool;
}

void MapToMapManage::printf()
{
    foreach(auto ontquyu,quyuList)
    {
        qDebug()<<"fn---"<<ontquyu.fn;
        foreach(auto ontlujing,ontquyu.lujingList)
        {
            qDebug()<<"qidian---"<<ontlujing.qidian;
            qDebug()<<"zhongdian---"<<ontlujing.zhongdian;
            qDebug()<<"roomList---"<<ontlujing.roomList;
        }
    }
}

void MapToMapManage::printfitemPointMap(std::unordered_map<int, std::unordered_map<int, int>>& sadf)
{
    auto oneite=sadf.begin();
    while(oneite!=sadf.end())
    {
        qDebug()<<"MapToMapManage::printfitemPointMap        begin---"<<oneite->first;
        auto seite=oneite->second.begin();
        while(seite!=oneite->second.end())
        {
            qDebug()<<"MapToMapManage::printfitemPointMap  seite---"<<seite->first<<"   time---"<<seite->second;
            seite++;
        }
        oneite++;
    }
}

QVector<int> MapToMapManage::shortest_path(int start, int finish, std::unordered_map<int, std::unordered_map<int, int> > &vertices)
{
    std::unordered_map<int, int> distances;
    std::unordered_map<int, int> previous;
    std::vector<int> nodes;
    QVector<int> path;
    //qDebug()<<"shortest_path";

    auto comparator = [&] (int left, int right) { return distances[left] > distances[right]; };

    for (auto& vertex : vertices)
    {
        if (vertex.first == start)
        {
            distances[vertex.first] = 0;
        }
        else
        {
            distances[vertex.first] = std::numeric_limits<int>::max();
        }

        nodes.push_back(vertex.first);
        push_heap(begin(nodes), end(nodes), comparator);
    }

    while (!nodes.empty())
    {
        pop_heap(begin(nodes), end(nodes), comparator);
        int smallest = nodes.back();
        //qDebug()<<"MapToMapManage::shortest_path  smallest---"<<smallest;
        nodes.pop_back();

        if (smallest == finish)
        {
            while (previous.find(smallest) != end(previous))
            {
                path.push_front(smallest);
                smallest = previous[smallest];
            }
            path.push_front(start);
            break;
        }

        if (distances[smallest] == std::numeric_limits<int>::max())
        {
            break;
        }

        for (auto& neighbor : vertices[smallest])
        {
            int alt = distances[smallest] + neighbor.second;
            if (alt < distances[neighbor.first])
            {
                distances[neighbor.first] = alt;
                previous[neighbor.first] = smallest;
                make_heap(begin(nodes), end(nodes), comparator);
            }
        }
    }

    return path;
}
