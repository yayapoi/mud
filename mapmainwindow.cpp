#include "mapmainwindow.h"
#include "ui_mapmainwindow.h"
#include "qdebug.h"
#include "qevent.h"
#include "qjsonarray.h"
#include "mapCreateWindow/mapcreateroomitem.h"
#include "mapCreateWindow/mapcreateview.h"
#include "mapCreateWindow/mapcreatelineitem.h"
#include "showWidget/outform.h"
#include "showWidget/goform.h"
#include "flowjson/jsoninter.h"
#include "QFileDialog"
#include <QMessageBox>
#include <QAction>
#include <QShortcut>
#include "work/worksys.h"
#include <QRandomGenerator>
#include <QTime>
#include <ZHToEN/zhtopy.h>

#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <windows.h>
#else
#include <dlfcn.h>
#endif

struct roominin{
    int roomNum=-1;
};

MapMainWindow::MapMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MapMainWindow)
{
    ui->setupUi(this);

    QShortcut *shortCut = new QShortcut(Qt::CTRL + Qt::Key_S, this );
    connect(shortCut, SIGNAL(activated()), this , SLOT(on_saveRoomBT_clicked()));

    QAction* m_ActionAddTo = new QAction(tr("增加出口"), this);
    connect(m_ActionAddTo,&QAction::triggered,this,[this](){
        GoForm* goFor2=new GoForm;
        goFor2->initWidget("west", "", "", "",false);
        connect(goFor2,&GoForm::deleteGo,this,[this](GoForm* removeItem){
            this->toroomLayout->removeWidget(removeItem);
            removeItem->deleteLater();
        });
        connect(goFor2,&GoForm::GoFormGo,this,[this](GoForm* goItem){
            QString outCB, cmd, time, room;
            bool longolngtime;
            goItem->getWidget(outCB, cmd, time, room, longolngtime);
            if(!cmd.isEmpty())
            {
                //发送命令，等待成功
                this->waitOut.outcmd=outCB;
                this->waitOut.outCmdNow=cmd;
                this->waitOut.time=time.toInt();
                this->waitOut.room=room.toInt();
                this->waitOut.room=room.toInt();
                this->waitOut.longtime=longolngtime;
                waitGo=true;
                waitgoForm=goItem;
                jishu=true;
                WorkSys::GetInstance()->releasepareCmd("#path("+getroomID()+":"+cmd+")", true);
            }
        });
        this->toroomLayout->addWidget(goFor2);
    });
    MyMenu.addAction(m_ActionAddTo);

    fromroomLayout=new QVBoxLayout();
    ui->outRoomWidget->setLayout(fromroomLayout);

    toroomLayout=new QVBoxLayout();
    ui->inRoomWidget->setLayout(toroomLayout);

    connect(ui->graphicsView,&MapCreateView::itemeclick,this,[this](MapCreateRoomItem* itemClick){
        //点击控件,刷新界面
        //qDebug()<<"ui->graphicsView,&MapCreateView::itemeclick--";
        auto mapiter=JsonInter::GetInstance()->roomMap.begin();
        while(mapiter!=JsonInter::GetInstance()->roomMap.end())
        {
            if(mapiter.value().second==itemClick)
            {
                //qDebug()<<"ui->graphicsView,&MapCreateView::itemeclick--   mapiter.key()--"<<mapiter.key();
                nowClickNum=mapiter.key();
                ui->mapWidget->nowClickNum=mapiter.key();
                ui->mapWidget->setWidger(mapiter->first);
                setWidget(nowClickNum);
                calculateTo();
                ui->mapWidget->uselastname(fZH,fEn,sZH,sEn,srdZH,srdEh);
                break;
            }
            mapiter++;
        }
    });

    connect(ui->graphicsView,&MapCreateView::Itemdelete,this,[this](MapCreateRoomItem* itemdelete){
        JsonInter::GetInstance()->deleteRoom(itemdelete->roomNum);
        ui->graphicsView->deleteItem(itemdelete);
        ui->graphicsView->setsomeClike();
    });

    connect(ui->graphicsView,&MapCreateView::itemeMerge,this,[this](MapCreateRoomItem* beginItem, MapCreateRoomItem* endItem){
        JsonInter::GetInstance()->itemMarge(beginItem, endItem);
        //qDebug()<<"MapForm::GoSuccess()  111allDoc--"<<JsonInter::GetInstance()->allDoc;
        ui->graphicsView->hebingTwoItem();
        //qDebug()<<"MapForm::GoSuccess()  222allDoc--"<<JsonInter::GetInstance()->allDoc;
        JsonInter::GetInstance()->deleteRoom(beginItem->roomNum);
        ui->graphicsView->deleteItem(beginItem);
        //qDebug()<<"MapForm::GoSuccess()  333allDoc--"<<JsonInter::GetInstance()->allDoc;
    });

    JsonInter::GetInstance();

    ui->graphicsView->initRoom();

    /*starttimer=new QTimer;
    connect(starttimer,&QTimer::timeout,this,[this](){
        starttimer->stop();
        WorkSys::GetInstance()->Walk();
    });


    connect(WorkSys::GetInstance(),&WorkSys::cmdroom,this,[this](QString room, QString cmd){
        QString backstr=outjianhua(cmd);
        //qDebug()<<QTime::currentTime().toString("mm:ss zzz:")<<"backstr--"<<backstr;
        if(backstr!="特殊方向")//是方向延时返回成功
        {
            int starttime=QRandomGenerator::global()->bounded(160,200);
//qDebug()<<QTime::currentTime().toString("mm:ss zzz:")<<"back time--"<<starttime;
            QTimer* backworktimer=new QTimer;
            backtimelist.append(backworktimer);
            connect(backworktimer,&QTimer::timeout,this,[this](){
                QTimer *p = qobject_cast<QTimer *>(sender());
                int starttime=QRandomGenerator::global()->bounded(0, 2);
                p->stop();
                if(starttime!=0)
                {
                    WorkSys::GetInstance()->moveStatus(false);
                }
                else{
                    WorkSys::GetInstance()->moveStatus(true);
                }
            });

            int checkbuy=QRandomGenerator::global()->bounded(0, 2);
            if(checkbuy!=0)
            {
                WorkSys::GetInstance()->busyStatus(true);
                int busyttime=QRandomGenerator::global()->bounded(50,60);
//qDebug()<<QTime::currentTime().toString("mm:ss zzz:")<<"busy  time--"<<busyttime;
                QTimer* busyworktimer=new QTimer;
                busytimelist.append(busyworktimer);
                connect(busyworktimer,&QTimer::timeout,this,[this](){
                    QTimer *p = qobject_cast<QTimer *>(sender());
                    p->stop();
                    WorkSys::GetInstance()->busyStatus(false);
                });
                busyworktimer->start(busyttime);
            }

            backworktimer->start(starttime);
        }
        else
        {
            if(cmd.indexOf("#workStop")!=-1)
            {
                WorkSys::GetInstance()->stopWalk();
                int starttime=QRandomGenerator::global()->bounded(100, 200);
//qDebug()<<QTime::currentTime().toString("mm:ss zzz:")<<"start starttime--"<<starttime;
                this->starttimer->start(starttime);
            }
        }
    });*/
}

