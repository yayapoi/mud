#include "mainwindow.h"
#include "qevent.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <iostream>
#include <QFontDatabase>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileDialog>
#include <QFile>
#include <INI/inimanarge.h>

struct totalZlibStruct{
    int showNum=0;//出现几次
    int maxSize=0;//这种倍率下最大的包
    int minSize=999999;//这种倍率下最小的包
};
/** @brief 统计压缩次数，压缩倍率，出现几次*/
QMap<double, totalZlibStruct*> totalZlibNum;

/** @brief 统计压缩次数，压缩倍率，出现几次*/
void testtotalZlibNum(int outNum, int inNum)
{
    double levelNum=outNum/inNum;
    if(levelNum<0.999)
    {
        totalZlibNum.value(0.999)->showNum+=1;
        if(inNum>totalZlibNum.value(0.999)->maxSize)
        {
            totalZlibNum.value(0.999)->maxSize=inNum;
        }
        if(totalZlibNum.value(0.999)->minSize>inNum)
        {
            totalZlibNum.value(0.999)->minSize=inNum;
        }
    }
    else if(levelNum<1.999)
    {
        totalZlibNum.value(1.999)->showNum+=1;
        if(inNum>totalZlibNum.value(1.999)->maxSize)
        {
            totalZlibNum.value(1.999)->maxSize=inNum;
        }
        if(totalZlibNum.value(1.999)->minSize>inNum)
        {
            totalZlibNum.value(1.999)->minSize=inNum;
        }
    }
    else if(levelNum<2.999)
    {
        totalZlibNum.value(2.999)->showNum+=1;
        if(inNum>totalZlibNum.value(2.999)->maxSize)
        {
            totalZlibNum.value(2.999)->maxSize=inNum;
        }
        if(totalZlibNum.value(2.999)->minSize>inNum)
        {
            totalZlibNum.value(2.999)->minSize=inNum;
        }
    }
    else if(levelNum<3.999)
    {
        totalZlibNum.value(3.999)->showNum+=1;
        if(inNum>totalZlibNum.value(3.999)->maxSize)
        {
            totalZlibNum.value(3.999)->maxSize=inNum;
        }
        if(totalZlibNum.value(3.999)->minSize>inNum)
        {
            totalZlibNum.value(3.999)->minSize=inNum;
        }
    }
    else if(levelNum<4.999)
    {
        totalZlibNum.value(4.999)->showNum+=1;
        if(inNum>totalZlibNum.value(4.999)->maxSize)
        {
            totalZlibNum.value(4.999)->maxSize=inNum;
        }
        if(totalZlibNum.value(4.999)->minSize>inNum)
        {
            totalZlibNum.value(4.999)->minSize=inNum;
        }
    }
    else if(levelNum<5.999)
    {
        totalZlibNum.value(5.999)->showNum+=1;
        if(inNum>totalZlibNum.value(5.999)->maxSize)
        {
            totalZlibNum.value(5.999)->maxSize=inNum;
        }
        if(totalZlibNum.value(5.999)->minSize>inNum)
        {
            totalZlibNum.value(5.999)->minSize=inNum;
        }
    }
    else if(levelNum<6.999)
    {
        totalZlibNum.value(6.999)->showNum+=1;
        if(inNum>totalZlibNum.value(6.999)->maxSize)
        {
            totalZlibNum.value(6.999)->maxSize=inNum;
        }
        if(totalZlibNum.value(6.999)->minSize>inNum)
        {
            totalZlibNum.value(6.999)->minSize=inNum;
        }
    }
    else if(levelNum<7.999)
    {
        totalZlibNum.value(7.999)->showNum+=1;
        if(inNum>totalZlibNum.value(7.999)->maxSize)
        {
            totalZlibNum.value(7.999)->maxSize=inNum;
        }
        if(totalZlibNum.value(7.999)->minSize>inNum)
        {
            totalZlibNum.value(7.999)->minSize=inNum;
        }
    }
    else if(levelNum<8.999)
    {
        totalZlibNum.value(8.999)->showNum+=1;
        if(inNum>totalZlibNum.value(8.999)->maxSize)
        {
            totalZlibNum.value(8.999)->maxSize=inNum;
        }
        if(totalZlibNum.value(8.999)->minSize>inNum)
        {
            totalZlibNum.value(8.999)->minSize=inNum;
        }
    }
    else if(levelNum<9.999)
    {
        totalZlibNum.value(9.999)->showNum+=1;
        if(inNum>totalZlibNum.value(9.999)->maxSize)
        {
            totalZlibNum.value(9.999)->maxSize=inNum;
        }
        if(totalZlibNum.value(9.999)->minSize>inNum)
        {
            totalZlibNum.value(9.999)->minSize=inNum;
        }
    }
    else if(levelNum<10.999)
    {
        totalZlibNum.value(10.999)->showNum+=1;
        if(inNum>totalZlibNum.value(10.999)->maxSize)
        {
            totalZlibNum.value(10.999)->maxSize=inNum;
        }
        if(totalZlibNum.value(10.999)->minSize>inNum)
        {
            totalZlibNum.value(10.999)->minSize=inNum;
        }
    }
    else if(levelNum<14.999)
    {
        totalZlibNum.value(14.999)->showNum+=1;
        if(inNum>totalZlibNum.value(14.999)->maxSize)
        {
            totalZlibNum.value(14.999)->maxSize=inNum;
        }
        if(totalZlibNum.value(14.999)->minSize>inNum)
        {
            totalZlibNum.value(14.999)->minSize=inNum;
        }
    }
    else if(levelNum<19.999)
    {
        totalZlibNum.value(19.999)->showNum+=1;
        if(inNum>totalZlibNum.value(19.999)->maxSize)
        {
            totalZlibNum.value(19.999)->maxSize=inNum;
        }
        if(totalZlibNum.value(19.999)->minSize>inNum)
        {
            totalZlibNum.value(19.999)->minSize=inNum;
        }
    }
    else if(levelNum<29.999)
    {
        totalZlibNum.value(29.999)->showNum+=1;
        if(inNum>totalZlibNum.value(29.999)->maxSize)
        {
            totalZlibNum.value(29.999)->maxSize=inNum;
        }
        if(totalZlibNum.value(29.999)->minSize>inNum)
        {
            totalZlibNum.value(29.999)->minSize=inNum;
        }
    }
    else if(levelNum<39.999)
    {
        totalZlibNum.value(39.999)->showNum+=1;
        if(inNum>totalZlibNum.value(39.999)->maxSize)
        {
            totalZlibNum.value(39.999)->maxSize=inNum;
        }
        if(totalZlibNum.value(39.999)->minSize>inNum)
        {
            totalZlibNum.value(39.999)->minSize=inNum;
        }
    }
    else if(levelNum<49.999)
    {
        totalZlibNum.value(49.999)->showNum+=1;
        if(inNum>totalZlibNum.value(49.999)->maxSize)
        {
            totalZlibNum.value(49.999)->maxSize=inNum;
        }
        if(totalZlibNum.value(49.999)->minSize>inNum)
        {
            totalZlibNum.value(49.999)->minSize=inNum;
        }
    }
}

