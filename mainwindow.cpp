#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <QRegExp>
#include <iostream>
#include <QRegularExpression>
#include <QFontDatabase>

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
        qDebug()<<"key="<<beginite.key()<<"  showNum--"<<beginite.value()->showNum<<"  maxSize--"<<beginite.value()->maxSize<<"  minSize--"<<beginite.value()->minSize;
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
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    zout.resize(zoutSize);


    messageFile=new QFile("D:/sdfgsdfg.txt");
    if(messageFile->open(QIODevice::WriteOnly))
    {
        qDebug()<<"open";
    }
    inittotalZlibNum();
    testSocket=new QTcpSocket;
    connect(testSocket,&QTcpSocket::connected,[&](){});
    connect(testSocket,&QTcpSocket::disconnected,[&](){});
    connect(testSocket,&QTcpSocket::readyRead,[&](){
        /*{
            zbuffer.append(testSocket->readAll());
            if (compressed) {
                    int rc;
                    do {
                        zstrm.next_in = (Bytef*)(zbuffer.data());
                        zstrm.avail_in = zbuffer.size();
                        zout.resize(zstrm.total_out + 2000);
                        zstrm.next_out = (Bytef*)(zout.data() + zstrm.total_out);
                        zstrm.avail_out = 2000;
                        rc = inflate(&zstrm, Z_SYNC_FLUSH);
                        qDebug()<<"size--"<<zstrm.next_in - (Bytef*)zbuffer.data()<<" rc-"<<rc;
                        zbuffer.remove(0, zstrm.next_in - (Bytef*)zbuffer.data());
                    } while (rc == Z_OK && zstrm.avail_out == 0);
                    if (rc == Z_OK) {
                        zout.truncate(zstrm.total_out);
                        buffer.append(zout);
                        zout.clear();
                        buffer.append(zbuffer);
                        zbuffer.clear();
                        inflateEnd(&zstrm);
                        qDebug()<<"str---"<<QString(buffer);
                        buffer.clear();
                    }
                    else if (rc != Z_OK) {
                        // ERROR!  look at zstrm.msg
                        qDebug()<<"rc != Z_OK---"<<rc;
                    }
                }
            else
            {
                checkStr(zbuffer);
                zbuffer.clear();
                return ;
            }
        }*/
        //假如使用了mccp2协议，则以下需要解压
        zbuffer.append(testSocket->readAll());
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
                /*if(zstrm.total_out>5)
                {
                    QString babababa;//十六进制查看
                    for(int num=zstrm.total_out-5; num<zstrm.total_out; num++)
                    {
                        babababa=babababa+tr("0x%1,").arg((quint8)zout.at(num),2,16,QLatin1Char('0')).toUpper();
                    }
                    qDebug()<<"**----"<<babababa;
                }
                else
                {
                    QString babababa;//十六进制查看
                    for(int num=0; num<zstrm.total_out; num++)
                    {
                        babababa=babababa+tr("0x%1,").arg((quint8)zout.at(num),2,16,QLatin1Char('0')).toUpper();
                    }
                    qDebug()<<"**----"<<babababa;
                }*/
            }
        }
        else
        {
            //最先收到时候，若第一字节为255，则可能是服务器申请使用mccp2,需要判断。也有可能是对方中止连接，需要判断。
            checkStr(zbuffer);
            backArray.append(zbuffer);
            zbuffer.clear();
        }

        /*{
            QRegularExpression regular("\\033\\[\\d+(;\\d+)*m");
            QRegularExpression regular1("4\\d+");
            int index=0;
            do{
                QRegularExpressionMatch regularmatch=regular.match(testStr, index);
                if(regularmatch.hasMatch())
                {
                    index=regularmatch.capturedEnd();
                    //qDebug()<<"("<<regularmatch.capturedStart()<<","<<index<<")"<<regularmatch.captured(0);
                    QString checkStr=regularmatch.captured(0);
                    QRegularExpressionMatch regularmatch1=regular1.match(checkStr);
                    if(regularmatch1.hasMatch())
                    {
                        //qDebug()<<regularmatch1.captured(0);
                        messageFile->write(regularmatch1.captured(0).toUtf8());
                        break;
                    }
                }
                else
                {
                    break;
                }
            }while (index < testStr.length());
        }*/
        messageFile->write(backArray);

        QString testStr(backArray);
        qDebug()<<lowNum++<<"****"<<testStr;
        ui->fightTE->appendNewText(backArray);

        backArray.clear();
    });
    testSocket->connectToHost("47.97.249.185",8081);
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
        qDebug()<<"MainWindow::socketWrite";
    }*/
    if(testSocket!=nullptr)
    {
        testSocket->write(writeStr.toStdString().data());
        //qDebug()<<"MainWindow::socketWrite";
    }
}

void MainWindow::checkStr(QByteArray testArray)
{
    //qDebug()<<"MainWindow::checkStr begin";
    bool backWrite=false;//需要写回服务器
    QByteArray backArray;//返回给服务器的mccp2请求
    //qDebug()<<"MainWindow::checkStr checkStr--"<<testArray;
    for(int num=0; num<testArray.size(); num=num+3)
    {
        char firstChar=testArray[0];
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
                        backArray.append(Common::IAC);//DO  :IAC DO MCCP2
                        backArray.append(Common::DO);
                        backArray.append(Common::MCCP2);
                        backWrite=true;
                    }
                    else if(uchar(secondChar)==Common::SB)//se    :IAC SB MCCP2 IAC SE
                    {
                        qDebug()<<"MainWindow::checkStr Common::SB";
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
                        qDebug()<<"MainWindow::checkStr Common::DONT";
                        compressed = false;
                    }
                }
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
        //qDebug()<<"MainWindow::checkStr--"<<backArray;
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

void MainWindow::checkAlise(QByteArray &)
{
    //d
}

void MainWindow::on_cmdLE_returnPressed()
{
    socketWrite(ui->cmdLE->text());
    ui->cmdLE->selectAll();
}