MapMainWindow::~MapMainWindow()
{
    delete ui;
}

void MapMainWindow::setWidget(int roomNum)
{
    nowClickNum=roomNum;
    clearFromRoom();
    clearToRoom();
    initToRoom();
    initFromRoom();
}

void MapMainWindow::clearFromRoom()
{
    QLayoutItem* child;
    while ((child = fromroomLayout->itemAt(0)) != nullptr) {
        fromroomLayout->removeItem(child);
        delete child->widget();
        delete child;
        child = nullptr;
    }
}

void MapMainWindow::clearToRoom()
{
    QLayoutItem* child;
    while ((child = toroomLayout->itemAt(0)) != nullptr) {
        toroomLayout->removeItem(child);
        delete child->widget();
        delete child;
        child = nullptr;
    }
}

void MapMainWindow::initToRoom()
{
    auto mapiter=JsonInter::GetInstance()->roomMap.find(nowClickNum);
    if(mapiter!=JsonInter::GetInstance()->roomMap.end())
    {
        QList<OutInfo> infoList=mapiter.value().first->outInfo;
        for(int num=0;num<infoList.size();num++)
        {
            GoForm* goFor2=new GoForm;
            goFor2->initWidget(infoList[num].outcmd, infoList[num].outCmdNow,
                               QString::number(infoList[num].time), QString::number(infoList[num].room), infoList[num].longtime);
            connect(goFor2,&GoForm::deleteGo,this,[this](GoForm* removeItem){
                this->toroomLayout->removeWidget(removeItem);
                removeItem->deleteLater();
            });
            connect(goFor2,&GoForm::GoFormGo,this,[this](GoForm* goItem){
                QString outCB, cmd, time, room;
                bool longolngtime;
                goItem->getWidget(outCB, cmd, time, room, longolngtime);
                if(!cmd.isEmpty())
                {
                    //发送命令，等待成功
                    this->waitOut.outcmd=outCB;
                    this->waitOut.outCmdNow=cmd;
                    this->waitOut.time=time.toInt();
                    this->waitOut.room=room.toInt();
                    this->waitOut.longtime=longolngtime;
                    waitGo=true;
                    waitgoForm=goItem;
                    jishu=true;
                    WorkSys::GetInstance()->releasepareCmd("#path("+getroomID()+":"+cmd+")", true);
                }
            });
            toroomLayout->addWidget(goFor2);
        }
    }
}