/** @brief 显示统计压缩次数，压缩倍率，出现几次*/
void showtotalZlibNum()
{
    QMap<double, totalZlibStruct*>::iterator beginite=totalZlibNum.begin();
    while (beginite!=totalZlibNum.end()) {
        //qDebug()<<"key="<<beginite.key()<<"  showNum--"<<beginite.value()->showNum<<"  maxSize--"<<beginite.value()->maxSize<<"  minSize--"<<beginite.value()->minSize;
        beginite++;
    }
}

void inittotalZlibNum()
{
    totalZlibNum.insert(0.999,new totalZlibStruct);
    totalZlibNum.insert(1.999,new totalZlibStruct);
    totalZlibNum.insert(2.999,new totalZlibStruct);
    totalZlibNum.insert(3.999,new totalZlibStruct);
    totalZlibNum.insert(4.999,new totalZlibStruct);
    totalZlibNum.insert(5.999,new totalZlibStruct);
    totalZlibNum.insert(6.999,new totalZlibStruct);
    totalZlibNum.insert(7.999,new totalZlibStruct);
    totalZlibNum.insert(8.999,new totalZlibStruct);
    totalZlibNum.insert(9.999,new totalZlibStruct);
    totalZlibNum.insert(10.999,new totalZlibStruct);
    totalZlibNum.insert(14.999,new totalZlibStruct);
    totalZlibNum.insert(19.999,new totalZlibStruct);
    totalZlibNum.insert(29.999,new totalZlibStruct);
    totalZlibNum.insert(39.999,new totalZlibStruct);
    totalZlibNum.insert(49.999,new totalZlibStruct);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    zout.resize(zoutSize);
    showGmcpCheck asdf;
    INIManarge::GetInstance()->getCheckGmcp(asdf);
    INIManarge::GetInstance()->setCheckGmcp(asdf);
    ui->statusbar->hide();
    ui->cmdLE->setStyleSheet("background-color: rgb(0, 0, 0);color:lightGray;");
    initSysTrayIcon();

    /*
    void getSendMessage(int port, QString lei, QString name, QStringList regList);
signals:
    void getMessage(QList<QString>);*/
    connect(&(tcpServerForm.tcpServerControl),&TcpServerControl::getMessage,[&](QList<QString> StrList){cmdControl.appendMessage(StrList);});
    connect(&testRegClass,&RegClass::regStrSendToTcp,&(tcpServerForm.tcpServerControl),&TcpServerControl::getSendMessage);
    connect(&testRegClass,&RegClass::regStrSend,[&](QString Str){cmdControl.appendMessage(Str);});
    connect(&cmdControl,&CmdControl::newMessage,[&](QQueue<QString> queueStr){cmdDo.newMessage(queueStr);});
    connect(&configForm,&ConfigForm::closeWidget,this,[this](){
        QString name;
        this->configForm.getNameAndID(name,this->id);
        this->ui->fightTE->setMyId(name, this->id);
    });
    connect(&cmdDo,&CmdDo::setHPBar,[&](QString hpStr){ui->fightTE->setHpMpStatus(hpStr);});
    connect(&cmdDo,&CmdDo::pritf,[&](QString pritfStr){
        QRegularExpressionMatch regularmatch=regStr.match(pritfStr, 0);
        if(regularmatch.hasMatch())
        {
            QString pritfStrstr=regularmatch.captured(1);
            ui->fightTE->appendNewText(pritfStrstr);
            testRegClass.getMessage(pritfStrstr.toUtf8());
            //qDebug()<<"checkStr--";
        }
    });
    connect(&cmdDo,&CmdDo::newRegStr,[&](QString newRegStr){testRegClass.newRegStr(newRegStr);});//发送给触发类
    connect(&cmdDo,&CmdDo::deleteRegStr,[&](QString deleteRegStr){testRegClass.deleteRegStr(deleteRegStr);});//发送给触发类
    connect(&cmdDo,&CmdDo::enableRegStr,[&](QString enableRegStr){testRegClass.enableRegStr(enableRegStr);});//发送给触发类
    connect(&cmdDo,&CmdDo::sendToServer,[&](QString sendToServerStr){socketWrite(sendToServerStr);});//发送给服务器
    connect(&cmdDo,&CmdDo::cmdShowInWindow,[&](QString cmdShowInWindowStr){ui->fightTE->appendNewText(cmdShowInWindowStr.toUtf8());});//发送给显示界面

    messageFile=new QFile("D:/gmcp.txt");
    if(messageFile->open(QIODevice::WriteOnly))
    {
        //qDebug()<<"open";
    }
    inittotalZlibNum();
    testSocket=new QTcpSocket;
    connect(testSocket,&QTcpSocket::connected,[&](){});
    connect(testSocket,&QTcpSocket::disconnected,[&](){});
    connect(testSocket,&QTcpSocket::readyRead,[&](){//粘包问题，或者丢到触发处判断
        if(!closeNumBool)
        {
            closeNum++;
            if(closeNum==10)
            {
                closeNumBool=true;
            }
        }
        //qDebug()<<"zbuffer size---"<<zbuffer.size();
        if (compressed)
        {
            //假如使用了mccp2协议，则以下需要解压
            zbuffer.append(testSocket->readAll());
            int rc;
            int total_Size=checkOutSize(zbuffer.size());
            zstrm.next_in = (Bytef*)(zbuffer.data());
            zstrm.avail_in = zbuffer.size();
            zstrm.total_in=0;
            if(total_Size>zoutSize)
            {
                zoutSize=total_Size;
                zout.resize(zoutSize);
            }
            //zout.resize(total_Size);
            zstrm.next_out = (Bytef*)(zout.data());
            zstrm.avail_out = zoutSize;
            zstrm.total_out=0;
            rc = inflate(&zstrm, Z_SYNC_FLUSH);
            //qDebug()<<"size--"<<zstrm.next_in - (Bytef*)zbuffer.data()<<" rc-"<<rc;
            zbuffer.remove(0, zstrm.next_in - (Bytef*)zbuffer.data());
            //qDebug()<<"avail_out--"<<zstrm.avail_out<<"  total_out--"<<zstrm.total_out<<"  total_in--"<<zstrm.total_in<<"  rc--"<<rc;
            testtotalZlibNum(zstrm.total_out, zstrm.total_in);
            if(rc == Z_OK)
            {
                backArray.append(zout.mid(0,zstrm.total_out));
                //                if(zstrm.total_out>5)
                //                {
                //                    QString babababa;//十六进制查看
                //                    for(int num=zstrm.total_out-5; num<zstrm.total_out; num++)
                //                    {
                //                        babababa=babababa+tr("0x%1,").arg((quint8)zout.at(num),2,16,QLatin1Char('0')).toUpper();
                //                    }
                //qDebug()<<"**----"<<babababa;
                //                }
                //                else
                //                {
                //                    QString babababa;//十六进制查看
                //                    for(int num=0; num<zstrm.total_out; num++)
                //                    {
                //                        babababa=babababa+tr("0x%1,").arg((quint8)zout.at(num),2,16,QLatin1Char('0')).toUpper();
                //                    }
                //qDebug()<<"**----"<<babababa;
                //                }
            }
        }
        else
        {
            zbuffer.append(testSocket->readAll());
            //QString testStr(zbuffer);
            //qDebug()<<lowNum<<"****"<<zbuffer;
            //qDebug()<<lowNum<<"****"<<testStr;
            //最先收到时候，若第一字节为255，则可能是服务器申请使用mccp2,需要判断。也有可能是对方中止连接，需要判断。
            if(!closeNumBool)//假如依旧过了10条信息，就没必要看IAC了
            {
                backArray=zbuffer;
                checkStr(backArray);
                zbuffer.clear();
            }
            else
            {
                int num=zbuffer.size()-1;
                //qDebug()<<"zbuffer11--"<<zbuffer;
                for(; num-1>=0; num--)
                {
                    if(zbuffer[num]=='\n' && zbuffer[num-1]=='\r')
                    {
                        break;
                    }
                    else if(zbuffer[num]=='\xF0' && zbuffer[num-1]=='\xFF')
                    {
                        break;
                    }
                    else if(zbuffer[num]=='\xF9' && zbuffer[num-1]=='\xFF')
                    {
                        break;
                    }
                    else if(zbuffer[num]=='m' && zbuffer[num-1]=='0')
                    {
                        break;
                    }
                    else if (zbuffer[num]=='\r')
                    {
                        break;
                    }
                }
                if(num!=0)
                {
                    backArray=zbuffer.mid(0,num+1);
                    //qDebug()<<"backArray--"<<backArray;
                    if(num!=zbuffer.size()-1)
                    {
                        zbuffer=zbuffer.mid(num+1);
                    }
                    else
                    {
                        zbuffer.clear();
                    }
                }
                //qDebug()<<"zbuffer22--"<<zbuffer;
                /*if(zbuffer.size()!=0)
                {
                    qDebug()<<"zbuffer--"<<QString(zbuffer);
                    //messageFile->write(zbuffer);
                    //messageFile->write("\r\n");
                }*/
            }
            //backArray.append(backArray);
        }

        //QString testStr(backArray);
        //qDebug()<<lowNum<<"****"<<backArray;
        //qDebug()<<lowNum<<"****"<<testStr;
        checkGMCP();
        ui->fightTE->appendNewText(backArray);
        testRegClass.getMessage(backArray);

        backArray.clear();



        //假如使用了mccp2协议，则以下需要解压
        /*zbuffer.append(testSocket->readAll());
//qDebug()<<"zbuffer size---"<<zbuffer.size();
        if (compressed)
        {
            int rc;
            int total_Size=checkOutSize(zbuffer.size());
            zstrm.next_in = (Bytef*)(zbuffer.data());
            zstrm.avail_in = zbuffer.size();
            zstrm.total_in=0;
            if(total_Size>zoutSize)
            {
                zoutSize=total_Size;
                zout.resize(zoutSize);
            }
            //zout.resize(total_Size);
            zstrm.next_out = (Bytef*)(zout.data());
            zstrm.avail_out = zoutSize;
            zstrm.total_out=0;
            rc = inflate(&zstrm, Z_SYNC_FLUSH);
//qDebug()<<"size--"<<zstrm.next_in - (Bytef*)zbuffer.data()<<" rc-"<<rc;
            zbuffer.remove(0, zstrm.next_in - (Bytef*)zbuffer.data());
//qDebug()<<"avail_out--"<<zstrm.avail_out<<"  total_out--"<<zstrm.total_out<<"  total_in--"<<zstrm.total_in<<"  rc--"<<rc;
            testtotalZlibNum(zstrm.total_out, zstrm.total_in);
            if(rc == Z_OK)
            {
                backArray.append(zout.mid(0,zstrm.total_out));
//                if(zstrm.total_out>5)
//                {
//                    QString babababa;//十六进制查看
//                    for(int num=zstrm.total_out-5; num<zstrm.total_out; num++)
//                    {
//                        babababa=babababa+tr("0x%1,").arg((quint8)zout.at(num),2,16,QLatin1Char('0')).toUpper();
//                    }
////qDebug()<<"**----"<<babababa;
//                }
//                else
//                {
//                    QString babababa;//十六进制查看
//                    for(int num=0; num<zstrm.total_out; num++)
//                    {
//                        babababa=babababa+tr("0x%1,").arg((quint8)zout.at(num),2,16,QLatin1Char('0')).toUpper();
//                    }
////qDebug()<<"**----"<<babababa;
//                }
            }
        }
        else
        {
            //最先收到时候，若第一字节为255，则可能是服务器申请使用mccp2,需要判断。也有可能是对方中止连接，需要判断。
            checkStr(zbuffer);
            backArray.append(zbuffer);
            zbuffer.clear();
        }

        //QString testStr(backArray);
        //lowNum++;
//qDebug()<<lowNum<<"****"<<backArray;
//qDebug()<<lowNum<<"****"<<testStr;
        checkGMCP();
        ui->fightTE->appendNewText(backArray);
        testRegClass.getMessage(backArray);

        backArray.clear();*/
    });
    testSocket->connectToHost("47.97.249.185",8081);

    /*QString testStr="#4.89M,3463,5260,5260,5260,5260\r\n#2517,2517,2517,1794,1794,1764\r\n#0,101,0,-1,0,0";
    QRegularExpression regular("#([A-Za-z0-9.-]+)(?:,([A-Za-z0-9.-]+))*\\r\\n#([A-Za-z0-9.-]+)(?:,([A-Za-z0-9.-]+))*\\r\\n#([A-Za-z0-9.-]+)(?:,([A-Za-z0-9.-]+))*");
    int index=0;
    QRegularExpressionMatch regularmatch=regular.match(testStr, index);
    if(regularmatch.hasMatch())
    {
        index=regularmatch.capturedEnd();
//qDebug()<<"("<<regularmatch.capturedStart()<<","<<index<<")"<<regularmatch.captured(0);
        QString checkStr=regularmatch.captured(0);
    }
    else
    {
//qDebug()<<"error";
    }*/
    /*QFontDatabase database;
    foreach(const QString &family, database.families(QFontDatabase::SimplifiedChinese))
    {
//qDebug() << family;
    }*/
    /*QJsonObject sendObj;
    sendObj.insert("Class","哈哈哈");
    sendObj.insert("Name","草泥马");
    sendObj.insert("RegStr","#([A-Za-z0-9.-]+)(?:,([A-Za-z0-9.-]+))*\\r\\n#([A-Za-z0-9.-]+)(?:,([A-Za-z0-9.-]+))*\\r\\n#([A-Za-z0-9.-]+)(?:,([A-Za-z0-9.-]+))*");
    sendObj.insert("ArraySize",3);
    QJsonArray strListArray;
    strListArray.append("111");
    strListArray.append("222");
    strListArray.append("333");
    sendObj.insert("RegStrList",strListArray);
    QJsonDocument backdocu(sendObj);
//qDebug()<<"backdocu Compact size--"<<backdocu.toJson(QJsonDocument::Compact).size();
//qDebug()<<"backdocu Indented size--"<<backdocu.toJson(QJsonDocument::Indented).size();*/



    /*str== "\u001B[36m冲虚道长\u001B[2;37;0m\u001B[36m说道：「已经帮你取消了诵经任务。\u001B[2;37;0m\u001B[36m」\r\n"
    inArray== "\x1B[36m\xE5\x86\xB2\xE8\x99\x9A\xE9\x81\x93\xE9\x95\xBF\x1B[2;37;0m\x1B[36m\xE8\xAF\xB4\xE9\x81\x93\xEF\xBC\x9A\xE3\x80\x8C\xE5\xB7\xB2\xE7\xBB\x8F\xE5\xB8\xAE\xE4\xBD\xA0\xE5\x8F\x96\xE6\xB6\x88\xE4\xBA\x86\xE8\xAF\xB5\xE7\xBB\x8F\xE4\xBB\xBB\xE5\x8A\xA1\xE3\x80\x82\x1B[2;37;0m\x1B[36m\xE3\x80\x8D\r\n"
    QByteArray inArray;
    inArray.append('\xE5');
    inArray.append('\x86');
    inArray.append('\xB2');
    inArray.append('\xE8');
    inArray.append('\x99');
    inArray.append('\x9A');
    inArray.append('\xE9');
    inArray.append('\x81');
    inArray.append('\x93');
    inArray.append('\xE9');
    inArray.append('\x95');
    inArray.append('\xBF');
    inArray.append('\x1B');
    inArray.append('[');
    inArray.append('3');
    inArray.append('6');
    inArray.append('m');
    inArray.append('\xE8');
    inArray.append('\xAF');
    inArray.append('\xB4');
    inArray.append('\xE9');
    inArray.append('\x81');
    inArray.append('\x93');
    inArray.append('\xEF');
    inArray.append('\xBC');
    inArray.append('\x9A');
    inArray.append('\xE3');
    inArray.append('\x80');
    inArray.append('\x8C');


//qDebug()<<"str=="<<QString(inArray);
//qDebug()<<"inArray=="<<inArray;
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
            }
        }
        Num++;
    }
//qDebug()<<"str=="<<QString(inArray);
//qDebug()<<"inArray=="<<inArray;*/

    /*backArray.append('\xFF');
    backArray.append('\xFF');
    backArray.append('\xFA');
    backArray.append('\xC9');
    backArray.append('G');
    backArray.append('M');
    backArray.append('C');
    backArray.append('P');
    backArray.append('.');
    backArray.append('B');
    backArray.append('u');
    backArray.append('f');
    backArray.append('f');
    backArray.append('\xFF');
    backArray.append('\xF0');
    backArray.append('\xFF');
    backArray.append('\xFA');
    backArray.append('\xC9');
    backArray.append('G');
    backArray.append('M');
    backArray.append('C');
    backArray.append('P');
    backArray.append('.');
    backArray.append('S');
    backArray.append('\xFF');
    backArray.append('\xF0');
    backArray.append('\xFF');
    checkGMCP();
    ui->fightTE->appendNewText(backArray);*/
}

