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
        if(!nowMap.empty())
        {
            quyuList[backint].itemPointMap.insert(std::unordered_map<int, std::unordered_map<int, int>>::value_type(roommapite.key(), nowMap));
        }
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
                    alltime=endroomite->second;
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
    /*///放着区域出入口简化房间 int对应JsonInter中的数值
    QList<int> easyRoomList;
    ///所有点的权值 初始化必须在调用lujingListquyu()之后 前两个int是easyRoomList的坐标  第三个是权值或者路径最大值
    std::unordered_map<int, std::unordered_map<int, int>> itemPointMap;*/
    foreach(auto onequyu, quyuList)
    {
        foreach(auto oneroom, onequyu.IOroom)
        {
            easyRoomList.append(oneroom);
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
        qDebug()<<"MapToMapManage::findLujing 11111";
        auto endite=JsonInter::GetInstance()->roomMap.find(end);
        if (endite!=JsonInter::GetInstance()->roomMap.end())
        {
            qDebug()<<"MapToMapManage::findLujing 222222";
            if(beginite->first->FqZH==endite->first->FqZH
                    && beginite->first->sqZH==endite->first->sqZH
                    && beginite->first->sthqZH==endite->first->sthqZH)
            {
                qDebug()<<"MapToMapManage::findLujing 在同一区域";
                //在同一区域
                for(int num=0;num<quyuList.size();num++)
                {
                    qDebug()<<"MapToMapManage::findLujing fn--"<<quyuList[num].fn;
                    if(quyuList[num].fn==endite->first->FqZH
                            && quyuList[num].sn==endite->first->sqZH
                            && quyuList[num].srdn==endite->first->sthqZH)
                    {
                        qDebug()<<"MapToMapManage::findLujing 在同一区域2222222222";
                        backlujing=shortest_path(begin, end, quyuList[num].itemPointMap);
                        break;
                    }
                }
            }
            else
            {
                qDebug()<<"MapToMapManage::findLujing 不在同一区域";
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
                qDebug()<<"MapToMapManage::findLujing beginquyu--"<<beginquyu<<"    endquyu---"<<endquyu;
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
                        qDebug()<<"begin--"<<begin<<"  chukouroon--"<<chukouroon<<"  roomList--"<<newlujing.roomList;
                        newlujing.time=addTimeInMap(newlujing.roomList, quyuList[beginquyu].itemPointMap);
                        begintoquyu.append(newlujing);
                        newmp.insert(std::unordered_map<int, int>::value_type(chukouroon,newlujing.time));
                    }
                    vertices.insert(std::unordered_map<int, std::unordered_map<int, int>>::value_type(begin,newmp));
                    qDebug()<<"MapToMapManage::findLujing beginquyu  vertices1--"<<vertices.size()<<"  begintoquyu--"<<begintoquyu.size();

                    foreach(int beginroon,quyuList[beginquyu].IOroom)//找起点区域各个出口到终点区域各个出口的路径和时间
                    {
                        newmp.clear();
                        foreach(int endroon,quyuList[endquyu].IOroom)
                        {
                            lujing newlujing;
                            newlujing.qidian=beginroon;
                            newlujing.zhongdian=endroon;
                            newlujing.roomList=shortest_path(beginroon, endroon, itemPointMap);
                            qDebug()<<"beginroon--"<<beginroon<<"  endroon--"<<endroon<<"  roomList--"<<newlujing.roomList;
                            newlujing.time=addTimeInMap(newlujing.roomList, itemPointMap);
                            quyutoquyu.append(newlujing);
                            newmp.insert(std::unordered_map<int, int>::value_type(endroon,newlujing.time));
                        }
                        vertices.insert(std::unordered_map<int, std::unordered_map<int, int>>::value_type(beginroon,newmp));
                    }
                    qDebug()<<"MapToMapManage::findLujing beginquyu  vertices2--"<<vertices.size()<<"  quyutoquyu--"<<quyutoquyu.size();

                    foreach(int endroon,quyuList[endquyu].IOroom)//找终点区域各个出口到终点的路径和时间
                    {
                        newmp.clear();
                        lujing newlujing;
                        newlujing.qidian=endroon;
                        newlujing.zhongdian=end;
                        newlujing.roomList=shortest_path(endroon, end, quyuList[endquyu].itemPointMap);
                        qDebug()<<"endroon--"<<endroon<<"  end--"<<end<<"  roomList--"<<newlujing.roomList;
                        newlujing.time=addTimeInMap(newlujing.roomList, quyuList[endquyu].itemPointMap);
                        quyutoend.append(newlujing);
                        newmp.insert(std::unordered_map<int, int>::value_type(end,newlujing.time));
                        vertices.insert(std::unordered_map<int, std::unordered_map<int, int>>::value_type(endroon,newmp));
                    }
                    qDebug()<<"MapToMapManage::findLujing beginquyu  vertices3--"<<vertices.size()<<"  quyutoend--"<<quyutoend.size();

                    QVector<int> backvecbec=shortest_path(begin, end, vertices);
                    qDebug()<<"MapToMapManage::findLujing beginquyu  backvecbec--"<<backvecbec;
                    int allllltime=addTimeInMap(backvecbec, vertices);
                    if(backvecbec.size()>=4)
                    {
                        for(int num=0;num<begintoquyu.size();num++)
                        {
                            if(begintoquyu[num].qidian==backvecbec[0] && begintoquyu[num].zhongdian==backvecbec[1])
                            {
                                for(int beginnum=0; beginnum<begintoquyu[num].roomList.size(); beginnum++)
                                {
                                    backlujing.append(begintoquyu[num].roomList[beginnum]);
                                }
                                break;
                            }
                        }
                        for(int num=0;num<quyutoquyu.size();num++)
                        {
                            if(quyutoquyu[num].qidian==backvecbec[1] && quyutoquyu[num].zhongdian==backvecbec[2])
                            {
                                for(int midnum=0; midnum<quyutoquyu[num].roomList.size(); midnum++)
                                {
                                    backlujing.append(quyutoquyu[num].roomList[midnum]);
                                }
                                break;
                            }
                        }
                        for(int num=0;num<quyutoend.size();num++)
                        {
                            if(quyutoend[num].qidian==backvecbec[2] && quyutoend[num].zhongdian==backvecbec[3])
                            {
                                for(int endnum=0; endnum<quyutoend[num].roomList.size(); endnum++)
                                {
                                    backlujing.append(quyutoend[num].roomList[endnum]);
                                }
                                break;
                            }
                        }
                    }
                }
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