void MapMainWindow::initFromRoom()
{
    auto mapiter=JsonInter::GetInstance()->roomMap.find(nowClickNum);
    if(mapiter!=JsonInter::GetInstance()->roomMap.end())
    {
        QList<int> fromRoomList=mapiter.value().first->fromRoomList;
        for(int num=0;num<fromRoomList.size();num++)
        {
            auto roomiter=JsonInter::GetInstance()->roomMap.find(fromRoomList[num]);
            if(roomiter!=JsonInter::GetInstance()->roomMap.end())
            {
                OutForm* outFor2=new OutForm;
                bool findBool=false;
                int num=0;
                for(;num<roomiter->first->outInfo.size(); num++)
                {
                    if(roomiter->first->outInfo[num].room==nowClickNum)
                    {
                        findBool=true;
                        break;
                    }
                }
                if(findBool)
                {
                    outFor2->initWidget(QString::number(roomiter->second->roomNum), roomiter->first->roomZH,
                                        roomiter->first->outInfo[num].outcmd, roomiter->first->outInfo[num].outCmdNow);
                    fromroomLayout->addWidget(outFor2);
                }
                else
                {
                    outFor2->deleteLater();
                }
            }
        }
    }
}

void MapMainWindow::upRoomZhEn(int roomNum)
{
    auto mapiter=JsonInter::GetInstance()->roomMap.find(roomNum);
    if(mapiter!=JsonInter::GetInstance()->roomMap.end())
    {
        fZH=mapiter->first->FqZH;
        fEn=mapiter->first->FqEN;
        sZH=mapiter->first->sqZH;
        sEn=mapiter->first->sqEN;
        srdZH=mapiter->first->sthqZH;
        srdEh=mapiter->first->sthqEN;
    }
}

void MapMainWindow::updateFrom(roomInfo *roomIter)
{
    roomIter->fromRoomList.clear();
    for(int num=0; num<fromroomLayout->count(); num++)
    {
        QString comeRoom, roomName, outLe, cmdLe;
        ((OutForm*)(fromroomLayout->itemAt(num)->widget()))->getWidget(comeRoom, roomName, outLe, cmdLe);
        roomIter->fromRoomList.append(comeRoom.toInt());
    }
}

void MapMainWindow::updateTo(roomInfo *roomIter)
{
    roomIter->toRoomList.clear();
    roomIter->outInfo.clear();
    for(int num=0; num<toroomLayout->count(); num++)
    {
        QString outCB, cmd, time, room;
        bool longlongtime;
        ((GoForm*)(toroomLayout->itemAt(num)->widget()))->getWidget(outCB, cmd, time, room, longlongtime);
        if(time=="" || room=="" || cmd=="")
        {
            //有问题
        }
        else
        {
            OutInfo outinfo;
            outinfo.outcmd=outCB;
            outinfo.outCmdNow=cmd;
            outinfo.time=time.toInt();
            outinfo.room=room.toInt();
            outinfo.longtime=longlongtime;
            roomIter->toRoomList.append(room.toInt());
            roomIter->outInfo.append(outinfo);
        }
    }
}

bool MapMainWindow::checkTo()
{
    bool findName=false;
    for(int num=0; num<toroomLayout->count(); num++)
    {
        QString outCB, cmd, time, room;
        bool longlongtime;
        ((GoForm*)(toroomLayout->itemAt(num)->widget()))->getWidget(outCB, cmd, time, room, longlongtime);
        if(room=="")
        {
            //有问题
        }
        else
        {
            for(int num1=0; num1<toroomLayout->count(); num1++)
            {
                if(num1!=num)
                {
                    QString outCB1, cmd1, time1, room1;
                    bool longlongtime;
                    ((GoForm*)(toroomLayout->itemAt(num1)->widget()))->getWidget(outCB1, cmd1, time1, room1, longlongtime);
                    if(room1=="")
                    {
                        //有问题
                    }
                    else
                    {
                        if(room1==room)
                        {
                            findName=true;
                            break;
                        }
                    }
                }
            }
        }
        if(findName)
            break;
    }
    return findName;
}