MainWindow::~MainWindow()
{
    messageFile->close();
    showtotalZlibNum();
    delete ui;
}

void MainWindow::socketWrite(QString writeStr)
{
    writeStr=writeStr+"\n\r";
    //char pasdf[1024];
    //int sizeofstring=0;
    //假如使用了mccp2，则需要先压缩
    /*if(mccp2Enabel)
    {
        QByteArray ba2;
        ba2.append(writeStr);
        char* buf=ba2.data();
        std::cout << "========= CompressString ===========" << std::endl;
        std::cout << "Source Buffer Size: " << strlen(buf) << std::endl;
        std::string out_compress;
        assert(CompressString(buf,strlen(buf),out_compress,Z_DEFAULT_COMPRESSION) == Z_OK);
        std::cout << "Compress Buffer Size: " << out_compress.size() << std::endl;

        sizeofstring=out_compress.size();
        out_compress.copy(pasdf, sizeofstring, 0);
    }

    if(testSocket!=nullptr)
    {
        testSocket->write(&pasdf[0],sizeofstring);
//qDebug()<<"MainWindow::socketWrite";
    }*/
    if(testSocket!=nullptr)
    {
        testSocket->write(writeStr.toStdString().data());
        //testSocket->write(writeStr.toUtf8());
        testSocket->flush();
        //qDebug()<<"MainWindow::socketWrite--"<<writeStr;
    }
}

