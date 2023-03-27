#include "statusform.h"
#include "KillSys/killsys.h"
#include "qjsonarray.h"
#include "ui_statusform.h"
#include <statusBar/pointbar.h>
#include <QRegularExpression>
#include <QJsonDocument>
#include <QJsonObject>
#include <INI/inimanarge.h>
#include <work/worksys.h>

StatusForm::StatusForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusForm)
{
    ui->setupUi(this);
    ui->resizeBT->setCheckable(true);
    ui->mpBar->setPointStatus(pointStatus::mp);
    ui->jingliBar->setPointStatus(pointStatus::mp);
    setStyleSheet("background-color: rgb(169,169,169);color:black");
    UserNameGmcp backstruct;
    INIManarge::GetInstance()->getUserNameGmcp(backstruct);
    ID=backstruct.userEnName;
    //on_resizeBT_clicked(true);
}

StatusForm::~StatusForm()
{
    delete ui;
}

void StatusForm::setHpMpStatus(int hpMax, int hped, int hpNow, int mpMax, int mped, int mpNow)
{
    ui->hpBar->setPointNum(hpNow, hped, hpMax);
    ui->mpBar->setPointNum(mpNow, mped, mpMax);
}

void StatusForm::setHpMpStatus(QStringList testList)
{
    if(testList.size()>=18)
    {
        int hpMax=testList[6].toInt(), hped=testList[7].toInt(), hpNow=testList[8].toInt(), mpMax=testList[9].toInt(), mped=testList[10].toInt(), mpNow=testList[11].toInt();
        ui->hpBar->setPointNum(hpNow, hped, hpMax);
        ui->mpBar->setPointNum(mpNow, mped, mpMax);
        ui->neiliBar->setPointNum(testList[3].toInt(), testList[2].toInt(), testList[2].toInt());
        ui->jingliBar->setPointNum(testList[5].toInt(), testList[4].toInt(), testList[4].toInt());
        ui->jingyan->setText("经验:"+testList[0]+"   ");
        ui->qianneng->setText("潜能:"+testList[1]+"   ");
        ui->zhenqi->setText("真气:"+testList[12]+"   ");
        ui->zhanyi->setText("战意:"+testList[13]+"   ");
        ui->shiwu->setText("食物:"+testList[14]+"   ");
        ui->yinshui->setText("饮水:"+testList[15]+"   ");
        QString zhandou(testList[16].toInt()==1?"是":"否");
        ui->zhandou->setText("战斗:"+zhandou+"   ");
        QString manglu(testList[17].toInt()==1?"是":"否");
        ui->mang->setText("忙碌:"+manglu+"   ");
    }
}

void StatusForm::setHpMpStatus(QString instr)
{
    QRegularExpression regStr("^#setHpBar\\(\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\"\\)$");
    QRegularExpressionMatch regularmatch=regStr.match(instr);
    if(regularmatch.hasMatch())
    {
        QStringList testList=regularmatch.capturedTexts();
        testList.removeFirst();
        setHpMpStatus(testList);
    }
}

void StatusForm::setStatus(QByteArray &newstring, GMCPType type)
{
    QByteArray newstr;
    switch (type) {
    case GMCPType::status:
    {
        newstr=newstring.mid(14,newstring.size()-2-14);
    }
        break;
    case GMCPType::buff:
    {
        newstr=newstring.mid(12,newstring.size()-2-12);
    }
        break;
    case GMCPType::move:
    {
        newstr=newstring.mid(12,newstring.size()-2-12);
    }
        break;
    case GMCPType::combat:
    {
        newstr=newstring.mid(14,newstring.size()-2-14);
    }
        break;
    default:
        return;
        break;
    }
    //qDebug()<<"StatusForm::setStatus  ---"<<newstr;
    stringToJson(newstr, type);
}