void MapMainWindow::GoSuccess()
{
    if(waitGo)
    {
        waitGo=false;
        //qDebug()<<"MapMainWindow::GoSuccess()  waitOut.room--"<<waitOut.room;
        if(waitOut.room==-1 || waitOut.room==0)//没有房间数字
        {
            int num=0;//房间数字
            if(JsonInter::GetInstance()->roomNumList.isEmpty())
            {
                num=1;
                JsonInter::GetInstance()->setnewRoomInJson(num, fZH, fEn, sZH, sEn, srdZH, srdEh);
            }
            else
            {
                qSort(JsonInter::GetInstance()->roomNumList.begin(), JsonInter::GetInstance()->roomNumList.end());
                //qDebug()<<"MapMainWindow::GoSuccess()  roomNum--"<<JsonInter::GetInstance()->roomNum;
                bool findNUm=false;
                for(; num<JsonInter::GetInstance()->roomNumList.size(); num++)
                {
                    if(num+1!=JsonInter::GetInstance()->roomNumList[num])
                    {
                        num++;
                        //qDebug()<<"MapMainWindow::GoSuccess()  num++"<<num;
                        findNUm=true;
                        break;
                    }
                }
                if(!findNUm)
                {
                    num=JsonInter::GetInstance()->roomNumList.size()+1;
                    //qDebug()<<"MapMainWindow::GoSuccess()  ednum--"<<num;
                }
                //qDebug()<<"MapMainWindow::GoSuccess()  ednum--"<<num;
                JsonInter::GetInstance()->setnewRoomInJson(num, fZH, fEn, sZH, sEn, srdZH, srdEh);
            }
            waitOut.room=num;
            waitgoForm->setRoomWidget(QString::number(num));
            auto mapiter=JsonInter::GetInstance()->roomMap.find(nowClickNum);
            ui->graphicsView->addnewItem(num, mapiter->second, waitOut.outcmd);
        }
        //假如已经有时间了，统计时间
        int nowTime=begintime.msecsTo(QTime::currentTime());
        if(waitOut.longtime)
        {
            if(waitOut.time<nowTime)
            {
                waitOut.time=nowTime;
            }
        }
        else {
            if(errorTime && nowTime>50)
            {
                nowTime=50;
            }
            if(waitOut.time>nowTime)
            {
                waitOut.time=nowTime;
            }
            else if(waitOut.time<=0)
            {
                waitOut.time=nowTime;
            }
        }
        waitgoForm->setRoomTime(QString::number(waitOut.time));
        //保存json,保存map,即本map增加出口，json增加出口，
        on_saveRoomBT_clicked();
        ui->graphicsView->setsomeClike(waitOut.room);
        ui->graphicsView->centeeron();
    }
}

void MapMainWindow::calculateTo()
{
    QMap<QString,roominin*> listlist;
    //分析此房间描述都有啥出口
    QString outstr=ui->mapWidget->getRoomout();
    if(!outstr.isEmpty())
    {
        QStringList outList=outstr.split(';');
        foreach(auto ontout,outList)
        {
            listlist.insert(outjianhua(ontout),new roominin);
        }
    }
    //分析此房间实际都有啥出口
    QString nowoutstr=ui->mapWidget->getRoomnowout();
    if(!nowoutstr.isEmpty())
    {
        QStringList outList=nowoutstr.split(';');
        foreach(auto ontout,outList)
        {
            listlist.insert(outjianhua(ontout),new roominin);
        }
    }
    //分析此房间实际有几个进来的口，将上步统计出出口填入房间名
    for(int num=0; num<fromroomLayout->count(); num++)
    {
        QString comeRoom,roomName,outLe,cmdLe;
        ((OutForm*)(fromroomLayout->itemAt(num)->widget()))->getWidget(comeRoom,roomName,outLe,cmdLe);
        //qDebug()<<"aa"<<outLe;
        auto listIter=listlist.begin();
        while(listIter!=listlist.end())
        {
            if(listIter.key()==outChange(outLe))
            {
                listIter.value()->roomNum=comeRoom.toInt();
                break;
            }
            listIter++;
        }
    }
    /*auto listIter=listlist.begin();
    while(listIter!=listlist.end())
    {
//qDebug()<<listIter.key()<<"   "<<listIter.value()->roomNum;
        listIter++;
    }*/
    //分析layout现在已经有啥出口 出房间是啥
    for(int num=0; num<toroomLayout->count(); num++)
    {
        QString outCB,cmd,time,room;
        bool longlongtime;
        ((GoForm*)(toroomLayout->itemAt(num)->widget()))->getWidget(outCB,cmd,time,room,longlongtime);
        //qDebug()<<"aa"<<outLe;
        auto listIter=listlist.begin();
        while(listIter!=listlist.end())
        {
            if(listIter.key()==outCB)
            {
                listlist.remove(outCB);
                break;
            }
            listIter++;
        }
    }
    //剩余没有的出口自动创建，并填入房间
    auto listIter=listlist.begin();
    while(listIter!=listlist.end())
    {
        //qDebug()<<"MapMainWindow::calculateTo()---"<<listIter.key();
        GoForm* goFor2=new GoForm;
        if(listIter.value()->roomNum!=-1)
        {
            goFor2->initWidget(listIter.key(), "", "", QString::number(listIter.value()->roomNum),false);
        }
        else
        {
            goFor2->initWidget(listIter.key(), "", "", "",false);
        }
        connect(goFor2,&GoForm::deleteGo,this,[this](GoForm* removeItem){
            this->toroomLayout->removeWidget(removeItem);
            removeItem->deleteLater();
        });
        connect(goFor2,&GoForm::GoFormGo,this,[this](GoForm* goItem){
            QString outCB, cmd, time, room;
            bool longolngtime;
            goItem->getWidget(outCB, cmd, time, room, longolngtime);
            if(!cmd.isEmpty())
            {
                //发送命令，等待成功
                this->waitOut.outcmd=outCB;
                this->waitOut.outCmdNow=cmd;
                this->waitOut.time=time.toInt();
                this->waitOut.room=room.toInt();
                this->waitOut.longtime=longolngtime;
                waitGo=true;
                waitgoForm=goItem;
                jishu=true;
                WorkSys::GetInstance()->releasepareCmd("#path("+getroomID()+":"+cmd+")", true);
            }
        });
        this->toroomLayout->addWidget(goFor2);
        listIter++;
    }
}