void MainWindow::checkStr(QByteArray testArray)
{
    //qDebug()<<"MainWindow::checkStr begin";
    bool backWrite=false;//需要写回服务器
    QByteArray backArray;//返回给服务器的mccp2请求
    //qDebug()<<"MainWindow::checkStr testArray.size()--"<<testArray.size();
    //qDebug()<<"MainWindow::checkStr checkStr--"<<testArray.toHex();
    for(int num=0; num<testArray.size(); num=num+3)
    {
        char firstChar=testArray[num];
        if(num<testArray.size() && uchar(firstChar)==Common::IAC)
        {
            if(num+2 < testArray.size())
            {
                char secondChar=testArray[num+1];
                char endChar=testArray[num+2];
                if(uchar(endChar)==Common::MCCP2)//mccp2
                {
                    if(uchar(secondChar)==Common::WILL)//WILL  :IAC WILL MCCP2
                    {
                        //qDebug()<<"MainWindow::checkStr IAC WILL MCCP2";
                        backArray.append(Common::IAC);
                        backArray.append(Common::DO);
                        backArray.append(Common::IAC);
                        backWrite=true;
                    }
                    else if(uchar(secondChar)==Common::SB)//se    :IAC SB MCCP2 IAC SE
                    {
                        //qDebug()<<"MainWindow::checkStr IAC SB MCCP2 IAC SE";
                        zstrm.next_in = Z_NULL;
                        zstrm.avail_in = 0;
                        zstrm.zalloc = Z_NULL;
                        zstrm.zfree = Z_NULL;
                        zstrm.opaque = 0;
                        inflateInit(&zstrm);
                        compressed = true;
                    }
                    else if(uchar(secondChar)==Common::DONT)//DONT   :IAC DONT MCCP2
                    {
                        //qDebug()<<"MainWindow::checkStr Common::DONT";
                        compressed = false;
                    }
                }
                else if(uchar(endChar)==Common::GMCP)//GMCP
                {
                    if(uchar(secondChar)==Common::WILL)//WILL  :IAC DO GMCP
                    {
                        //qDebug()<<"MainWindow::checkStr IAC DO GMCP";
                        backArray.append(Common::IAC);
                        backArray.append(Common::DO);
                        backArray.append(Common::GMCP);
                        backWrite=true;
                    }
                    else if(uchar(secondChar)==Common::SB)//se    :IAC SB GMCP IAC SE
                    {
                        //qDebug()<<"MainWindow::checkStr Common::SB";
                    }
                    else if(uchar(secondChar)==Common::DONT)//DONT   :IAC DONT GMCP
                    {
                        //qDebug()<<"MainWindow::checkStr Common::DONT";
                        compressed = false;
                    }
                }
                /*else if(uchar(endChar)==Common::TYPE)//TYPE
                {
                    if(uchar(secondChar)==Common::WILL)//WILL  :IAC WILL TYPE
                    {
//qDebug()<<"MainWindow::checkStr IAC WILL TYPE";
                        backArray.append(Common::IAC);
                        backArray.append(Common::DO);
                        backArray.append(Common::TYPE);
                        backWrite=true;
                    }
                    else if(uchar(secondChar)==Common::SB)//se    :IAC，SB，TYPE，SEND，IAC，SE
                    {
//qDebug()<<"MainWindow::checkStr IAC，SB，TYPE，SEND，IAC，SE";
                        backArray.append(Common::IAC);
                        backArray.append(Common::SB);
                        backArray.append(Common::TYPE);
                        backArray.append(Common::IS);
                        backArray.append('Q');
                        backArray.append('T');
                        backArray.append('M');
                        backArray.append('U');
                        backArray.append('D');
                        backArray.append(Common::IAC);
                        backArray.append(Common::SE);
                        backWrite=true;
                    }
                    else if(uchar(secondChar)==Common::DO)//DONT   :IAC DO MCCP2
                    {
                        ////qDebug()<<"MainWindow::checkStr IAC，SB，TYPE，SEND，IAC，SE";
                        //                        backArray.append(Common::IAC);
                        //                        backArray.append(Common::SB);
                        //                        backArray.append(Common::TYPE);
                        //                        backArray.append(Common::IS);
                        //                        backArray.append('Q');
                        //                        backArray.append('t');
                        //                        backArray.append('M');
                        //                        backArray.append('u');
                        //                        backArray.append('d');
                        //                        backArray.append(Common::IAC);
                        //                        backArray.append(Common::SE);
                        //                        backWrite=true;
                        backArray.append(Common::IAC);
                        backArray.append(Common::WILL);
                        backArray.append(Common::TYPE);
                        backWrite=true;
                    }
                }*/
                else
                {
                    if(uchar(secondChar)==Common::DO)//do
                    {
                        backArray.append(Common::IAC);//WONT
                        backArray.append(Common::WONT);
                        backArray.append(uchar(endChar));
                        backWrite=true;
                    }
                    else if(uchar(secondChar)==Common::WILL)//WILL
                    {
                        backArray.append(Common::IAC);//dont
                        backArray.append(Common::DONT);
                        backArray.append(uchar(endChar));
                        backWrite=true;
                    }
                }
            }
        }
        else
        {
            break;
        }
    }
    if(backWrite)
    {
        //qDebug()<<"MainWindow::checkStr  back--"<<backArray.toHex();
        testSocket->write(backArray.data());
    }
}