void StatusForm::hideAll(bool flag)
{
    ui->hpHead->setHidden(flag);
    ui->hpBar->setHidden(flag);
    ui->mpHead->setHidden(flag);
    ui->mpBar->setHidden(flag);
    ui->neiliHead->setHidden(flag);
    ui->neiliBar->setHidden(flag);
    ui->jingliHead->setHidden(flag);
    ui->jingliBar->setHidden(flag);
    ui->jingyan->setHidden(flag);
    ui->qianneng->setHidden(flag);
    ui->zhenqi->setHidden(flag);
    ui->zhanyi->setHidden(flag);
    ui->shiwu->setHidden(flag);
    ui->yinshui->setHidden(flag);
    ui->zhandou->setHidden(flag);
    ui->mang->setHidden(flag);
    ui->buffWidget->setHidden(flag);
    ui->widget->setHidden(flag);
}

void StatusForm::setSizes(int Width, int Height)
{
    width=Width;
    height=Height;
}

bool StatusForm::getHideStatus()
{
    return ui->hpHead->isHidden();
}

void StatusForm::setMyId(QString name, QString id)
{
    ID=id;
}

void StatusForm::on_resizeBT_clicked(bool checked)
{
    hideAll(checked);
    if(checked)
    {
        resize(20,20);
    }
    else
    {
        resize(width,height);
    }
    emit StatusFormHide(checked);
}