void MapMainWindow::roomMessage(QByteArray roomMess)
{
    /*auto clickIter=JsonInter::GetInstance()->roomMap.find(nowClickNum);
    if(clickIter!=JsonInter::GetInstance()->roomMap.end())
    {
        clickIter->second->roomName="杭州提督府正门";
        clickIter->second->update();
    }*/
    while (roomMess.size()>0) {//循环截取出要打印的字符串  一行的那种
        QByteArray oneStr;
        getOneStrFromArray(roomMess, oneStr);//截取出要打印的字符串  一行的那种
        if(!roomifo.roomnamefind)//名字检测
        {
            //只有房间名以外的才需要去除颜色
            removeColorFromArray(oneStr);
            roomname(oneStr);
        }
        else if(!roomifo.RoomMessagefind)//描述检测
        {
            //只有房间名以外的才需要去除颜色
            removeColorFromArray(oneStr);
            roommes(oneStr);
        }
        else if(!roomifo.fangxiangfind)//出口检测
        {
            //只有房间名以外的才需要去除颜色
            removeColorFromArray(oneStr);
            roomout(oneStr);
        }
        else//npc检测
        {
            //只有房间名以外的才需要去除颜色
            removeColorFromArray(oneStr);
            roomnpc(oneStr);
        }
    }
}

void MapMainWindow::getOneStrFromArray(QByteArray &inArray, QByteArray &outArray)
{
    bool findStr=false;//找到回车换行
    int charNum=0;//没找到回车换行，但是到尾部了
    for(; charNum<inArray.size()-1; charNum++)
    {
        if(uchar(inArray[charNum])==0x0D && uchar(inArray[charNum+1])==0x0A)
        {
            findStr=true;
            charNum++;
            break;
        }
    }

    if(findStr)//找到回车换行
    {
        outArray=inArray.mid(0, charNum+1);
        inArray=inArray.mid(charNum+1);
        //qDebug()<<"outArray--"<<QString(outArray)<<"  backArray--"<<QString(backArray);
    }
    else
    {
        if(charNum+1 == inArray.size())//没找到回车换行，但是到尾部了
        {
            outArray=inArray;
            inArray=inArray.mid(charNum+1);
            //qDebug()<<"outArray--"<<QString(outArray)<<"  backArray--"<<QString(backArray);
        }
        else
        {
            //qDebug()<<"error  backArray--"<<QString(backArray);
        }
    }
}

bool MapMainWindow::removeColorFromArray(QByteArray &inArray)
{
    //QRegularExpression regular{"\\033\\[\\d+(;\\d+)*m"};//去除颜色
    //\x1B
    bool found=false;
    int Num=0;
    while(Num<inArray.size()-1)
    {
        if(inArray[Num]=='\x1B')
        {
            int key=Num+1;
            if(key<inArray.size() && inArray[key]=='[')//\x1B 后必是 [
            {
                key++;
                while(key<inArray.size())
                {
                    if(inArray[key]==';' || ('0'<=inArray[key] && inArray[key]<='9') || inArray[key]=='m')
                    {
                        if(inArray[key]=='m')//M结尾
                        {
                            found=true;
                            break;
                        }
                    }
                    else
                    {
                        found=false;
                        break;
                    }
                    key++;
                }
            }
            if(found)//数组中移除
            {
                inArray.remove(Num,key-Num+1);
                Num--;
            }
        }
        Num++;
    }
    return found;
}

void MapMainWindow::roomname(QByteArray &inArray)
{
    //qDebug()<<"MapMainWindow::roomname--"<<inArray;
    QRegularExpressionMatch regularmatch=nameRegStr.match(inArray);
    if(regularmatch.hasMatch())
    {
        QString backList=regularmatch.captured(1);
        //qDebug()<<"MapMainWindow::backList--"<<backList;
        ui->mapWidget->setRoomNC(backList,"");
        auto clickIter=JsonInter::GetInstance()->roomMap.find(nowClickNum);
        if(clickIter!=JsonInter::GetInstance()->roomMap.end())
        {
            clickIter->second->roomName=backList;
            clickIter->second->update();
        }
        roomifo.roomnamefind=true;
    }
}