int MainWindow::checkOutSize(int inSize)
{
    int backSize=0;
    if(inSize<=50)
    {
        backSize=inSize*40;
    }
    else if(inSize<=100)
    {
        backSize=inSize*30;
    }
    else if(inSize<=200)
    {
        backSize=inSize*20;
    }
    else if(inSize<=500)
    {
        backSize=inSize*15;
    }
    else
    {
        backSize=inSize*10;
    }
    return backSize;
}

void MainWindow::on_cmdLE_returnPressed()
{
    //qDebug()<<ui->cmdLE->text();
    //socketWrite(ui->cmdLE->text());//暂时通过传送至命令中转来达到执行系统命令效果
    cmdControl.appendMessage(ui->cmdLE->text());
    ui->cmdLE->selectAll();
}

void MainWindow::on_toolButton_clicked()
{
    ui->fightTE->setClickScrollBar();
}

void MainWindow::on_actionTCP_triggered()
{
    tcpServerForm.show();
}

//创建系统托盘
void MainWindow::initSysTrayIcon()
{
    //隐藏程序主窗口
    this->hide();

    //新建QSystemTrayIcon对象
    m_sysTrayIcon = new QSystemTrayIcon(this);

    //设置托盘图标
    QIcon icon = QIcon(":/icon/testIcon.png");    //资源文件添加的图标
    m_sysTrayIcon->setIcon(icon);

    //当鼠标移动到托盘上的图标时，会显示此处设置的内容
    m_sysTrayIcon->setToolTip("托盘提示信息");

    //给QSystemTrayIcon添加槽函数
    connect(m_sysTrayIcon, &QSystemTrayIcon::activated,
            [=](QSystemTrayIcon::ActivationReason reason)
    {
        switch(reason)
        {
        case QSystemTrayIcon::Trigger:
            //单击托盘图标
            /*m_sysTrayIcon->showMessage(QObject::trUtf8("Message Title"),
                                              QObject::trUtf8("欢迎使用此程序"),
                                              QSystemTrayIcon::Information,
                                              1000);*/
            break;
        case QSystemTrayIcon::DoubleClick:
            //双击托盘图标
            //双击后显示主程序窗口
            this->show();
            break;
        default:
            break;
        }
    });

    //建立托盘操作的菜单
    createActions();
    createMenu();
    //在系统托盘显示此对象
    m_sysTrayIcon->show();
}