void StatusForm::stringToJson(QByteArray &stringstr, GMCPType &type)
{
    QJsonDocument doucumen;
    QJsonParseError json_error;
    doucumen = QJsonDocument::fromJson(stringstr, &json_error);
    if(json_error.error == QJsonParseError::NoError)
    {
        switch (type) {
        case GMCPType::status:
        {
            QJsonObject newObj=doucumen.object();
            QJsonObject::Iterator objone=newObj.begin();
            QJsonObject::Iterator nowid=newObj.find("id");
            if( nowid==newObj.end() || (nowid!=newObj.end() && nowid.value().toString()==ID))
            {
                while(objone!=newObj.end())
                {
                    //qDebug()<<"StatusForm::stringToJson  ---"<<objone.key();
                    if(objone.key()=="water")//饮水
                    {
                        ui->yinshui->setText("饮水:"+QString::number(objone.value().toInt())+"   ");
                    }
                    else if(objone.key()=="food")//食物
                    {
                        ui->shiwu->setText("食物:"+QString::number(objone.value().toInt())+"   ");
                    }
                    else if(objone.key()=="qi")//气血
                    {
                        ui->hpBar->setPointNowNum(objone.value().toInt());
                    }
                    else if(objone.key()=="neili")//内力
                    {
                        ui->neiliBar->setPointNowNum(objone.value().toInt());
                    }
                    else if(objone.key()=="vigour/qi")//真气
                    {
                        int zhenqi=0;
                        if(objone.value().isNull())
                        {
                            zhenqi=0;
                        }
                        else
                        {
                            zhenqi=objone.value().toInt();
                        }
                        ui->zhenqi->setText("真气:"+QString::number(zhenqi)+"   ");
                    }
                    else if(objone.key()=="is_busy")//忙碌  "true"
                    {
                        QString busystr=objone.value().toString();
                        ui->mang->setText("忙碌:"+busystr+"   ");
                        WorkSys::GetInstance()->busyStatus(busystr=="true"?true:false);
                    }
                    else if(objone.key()=="name")//敌人名字 "加力"
                    {
                        objone.value().toString();
                    }
                    else if(objone.key()=="id")//敌人id   "mu zhuangzi#1942144"
                    {
                        objone.value().toString();
                    }
                    else if(objone.key()=="fighter_spirit")//战意
                    {
                        ui->zhanyi->setText("战意:"+QString::number(objone.value().toInt())+"   ");
                    }
                    else if(objone.key()=="is_fighting")//战斗中  "true"
                    {
                        QString zhandou=objone.value().toString();
                        ui->zhandou->setText("战斗:"+zhandou+"   ");
                        KillSys::GetInstance()->fightting(zhandou);
                    }
                    else if(objone.key()=="eff_qi")//有效气血
                    {
                        ui->hpBar->setPointEndNum(objone.value().toInt());
                    }
                    else if(objone.key()=="jing")//精神
                    {
                        ui->mpBar->setPointNowNum(objone.value().toInt());
                    }
                    else if(objone.key()=="eff_jing")//有效精神
                    {
                        ui->mpBar->setPointEndNum(objone.value().toInt());
                    }
                    else if(objone.key()=="jingli")//精力
                    {
                        ui->jingliBar->setPointNowNum(objone.value().toInt());
                    }
                    else if(objone.key()=="potential")//潜能
                    {
                        ui->qianneng->setText("潜能:"+QString::number(objone.value().toInt())+"   ");
                    }
                    else if(objone.key()=="combat_exp")//经验
                    {
                        ui->jingyan->setText("潜能:"+QString::number(objone.value().toInt())+"   ");
                    }
                    else if(objone.key()=="level")//级别
                    {
                        ui->dengji->setText("级别:"+QString::number(objone.value().toInt())+"   ");
                    }
                    else if(objone.key()=="title")//头衔
                    {
                        ui->touxian->setText("头衔:"+objone.value().toString()+"   ");
                    }
                    else if(objone.key()=="family/family_name")//门派  family/family_na
                    {
                        ui->menpai->setText("门派:"+objone.value().toString()+"   ");
                    }
                    else if(objone.key()=="vigour/yuan")//真元
                    {
                        int zhenyuan=0;
                        if(objone.value().isNull())
                        {
                            zhenyuan=0;
                        }
                        else
                        {
                            zhenyuan=objone.value().toInt();
                        }
                        ui->zhenyuan->setText("真元:"+QString::number(zhenyuan)+"   ");
                    }
                    else if(objone.key()=="per")//容貌
                    {
                        ui->rongmao->setText("容貌:"+QString::number(objone.value().toInt())+"   ");
                    }
                    else if(objone.key()=="str")//膂力
                    {
                        ui->lvli->setText("膂力:"+QString::number(objone.value().toInt())+"   ");
                    }
                    else if(objone.key()=="int")//悟性
                    {
                        ui->wuxing->setText("悟性:"+QString::number(objone.value().toInt())+"   ");
                    }
                    else if(objone.key()=="con")//根骨
                    {
                        ui->gengu->setText("根骨:"+QString::number(objone.value().toInt())+"   ");
                    }
                    else if(objone.key()=="dex")//身法
                    {
                        ui->shenfa->setText("身法:"+QString::number(objone.value().toInt())+"   ");
                    }
                    else if(objone.key()=="max_jingli")//最大精力
                    {
                        ui->jingliBar->setPointEndNum(objone.value().toInt());
                        ui->jingliBar->setPointMaxNum(objone.value().toInt());
                    }
                    else if(objone.key()=="max_neili")//最大内力
                    {
                        ui->neiliBar->setPointEndNum(objone.value().toInt());
                        ui->neiliBar->setPointMaxNum(objone.value().toInt());
                    }
                    else if(objone.key()=="max_jing")//最大精神
                    {
                        ui->mpBar->setPointMaxNum(objone.value().toInt());
                    }
                    else if(objone.key()=="max_qi")//最大气血
                    {
                        ui->hpBar->setPointMaxNum(objone.value().toInt());
                    }
                    objone++;
                }
            }
        }
            break;
        case GMCPType::buff:
        {
            QJsonObject newObj=doucumen.object();
            QJsonObject::Iterator objone=newObj.begin();
            while(objone!=newObj.end())
            {
                if(objone.key()=="name")//效果名称  "木桩子"
                {
                    objone.value().toString();
                }
                else if(objone.key()=="effect1")//具体效果1
                {
                    objone.value().toString();
                }
                else if(objone.key()=="effect2")//具体效果2
                {
                    objone.value().toString();
                }
                else if(objone.key()=="effect3")//具体效果3
                {
                    objone.value().toString();
                }
                else if(objone.key()=="effect4")//具体效果4
                {
                    objone.value().toString();
                }
                else if(objone.key()=="effect5")//具体效果5
                {
                    objone.value().toString();
                }
                else if(objone.key()=="last_time")//持续时间
                {
                    objone.value().toInt();
                }
                else if(objone.key()=="type")//效果类型
                {
                    objone.value().toString();
                }
                else if(objone.key()=="is_end")//效果结束  "is_end":"true"
                {
                    objone.value().toString();
                }
                else if(objone.key()=="last_inc")//效果延时
                {
                    objone.value().toInt();
                }
                else if(objone.key()=="terminated")//将中止的效果
                {
                    objone.value().toString();
                }
                objone++;
            }
        }
            break;
        case GMCPType::move:
        {//\xFF\xFA\xC9GMCP.Move [{\"result\":\"true\",\"dir\":[\"west\"],\"short\":\"\xE9\xBE\x9F\xE6\xB3\x89\"}]\xFF\xF0
            //[{"result":"true","dir":["east","northwest"],"short":"比武场"}]
            QJsonArray newArray=doucumen.array();
            for(int num=0; num<newArray.size(); num++)
            {
                QJsonObject newObj=newArray.at(num).toObject();
                QJsonObject::Iterator objone=newObj.begin();
                while(objone!=newObj.end())
                {
                    if(objone.key()=="result")//移动结果 true:成功
                    {
                        QString moveresult=objone.value().toString();
                    }
                    else if(objone.key()=="dir")//出口
                    {
                        objone.value().toArray();
                    }
                    else if(objone.key()=="short")//房间
                    {
                        objone.value().toArray();
                    }
                    objone++;
                }
            }
        }
            break;
        case GMCPType::combat:
        {//\xFF\xFA\xC9GMCP.combat [{"enemy_in":1,"name":"木桩子","id":"mu zhuangzi#1942144"}]\xFF\xF0
            //[{"enemy_in":1,"name":"流氓","id":"liu mang#930301"}]
            //{"enemy_in":1,"name":"流氓","id":"liu mang#7830018"}
            QJsonArray newArray=doucumen.array();
            for(int num=0; num<newArray.size(); num++)
            {
                QJsonObject newObj=newArray.at(num).toObject();
                QJsonObject::Iterator objone=newObj.begin();

                ///战斗系统需要战斗值
                bool enemy_inbool=false;
                bool namebool=false;
                bool idbool=false;
                QString id;
                QString name;
                int enemy_inin;

                while(objone!=newObj.end())
                {
                    if(objone.key()=="id")//liu mang#930301
                    {
                        idbool=true;
                        id=objone.value().toString();
                        //qDebug()<<"StatusForm::stringToJson  id---"<<id;
                    }
                    else if(objone.key()=="name")//name
                    {
                        namebool=true;
                        name=objone.value().toString();
                        //qDebug()<<"StatusForm::stringToJson  name---"<<name;
                    }
                    else if(objone.key()=="enemy_in")//enemy_in
                    {
                        enemy_inbool=true;
                        enemy_inin=objone.value().toInt();
                        //qDebug()<<"StatusForm::stringToJson  enemy_inin---"<<enemy_inin;
                    }
                    objone++;
                }
                if(idbool && namebool)
                {
                    if(enemy_inbool)//有敌人进入战斗
                    {
                        if(enemy_inin==1)//进入战斗为1
                        {
                            //KillSys::GetInstance()->killmeStart(name,id);
                        }
                        else
                        {
                            //脱离战斗
                            qDebug()<<"StatusForm::stringToJson  GMCPType::combat   die die die---";
                        }
                    }
                    else
                    {
                        KillSys::GetInstance()->fightCheck(name,id);
                    }
                }
            }
        }
            break;
        default:
            break;
        }
    }
    else
    {
        //qDebug()<<"StatusForm::stringToJson  ---"<<stringstr;
    }
}