void MapMainWindow::roommes(QByteArray &inArray)
{
    //qDebug()<<"MapMainWindow::roommes--"<<QString(inArray);
    if(!roomifo.RoomMessagebegin)
    {
        //qDebug()<<"MapMainWindow::roommes--  1111";
        QRegularExpressionMatch roomMesBeginmatch=roomMesBeginRegStr.match(inArray);
        if(roomMesBeginmatch.hasMatch())
        {
            //qDebug()<<"MapMainWindow::roommes--  2222";
            roomifo.RoomMessageArray.append(inArray);
            roomifo.RoomMessagebegin=true;
        }
    }
    else
    {
        //qDebug()<<"MapMainWindow::roommes--  3333";
        QRegularExpressionMatch roomMesendmatch=roomMesendRegStr.match(inArray);
        if(roomMesendmatch.hasMatch())
        {
            //qDebug()<<"MapMainWindow::roommes--  4444";
            ui->mapWidget->setroommes(roomifo.RoomMessageArray);
            roomifo.RoomMessagefind=true;
        }
        else
        {
            //qDebug()<<"MapMainWindow::roommes--  5555";
            roomifo.RoomMessageArray.append(inArray);
        }
    }
}

void MapMainWindow::roomout(QByteArray &inArray)
{
    //qDebug()<<"MapMainWindow::roomout--"<<QString(inArray);
    QRegularExpressionMatch roomoutmatch=roomoutRegStr.match(inArray);
    if(roomoutmatch.hasMatch())
    {
        QByteArray outList;
        bool findbegin=false;
        QByteArray outstr=roomoutmatch.captured(1).toUtf8();
        for(int num=0;num<outstr.size();num++)
        {
            if('a'<=outstr[num] && outstr[num]<='z')
            {
                findbegin=true;
                outList.append(outstr[num]);
            }
            else if('A'<=outstr[num] && outstr[num]<='Z')
            {
                findbegin=true;
                outList.append(outstr[num]-26);
            }
            else
            {
                if(findbegin)
                {
                    outList.append(';');
                    findbegin=false;
                }
            }
        }
        ui->mapWidget->setroomout(outList);
        roomifo.fangxiangfind=true;
    }
    else
    {
        QRegularExpressionMatch nooutmatch=nooutRegStr.match(inArray);//没有出口
        if(nooutmatch.hasMatch())
        {
            roomifo.fangxiangfind=true;
        }
    }
}

void MapMainWindow::roomnpc(QByteArray &inArray)
{
    //qDebug()<<"MapMainWindow::roomnpc--"<<inArray;
    QRegularExpressionMatch npcmatch=npcReg.match(inArray);//有npc
    if(npcmatch.hasMatch())
    {
        QStringList backList=npcmatch.capturedTexts();
        if(backList.size()>=4)
        {
            ui->mapWidget->appendNpc(backList[2],backList[3].toLower(),backList[1]);
        }
    }
    else
    {
        QRegularExpressionMatch endmatch=endReg.match(inArray);//结束字符
        if(endmatch.hasMatch())
        {
            //qDebug()<<"MapMainWindow::roomnpc--"<<mapcreateGetMessage;
            mapcreateGetMessage=false;
            calculateTo();
            ui->mapWidget->on_checkRoomName_clicked();
            on_saveRoomBT_clicked();
        }
    }
}

void MapMainWindow::startTime()
{
    if(jishu)
    {
        begintime=QTime::currentTime();
        jishu=false;
    }
}

QString MapMainWindow::getroomID()
{
    QString backstr;
    auto mapiter=JsonInter::GetInstance()->roomMap.find(nowClickNum);
    if(mapiter!=JsonInter::GetInstance()->roomMap.end())
        if(mapiter->first->FqEN!="")
        {
            if(mapiter->first->roomEN!="")
            {
                if(mapiter->first->sqEN!="")
                {
                    if(mapiter->first->sthqEN!="")
                    {
                        if(mapiter->first->chongfuNum==0)
                        {
                            backstr=mapiter->first->FqEN+"_"+mapiter->first->sqEN+"_"+mapiter->first->sthqEN+"_"+mapiter->first->roomEN;
                        }
                        else
                        {
                            backstr=mapiter->first->FqEN+"_"+mapiter->first->sqEN+"_"+mapiter->first->sthqEN+"_"+mapiter->first->roomEN+"_"+QString::number(mapiter->first->chongfuNum);
                        }
                    }
                    else
                    {
                        if(mapiter->first->chongfuNum==0)
                        {
                            backstr=mapiter->first->FqEN+"_"+mapiter->first->sqEN+"_"+mapiter->first->roomEN;
                        }
                        else
                        {
                            backstr=mapiter->first->FqEN+"_"+mapiter->first->sqEN+"_"+mapiter->first->roomEN+"_"+QString::number(mapiter->first->chongfuNum);
                        }
                    }
                }
                else
                {
                    if(mapiter->first->chongfuNum==0)
                    {
                        backstr=mapiter->first->FqEN+"_"+mapiter->first->roomEN;
                    }
                    else
                    {
                        backstr=mapiter->first->FqEN+"_"+mapiter->first->roomEN+"_"+QString::number(mapiter->first->chongfuNum);
                    }
                }
            }
        }
    return backstr;
}