void MainWindow::checkGMCP()
{
    bool backflag=true;
    QList<GMCPType> GMCPTypeList;
    QByteArrayList GMCPArrayList;
    while(backflag)
    {
        GMCPType GMCPType=GMCPType::none;
        QByteArray GMCPArray;
        backflag=slipeBackArray(GMCPType, GMCPArray);
        if(backflag)
        {
            GMCPTypeList.push_back(GMCPType);
            GMCPArrayList.push_back(GMCPArray);
        }
    }
    if(GMCPTypeList.size()>0)
    {
        for(int begin=0; begin<GMCPTypeList.size(); begin++)
        {
            GMCPType aa=GMCPTypeList.at(begin);
            QByteArray bb=GMCPArrayList.at(begin);
            switch (aa) {
            case GMCPType::buff:
            {
                if(true/*发送到端口*/)
                {
                    //须填
                }
                if(showGmcpAllBool && buffBool/*显示*/)
                {
                    if(true/*颜色*/)
                    {
                        QByteArray colorByte;
                        colorByte.append('\x1b');
                        colorByte.append('[');
                        colorByte.append('1');
                        colorByte.append(';');
                        colorByte.append('3');
                        colorByte.append('1');
                        colorByte.append('m');

                        QByteArray endcolorByte;
                        endcolorByte.append('\x1b');
                        endcolorByte.append('[');
                        endcolorByte.append('2');
                        endcolorByte.append(';');
                        endcolorByte.append('3');
                        endcolorByte.append('7');
                        endcolorByte.append(';');
                        endcolorByte.append('0');
                        endcolorByte.append('m');

                        bb=colorByte+bb+endcolorByte;
                    }
                    if(true/*换行*/)
                    {
                        bb=bb+'\r'+'\n';
                    }
                    backArray=bb+backArray;
                }
            }
                break;
            case GMCPType::move:
            {
                if(true/*发送到端口*/)
                {
                    //须填
                }
                if(showGmcpAllBool && moveBool/*显示*/)
                {
                    if(true/*颜色*/)
                    {
                        QByteArray colorByte;
                        colorByte.append('\x1b');
                        colorByte.append('[');
                        colorByte.append('1');
                        colorByte.append(';');
                        colorByte.append('3');
                        colorByte.append('2');
                        colorByte.append('m');

                        QByteArray endcolorByte;
                        endcolorByte.append('\x1b');
                        endcolorByte.append('[');
                        endcolorByte.append('2');
                        endcolorByte.append(';');
                        endcolorByte.append('3');
                        endcolorByte.append('7');
                        endcolorByte.append(';');
                        endcolorByte.append('0');
                        endcolorByte.append('m');

                        bb=colorByte+bb+endcolorByte;
                    }
                    if(true/*换行*/)
                    {
                        bb=bb+'\r'+'\n';
                    }
                    backArray=bb+backArray;
                }
            }
                break;
            case GMCPType::combat:
            {
                if(true/*发送到端口*/)
                {
                    //须填
                }
                if(showGmcpAllBool && combatBool/*显示*/)
                {
                    if(true/*颜色*/)
                    {
                        QByteArray colorByte;
                        colorByte.append('\x1b');
                        colorByte.append('[');
                        colorByte.append('1');
                        colorByte.append(';');
                        colorByte.append('3');
                        colorByte.append('5');
                        colorByte.append('m');

                        QByteArray endcolorByte;
                        endcolorByte.append('\x1b');
                        endcolorByte.append('[');
                        endcolorByte.append('2');
                        endcolorByte.append(';');
                        endcolorByte.append('3');
                        endcolorByte.append('7');
                        endcolorByte.append(';');
                        endcolorByte.append('0');
                        endcolorByte.append('m');

                        bb=colorByte+bb+endcolorByte;
                    }
                    if(true/*换行*/)
                    {
                        bb=bb+'\r'+'\n';
                    }
                    backArray=bb+backArray;
                }
            }
                break;
            case GMCPType::status:
            {
                if(true/*发送到端口*/)
                {
                    //须填
                }
                if(showGmcpAllBool && statusBool/*显示*/)
                {
                    if(true/*颜色*/)
                    {
                        QByteArray colorByte;
                        colorByte.append('\x1b');
                        colorByte.append('[');
                        colorByte.append('1');
                        colorByte.append(';');
                        colorByte.append('3');
                        colorByte.append('6');
                        colorByte.append('m');

                        QByteArray endcolorByte;
                        endcolorByte.append('\x1b');
                        endcolorByte.append('[');
                        endcolorByte.append('2');
                        endcolorByte.append(';');
                        endcolorByte.append('3');
                        endcolorByte.append('7');
                        endcolorByte.append(';');
                        endcolorByte.append('0');
                        endcolorByte.append('m');

                        bb=colorByte+bb+endcolorByte;
                    }
                    if(true/*换行*/)
                    {
                        bb=bb+'\r'+'\n';
                    }
                    backArray=bb+backArray;
                }
            }
                break;
            case GMCPType::message:
            {
                if(true/*发送到端口*/)
                {
                    //须填
                }
                if(showGmcpAllBool && messageBool/*显示*/)
                {
                    if(true/*颜色*/)
                    {
                        QByteArray colorByte;
                        colorByte.append('\x1b');
                        colorByte.append('[');
                        colorByte.append('1');
                        colorByte.append(';');
                        colorByte.append('3');
                        colorByte.append('7');
                        colorByte.append('m');

                        QByteArray endcolorByte;
                        endcolorByte.append('\x1b');
                        endcolorByte.append('[');
                        endcolorByte.append('2');
                        endcolorByte.append(';');
                        endcolorByte.append('3');
                        endcolorByte.append('7');
                        endcolorByte.append(';');
                        endcolorByte.append('0');
                        endcolorByte.append('m');

                        bb=colorByte+bb+endcolorByte;
                    }
                    if(true/*换行*/)
                    {
                        bb=bb+'\r'+'\n';
                    }
                    backArray=bb+backArray;
                }
            }
                break;
            default:
                break;
            }
        }
        /*int a=backArray.size();
        if(!(a>=2 && backArray[a-2]=='\r' && backArray[a-1]=='\n'))
        {
            backArray=backArray+'\r'+'\n';
        }*/
    }
}

