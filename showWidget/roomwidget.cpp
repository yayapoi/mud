#include "roomwidget.h"
#include "ui_roomwidget.h"
#include "flowjson/jsoninter.h"
#include <QMessageBox>
#include <ZHToEN/zhtopy.h>

RoomWidget::RoomWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomWidget)
{
    ui->setupUi(this);
    npcLayout=new QVBoxLayout();
    ui->npclist->setLayout(npcLayout);
}

RoomWidget::~RoomWidget()
{
    delete ui;
}

void RoomWidget::clearWidget()
{
    nowClickNum=-1;
    clearLayout();
    ui->FirstZH->clear();
    ui->FirstEN->clear();
    ui->secondZH->clear();
    ui->secondEN->clear();
    ui->srdZH->clear();
    ui->srdEN->clear();
    ui->roomZN->clear();
    ui->roomEN->clear();
    ui->roomID->clear();
    ui->roomMessage->clear();
    ui->roomColor->clear();
    ui->roomNum->clear();
    ui->outLE->clear();
    ui->nowLE->clear();
}

void RoomWidget::clearLayout()
{
    QLayoutItem* child;
    while ((child = npcLayout->itemAt(0)) != nullptr) {
        npcLayout->removeItem(child);
        delete child->widget();
        delete child;
        child = nullptr;
    }
}

void RoomWidget::setWidger(roomInfo *infoList)
{
    clearWidget();
    nowClickNum=infoList->roomNum;
    ui->FirstZH->setText(infoList->FqZH);
    ui->FirstEN->setText(infoList->FqEN);
    ui->secondZH->setText(infoList->sqZH);
    ui->secondEN->setText(infoList->sqEN);
    ui->srdZH->setText(infoList->sthqZH);
    ui->srdEN->setText(infoList->sthqEN);
    ui->roomZN->setText(infoList->roomZH);
    ui->roomEN->setText(infoList->roomEN);
    ui->roomMessage->setText(infoList->roomDes);
    ui->roomColor->setText(infoList->roomColor);
    ui->roomNum->setText(QString::number(infoList->roomNum));
    ui->outLE->setText(infoList->out);
    //qDebug()<<"RoomWidget::setWidger out--"<<infoList->out;
    ui->nowLE->setText(infoList->outnow);
    if(ui->FirstEN->text()!="")
    {
        if(ui->roomEN->text()!="")
        {
            if(ui->secondEN->text()!="")
            {
                if(ui->srdEN->text()!="")
                {
                    if(infoList->chongfuNum==0)
                    {
                        ui->roomID->setText(ui->FirstEN->text()+"_"+ui->secondEN->text()+"_"+ui->srdEN->text()+"_"+ui->roomEN->text());
                    }
                    else
                    {
                        ui->roomID->setText(ui->FirstEN->text()+"_"+ui->secondEN->text()+"_"+ui->srdEN->text()+"_"+ui->roomEN->text()+"_"+QString::number(infoList->chongfuNum));
                    }
                }
                else
                {
                    if(infoList->chongfuNum==0)
                    {
                        ui->roomID->setText(ui->FirstEN->text()+"_"+ui->secondEN->text()+"_"+ui->roomEN->text());
                    }
                    else
                    {
                        ui->roomID->setText(ui->FirstEN->text()+"_"+ui->secondEN->text()+"_"+ui->roomEN->text()+"_"+QString::number(infoList->chongfuNum));
                    }
                }
            }
            else
            {
                if(infoList->chongfuNum==0)
                {
                    ui->roomID->setText(ui->FirstEN->text()+"_"+ui->roomEN->text());
                }
                else
                {
                    ui->roomID->setText(ui->FirstEN->text()+"_"+ui->roomEN->text()+"_"+QString::number(infoList->chongfuNum));
                }
            }
        }
        else
        {
            ui->roomID->setText("");
        }
    }
    else
    {
        ui->roomID->setText("");
    }
    seNpcList(infoList);
}

void RoomWidget::seNpcList(roomInfo *infoList)
{
    for(int num=0;num<infoList->npcInfo.size();num++)
    {
        NPCForm* npcFor2=new NPCForm;
        npcFor2->initWidget((infoList->npcInfo)[num].nameZH, (infoList->npcInfo)[num].nameEN, (infoList->npcInfo)[num].title);
        connect(npcFor2,&NPCForm::deleteNpc,this,[this](NPCForm* removeItem){
            this->npcLayout->removeWidget(removeItem);
            removeItem->deleteLater();
        });
        npcLayout->addWidget(npcFor2);
    }
}

void RoomWidget::uselastname(QString &fzh, QString &fen, QString &szh, QString &sen, QString &srdzh, QString &srden)
{
    if(ui->FirstZH->text().isEmpty())
    {
        ui->FirstZH->setText(fzh);
        ui->FirstEN->setText(fen);
        ui->secondZH->setText(szh);
        ui->secondEN->setText(sen);
        ui->srdZH->setText(srdzh);
        ui->srdEN->setText(srden);
    }
}

void RoomWidget::getNpcList(roomInfo *infoList)
{
    infoList->npcInfo.clear();
    for(int num=0; num<npcLayout->count(); num++)
    {
        NpcInfo oneNpc;
        ((NPCForm*)(npcLayout->itemAt(num)->widget()))->getWidget(oneNpc.nameZH,oneNpc.nameEN,oneNpc.title);
        infoList->npcInfo.append(oneNpc);
    }
}