void MapMainWindow::showEvent(QShowEvent *)
{
    mapCreaterShow=true;
}

void MapMainWindow::hideEvent(QHideEvent *)
{
    mapCreaterShow=false;
}

void MapMainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() & Qt::RightButton)
    {
        //qDebug()<<"MapMainWindow::mouseReleaseEvent  a--"<<event->pos();
        //qDebug()<<"MapMainWindow::mouseReleaseEvent  b--"<<ui->scrollArea_3->mapTo(this,QPoint(0,0));
        QPoint endPoint=ui->scrollArea_3->mapTo(this,QPoint(0,0));
        if(event->pos().x()>=endPoint.x() && event->pos().y()>=endPoint.y())
        {
            MyMenu.exec(QCursor::pos());
        }
    }
    QWidget::mouseReleaseEvent(event);
}

void MapMainWindow::on_lookRoomBT_clicked()
{
    roomifo.clear();
    ui->mapWidget->clearLayout();
    mapcreateGetMessage=true;
    emit mapCreateCmd("l");
    //QString cmdtest="测试试试:#killnpc(wei zheng);sw;aaaaa;n;&测试试试:say 1;n&测试试试:#Timer(3000,\"()sa:y( 1;say 2;say 3)\");ne;&测试试试:say 3 ;yz_qsdd_1;s";
    //WorkSys::GetInstance()->releasepareCmd(cmdtest,true);
    //cmdtest="#killnpc(wei zheng);sw;say 1;n;#Timer(3000,\"()sa:y( 1;say 2;say 3)\");ne;say 3 ;yz_qsdd_1;s";
    //WorkSys::GetInstance()->releaseCmd(cmdtest,true);
    //QString cmdtest="#path(sw)";
    //WorkSys::GetInstance()->releaseCmd(cmdtest,true);
}