bool MainWindow::slipeBackArray(GMCPType &GMCPType, QByteArray &GMCPArray)
{
    bool findFlag=false;
    int beginInt=0;//gcmp的起点,从0开始
    int endInt=0;//gcmp的终点,从0开始
    //qDebug()<<"messageFile->all   --"<<backArray;
    for(int begin=0; begin<backArray.size()-10; )
    {
        if(backArray[begin]=='\xFF')
        {
            if(backArray[begin+1]=='\xFA')
            {
                if(backArray[begin+2]=='\xC9')
                {
                    if(backArray[begin+3]=='G')
                    {
                        if(backArray[begin+4]=='M')
                        {
                            if(backArray[begin+5]=='C')
                            {
                                if(backArray[begin+6]=='P')
                                {
                                    if(backArray[begin+7]=='.')
                                    {
                                        beginInt=begin;
                                        for(int endint=begin+8; endint<backArray.size()-1; endint++)
                                        {
                                            if(backArray[endint]=='\xFF')
                                            {
                                                if(backArray[endint+1]=='\xF0')
                                                {
                                                    endInt=endint+1;
                                                    if(backArray[begin+8]=='S')
                                                    {
                                                        GMCPType=GMCPType::status;
                                                        findFlag=true;
                                                        if(beginInt==0)
                                                        {
                                                            GMCPArray=backArray.mid(0,endInt-beginInt+1);
                                                            backArray=backArray.mid(endInt+1);
                                                        }
                                                        else
                                                        {
                                                            QByteArray beginArray;
                                                            beginArray=backArray.mid(0,beginInt);
                                                            GMCPArray=backArray.mid(beginInt,endInt-beginInt+1);
                                                            backArray=backArray.mid(endInt+1);
                                                            backArray=beginArray+backArray;
                                                        }
                                                        ui->fightTE->setStatus(GMCPArray, GMCPType);
                                                    }
                                                    else if(backArray[begin+8]=='M' && backArray[begin+9]=='o')
                                                    {
                                                        GMCPType=GMCPType::move;
                                                        findFlag=true;
                                                        if(beginInt==0)
                                                        {
                                                            GMCPArray=backArray.mid(0,endInt-beginInt+1);
                                                            backArray=backArray.mid(endInt+1);
                                                        }
                                                        else
                                                        {
                                                            QByteArray beginArray;
                                                            beginArray=backArray.mid(0,beginInt);
                                                            GMCPArray=backArray.mid(beginInt,endInt-beginInt+1);
                                                            backArray=backArray.mid(endInt+1);
                                                            backArray=beginArray+backArray;
                                                        }
                                                    }
                                                    else if(backArray[begin+8]=='M' && backArray[begin+9]=='e')
                                                    {
                                                        GMCPType=GMCPType::message;
                                                        findFlag=true;
                                                        if(beginInt==0)
                                                        {
                                                            GMCPArray=backArray.mid(0,endInt-beginInt+1);
                                                            backArray=backArray.mid(endInt+1);
                                                        }
                                                        else
                                                        {
                                                            QByteArray beginArray;
                                                            beginArray=backArray.mid(0,beginInt);
                                                            GMCPArray=backArray.mid(beginInt,endInt-beginInt+1);
                                                            backArray=backArray.mid(endInt+1);
                                                            backArray=beginArray+backArray;
                                                        }
                                                    }
                                                    else if(backArray[begin+8]=='C')
                                                    {
                                                        GMCPType=GMCPType::combat;
                                                        findFlag=true;
                                                        if(beginInt==0)
                                                        {
                                                            GMCPArray=backArray.mid(0,endInt-beginInt+1);
                                                            backArray=backArray.mid(endInt+1);
                                                        }
                                                        else
                                                        {
                                                            QByteArray beginArray;
                                                            beginArray=backArray.mid(0,beginInt);
                                                            GMCPArray=backArray.mid(beginInt,endInt-beginInt+1);
                                                            backArray=backArray.mid(endInt+1);
                                                            backArray=beginArray+backArray;
                                                        }
                                                    }
                                                    else if(backArray[begin+8]=='B')
                                                    {
                                                        GMCPType=GMCPType::buff;
                                                        findFlag=true;
                                                        if(beginInt==0)
                                                        {
                                                            GMCPArray=backArray.mid(0,endInt-beginInt+1);
                                                            backArray=backArray.mid(endInt+1);
                                                        }
                                                        else
                                                        {
                                                            QByteArray beginArray;
                                                            beginArray=backArray.mid(0,beginInt);
                                                            GMCPArray=backArray.mid(beginInt,endInt-beginInt+1);
                                                            backArray=backArray.mid(endInt+1);
                                                            backArray=beginArray+backArray;
                                                        }
                                                        ui->fightTE->setStatus(GMCPArray, GMCPType);
                                                    }
                                                    //qDebug()<<"messageFile->write  --"<<GMCPArray;
                                                    messageFile->write(GMCPArray);
                                                    break;
                                                }
                                            }
                                        }
                                        begin=begin+8;
                                    }
                                    else
                                    {
                                        begin=begin+7;
                                    }
                                }
                                else
                                {
                                    begin=begin+6;
                                }
                            }
                            else
                            {
                                begin=begin+5;
                            }
                        }
                        else
                        {
                            begin=begin+4;
                        }
                    }
                    else
                    {
                        begin=begin+3;
                    }
                }
                else
                {
                    begin=begin+2;
                }
            }
            else
            {
                begin=begin+1;
            }
        }
        else
        {
            begin=begin+1;
        }
    }
    //qDebug()<<"messageFile->write  backArray--"<<backArray;
    return findFlag;
}