void RoomWidget::getRoomIfo(roomInfo *infoList)
{
    infoList->FqZH=ui->FirstZH->text();
    infoList->FqEN=ui->FirstEN->text();
    infoList->sqZH=ui->secondZH->text();
    infoList->sqEN=ui->secondEN->text();
    infoList->sthqZH=ui->srdZH->text();
    infoList->sthqEN=ui->srdEN->text();
    infoList->roomZH=ui->roomZN->text();
    infoList->roomEN=ui->roomEN->text();
    infoList->roomDes=ui->roomMessage->toPlainText();
    infoList->roomColor=ui->roomColor->text();
    infoList->roomNum=ui->roomNum->text().toInt();
    infoList->out=ui->outLE->text();
    infoList->outnow=ui->nowLE->text();
}

QString RoomWidget::getRoomout()
{
    return ui->outLE->text();
}

QString RoomWidget::getRoomnowout()
{
    return ui->nowLE->text();
}

void RoomWidget::setRoomNC(QString name, QString color)
{
    ui->roomZN->setText(name);
    ui->roomEN->setText(ZhToPY::Instance()->zhToJP(name).toLower());
    ui->roomColor->setText(color);
}

void RoomWidget::appendNpc(QString nameZH, QString nameEN, QString title)
{
    NPCForm* npcFor2=new NPCForm;
    npcFor2->initWidget(title, nameZH, nameEN);
    connect(npcFor2,&NPCForm::deleteNpc,this,[this](NPCForm* removeItem){
        this->npcLayout->removeWidget(removeItem);
        removeItem->deleteLater();
    });
    npcLayout->addWidget(npcFor2);
}

void RoomWidget::setroommes(QString roomme)
{
    ui->roomMessage->append(roomme);
}

void RoomWidget::setroomout(QString roomout)
{
    ui->outLE->setText(roomout);
}

void RoomWidget::on_checkRoomName_clicked()
{
    if(nowClickNum==-1)
    {
        QMessageBox::warning(this,"房间为空","房间未选择，请先选择房间");
        return;
    }
    if(ui->FirstZH->text()=="")
    {
        QMessageBox::warning(this,"区域为空","第一区域不应为空");
    }
    else
    {
        if(ui->roomEN->text()=="")
        {
            QMessageBox::warning(this,"房间英文为空","房间英文不应为空");
        }
        else
        {
            QList<int> roomNum;
            auto myself=JsonInter::GetInstance()->roomMap.find(nowClickNum);
            auto mapInter=JsonInter::GetInstance()->roomMap.begin();
            while(mapInter!=JsonInter::GetInstance()->roomMap.end())
            {
                if(mapInter!=myself &&
                        mapInter.value().first->FqEN==ui->FirstEN->text() &&
                        mapInter.value().first->sqEN==ui->secondEN->text() &&
                        mapInter.value().first->sthqEN==ui->srdEN->text() &&
                        mapInter.value().first->roomEN==ui->roomEN->text())
                {
                    roomNum.append(mapInter.value().first->chongfuNum);
                }
                mapInter++;
            }
            qSort(roomNum.begin(), roomNum.end());
            int num=0;
            for(; num<roomNum.size(); num++)
            {
                if(num!=roomNum[num])
                {
                    break;
                }
            }
            myself->first->chongfuNum=num;

            QString roomId="";
            if(ui->secondEN->text()!="")
            {
                if(ui->srdEN->text()!="")
                {
                    roomId=ui->FirstEN->text()+"_"+ui->secondEN->text()+"_"+ui->srdEN->text()+"_"+ui->roomEN->text();
                }
                else
                {
                    roomId=ui->FirstEN->text()+"_"+ui->secondEN->text()+"_"+ui->roomEN->text();
                }
            }
            else
            {
                roomId=ui->FirstEN->text()+"_"+ui->roomEN->text();
            }
            if(num!=0)
            {
                roomId=roomId+"_"+QString::number(num);
            }
            ui->roomID->setText(roomId);
        }
    }
}

void RoomWidget::on_checkFirstEN_clicked()
{
    if(nowClickNum==-1)
    {
        QMessageBox::warning(this,"房间为空","房间未选择，请先选择房间");
        return;
    }
    auto mapInter=JsonInter::GetInstance()->roomMap.begin();
    while(true)
    {
        bool findError=false;
        if(mapInter==JsonInter::GetInstance()->roomMap.end())
        {
            break;
        }
        if(mapInter.value().first->FqZH!=ui->FirstZH->text() && mapInter.value().first->FqEN==ui->FirstEN->text())
        {
            findError=true;
        }
        if(findError)
        {
            QMessageBox::warning(this,"简拼重复","第一区域英文名重复，请重新换一个简拼并检测");
            break;
        }
        mapInter++;
    }
}


void RoomWidget::on_FirstZH_textChanged(const QString &arg1)
{
    ui->FirstEN->setText(ZhToPY::Instance()->zhToJP(arg1).toLower());
}


void RoomWidget::on_secondZH_textChanged(const QString &arg1)
{
    ui->secondEN->setText(ZhToPY::Instance()->zhToJP(arg1).toLower());
}


void RoomWidget::on_srdZH_textChanged(const QString &arg1)
{
    ui->srdEN->setText(ZhToPY::Instance()->zhToJP(arg1).toLower());
}