void MapMainWindow::on_saveRoomBT_clicked()
{
    if(!checkTo())
    {
        auto mapiter=JsonInter::GetInstance()->roomMap.find(nowClickNum);
        if(mapiter!=JsonInter::GetInstance()->roomMap.end())
        {
            //将信息更新至roominfo，比如toroom  fromroom
            roomInfo* roomPtr=mapiter.value().first;
            ui->mapWidget->getRoomIfo(roomPtr);
            ui->mapWidget->getNpcList(roomPtr);
            roomPtr->roomPoint=mapiter.value().second->pos().toPoint();
            updateFrom(roomPtr);
            updateTo(roomPtr);


            //将信息保存至doc
            QJsonObject allObj=JsonInter::GetInstance()->allDoc;
            QJsonObject npcListJson;
            QJsonObject outListJson;
            QJsonObject oneroomJson;

            //npc
            QList<NpcInfo> aaa=roomPtr->npcInfo;
            for(int num=0;num<aaa.size();num++)
            {
                QJsonObject npcJson;
                npcJson.insert("nameZH",aaa[num].nameZH);
                npcJson.insert("nameEN",aaa[num].nameEN);
                npcJson.insert("title",aaa[num].title);
                npcListJson.insert(QString::number(num),npcJson);
            }

            //room
            QList<OutInfo> bbb=roomPtr->outInfo;
            for(int num=0;num<bbb.size();num++)
            {
                QJsonObject roomJson;
                roomJson.insert("outcmd",bbb[num].outcmd);
                roomJson.insert("outCmdNow",bbb[num].outCmdNow);
                roomJson.insert("time",bbb[num].time);
                roomJson.insert("room",bbb[num].room);
                roomJson.insert("longtime",bbb[num].longtime);
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
            //qDebug()<<"MapMainWindow::on_saveRoomBT_clicked() out--"<<roomPtr->out;
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

            allObj.insert(QString::number(nowClickNum),oneroomJson);
            JsonInter::GetInstance()->allDoc=allObj;

            //刷新出去连线
            ui->graphicsView->flushOutItem(nowClickNum);
        }
        upRoomZhEn(nowClickNum);
    }
    else{
        QMessageBox::warning(this,"出口有两个同样房间","出口有两个同样房间,取消保存");
    }
}

void MapMainWindow::on_openMap_triggered()
{
    QString filepath = QFileDialog::getOpenFileName(this, "选择单个文件", "./", tr("(*.mudmap)"));
    if(filepath!="")
    {
        ui->graphicsView->clearView();
        ui->mapWidget->clearWidget();
        clearFromRoom();
        clearToRoom();
        JsonInter::GetInstance()->getRoomInFile(filepath);
        ui->graphicsView->scene()->setSceneRect(JsonInter::GetInstance()->minX-3000,JsonInter::GetInstance()->minY-3000
                                                ,JsonInter::GetInstance()->maxX-JsonInter::GetInstance()->minX+6000
                                                ,JsonInter::GetInstance()->maxY-JsonInter::GetInstance()->minY+6000);
        //初始化房间
        ui->graphicsView->initRoom();
    }
}


void MapMainWindow::on_saveMap_triggered()
{
    //qDebug()<<"MapMainWindow::on_saveMapBT_clicked()";
    QString filepath = QFileDialog::getSaveFileName(this, "选择单个文件", "./", tr("(*.mudmap)"));
    JsonInter::GetInstance()->saveRoomInFile(filepath);
}


void MapMainWindow::on_adddll_triggered()
{
#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    if(dlliter!=nullptr)
    {
        FreeLibrary(dlliter);
        dlliter=nullptr;
        killNpc=nullptr;
        boatIn=nullptr;
        cheIn=nullptr;
    }
    if(QFile::exists("libdllToMapCreate.dll"))
    {
        dlliter=LoadLibrary(L"libdllToMapCreate.dll");
        if(dlliter!=nullptr)
        {
            //定义相同的接口，打开So并获取对象。
            killNpc=(killnpc)GetProcAddress(dlliter,"killNpc");
            if (killNpc == NULL) {
                //qDebug()<<"killNpc fail--";
                return;
            }
            boatIn=(boatin)GetProcAddress(dlliter,"boatIn");
            if (boatIn == NULL) {
                //qDebug()<<"boatIn fail--";
                return;
            }
            cheIn=(chein)GetProcAddress(dlliter,"cheIn");
            if (cheIn == NULL) {
                //qDebug()<<"cheIn fail--";
                return;
            }
            //qDebug()<<"load成功";
        }
        else
        {
            //qDebug()<<"open fail--";
        }
    }
    else
    {
        //qDebug()<<"QFile::exists fail--";
    }
#else
    if(dlliter!=nullptr)
    {
        dlclose(dlliter);
        dlliter=nullptr;
        killNpc=nullptr;
        boatIn=nullptr;
        cheIn=nullptr;
    }
    if(QFile::exists("libdllToMapCreate.so"))
    {
        char soName[30]="libdllToMapCreate.so";
        dlliter=dlopen(soName,RTLD_NOW);
        if(dlliter!=nullptr)
        {
            //定义相同的接口，打开So并获取对象。
            killNpc = (killnpc)dlsym(dlliter, "killNpc");
            if (killNpc == NULL) {
                //std::cout << mTag << "unable to find createShowWraper" << std::endl << dlerror();
                return;
            }
            boatIn = (boatin)dlsym(dlliter,"boatIn");
            if (boatIn == NULL) {
                //std::cout << mTag << "unable to find createShowWraper" << std::endl << dlerror();
                return;
            }
            cheIn = (chein)dlsym(dlliter,"cheIn");
            if (cheIn == NULL) {
                //std::cout << mTag << "unable to find createShowWraper" << std::endl << dlerror();
                return;
            }
            //qDebug()<<"load成功";
        }
        else
        {
            //qDebug()<<"open fail--";
        }
    }
#endif
}


void MapMainWindow::on_deleteDLL_triggered()
{
#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    if(dlliter!=nullptr)
    {
        FreeLibrary(dlliter);
        dlliter=nullptr;
        killNpc=nullptr;
        boatIn=nullptr;
        cheIn=nullptr;
    }
#else
    if(dlliter!=nullptr)
    {
        dlclose(dlliter);
        dlliter=nullptr;
        killNpc=nullptr;
        boatIn=nullptr;
        cheIn=nullptr;
    }
#endif
}

void MapMainWindow::on_cmdLE_returnPressed()
{
    QString cmdname=ui->cmdLE->text();
    ui->cmdLE->clear();
    if(cmdname!="l")
    {
        for(int num=0; num<toroomLayout->count(); num++)
        {
            QString outCB, cmd, time, room;
            bool longlongtime;
            ((GoForm*)(toroomLayout->itemAt(num)->widget()))->getWidget(outCB, cmd, time, room, longlongtime);
            if(cmd==cmdname)
            {
                //发送命令，等待成功
                this->waitOut.outcmd=outCB;
                this->waitOut.outCmdNow=cmd;
                this->waitOut.time=time.toInt();
                this->waitOut.room=room.toInt();
                this->waitOut.longtime=longlongtime;
                waitGo=true;
                waitgoForm=((GoForm*)(toroomLayout->itemAt(num)->widget()));
                jishu=true;
                //#path(yz_mc:#chein(qu xinyang)&xy_mc:xia)
                WorkSys::GetInstance()->releasepareCmd("#path("+getroomID()+":"+cmd+")", true);
                break;
            }
        }
    }
    else
        on_lookRoomBT_clicked();
}


void MapMainWindow::on_action_triggered()
{
    configWidget.show();
}