//创建动作
void MainWindow::createActions()
{
    m_showMainAction = new QAction("显示窗口", this);
    connect(m_showMainAction,SIGNAL(triggered()),this,SLOT(on_showMainAction()));
    m_exitAppAction = new QAction("退出", this);
    connect(m_exitAppAction,SIGNAL(triggered()),this,SLOT(on_exitAppAction()));
}

//创建托盘菜单
void MainWindow::createMenu()
{
    m_menu = new QMenu(this);
    //新增菜单项---显示主界面
    m_menu->addAction(m_showMainAction);
    //增加分隔符
    m_menu->addSeparator();
    //新增菜单项---退出程序
    m_menu->addAction(m_exitAppAction);
    //把QMenu赋给QSystemTrayIcon对象
    m_sysTrayIcon->setContextMenu(m_menu);
}

//当在系统托盘点击菜单内的显示主界面操作
void MainWindow::on_showMainAction()
{
    QApplication::setQuitOnLastWindowClosed( false );
    //QMessageBox::information(nullptr, "xxxx", "xxxx有限公司copyright©2022");
    this->show();
}

//当在系统托盘点击菜单内的退出程序操作
void MainWindow::on_exitAppAction()
{
    qApp->exit();
}

//关闭事件
void MainWindow::closeEvent(QCloseEvent *event)
{
    //忽略窗口关闭事件
    QApplication::setQuitOnLastWindowClosed( true );
    this->hide();
    event->ignore();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_QuoteLeft))
    {
        //qDebug()<<"MainWindow::keyPressEvent";
        this->hide();
    }
    QMainWindow::keyPressEvent(event);
}

void MainWindow::on_actionRegShow_triggered()
{
    regForm.setRegMapPtr(&testRegClass.regMap);
    regForm.show();
}

void MainWindow::on_actionRegIn_triggered()
{
    QFileDialog fileD;
    QStringList filters;
    fileD.setDirectory("./");
    filters << "dat files(*.json)";
    fileD.setNameFilters(filters);//过滤文件
    if(fileD.exec() == QFileDialog::Accepted){
        QString filePa = fileD.selectedFiles().first();
        //qDebug() << "filePa:" << filePa;
        QFile file(filePa);
        //qDebug()<<"??????";
        if(file.open(QIODevice::ReadOnly))
        {
            QJsonParseError json_error;
            QJsonDocument inFile = QJsonDocument::fromJson(file.readAll(), &json_error);
            QJsonObject allJson=inFile.object();
            int allNum=allJson.count();
            //qDebug()<<"begin--"<<allNum;
            int Num=0;
            while (Num<allNum) {
                QJsonObject oneRegJson=allJson.value(QString::number(Num)).toObject();
                RegStr oneReg;
                oneReg.parent=oneRegJson.value("parent").toString();
                oneReg.regName=oneRegJson.value("regName").toString();
                oneReg.regStr=oneRegJson.value("regStr").toString();
                oneReg.row=oneRegJson.value("row").toInt();
                oneReg.oneStrOneReg=oneRegJson.value("oneStrOneReg").toBool();
                oneReg.enable=oneRegJson.value("enable").toBool();
                oneReg.sysOrUser=oneRegJson.value("sysOrUser").toBool();
                oneReg.port=oneRegJson.value("port").toInt();
                oneReg.sysStr=oneRegJson.value("sysStr").toString();
                oneReg.serverText=oneRegJson.value("serverText").toBool();
                testRegClass.newReg(oneReg);
                Num++;
            }
        }
        else
        {
            //qDebug()<<"error--"<<file.errorString();
        }
        file.close();
    }
}

void MainWindow::on_actionRegOut_triggered()
{
    QFileDialog fileD;
    QStringList filters;
    filters << "dat files(*.json)";
    fileD.setNameFilters(filters);//过滤文件
    if(fileD.exec() == QFileDialog::Accepted){
        QString filePa = fileD.selectedFiles().first();
        //qDebug() << "filePa:" << filePa;
        QFile file(filePa);
        if(file.open(QIODevice::WriteOnly))
        {
            //qDebug()<<"begin--";
            int Num=0;
            QJsonObject backobj;
            QMap<QString, QMap<QString, RegPtr*>*>::Iterator firstMapIter=testRegClass.regMap.begin();
            while (firstMapIter!=testRegClass.regMap.end()) {
                //qDebug()<<"firstMapIter.key()--"<<firstMapIter.key();
                QMap<QString, RegPtr*>::Iterator secondMapIter=firstMapIter.value()->begin();
                while (secondMapIter!=firstMapIter.value()->end()) {
                    //qDebug()<<"secondMapIter.key()--"<<secondMapIter.key();
                    QJsonObject oneReg;
                    oneReg.insert("parent",secondMapIter.value()->oneReg.parent);
                    oneReg.insert("regName",secondMapIter.value()->oneReg.regName);
                    oneReg.insert("regStr",secondMapIter.value()->oneReg.regStr);
                    oneReg.insert("row",secondMapIter.value()->oneReg.row);
                    oneReg.insert("oneStrOneReg",secondMapIter.value()->oneReg.oneStrOneReg);
                    oneReg.insert("enable",secondMapIter.value()->oneReg.enable);
                    oneReg.insert("sysOrUser",secondMapIter.value()->oneReg.sysOrUser);
                    oneReg.insert("port",secondMapIter.value()->oneReg.port);
                    oneReg.insert("sysStr",secondMapIter.value()->oneReg.sysStr);
                    oneReg.insert("serverText",secondMapIter.value()->oneReg.serverText);
                    backobj.insert(QString::number(Num),oneReg);
                    secondMapIter++;
                    Num++;
                }
                firstMapIter++;
            }
            QJsonDocument inFile(backobj);
            //qDebug()<<"--"<<inFile;
            file.write(inFile.toJson());
        }
        else
        {
            //qDebug()<<"error--"<<file.errorString();
        }
        file.close();
    }
}


void MainWindow::on_actionYuanWen_triggered(bool checked)
{
    ui->fightTE->setShowText(checked);
}


void MainWindow::on_actiongmcp_triggered()
{
    configForm.show();
}

