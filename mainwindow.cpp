#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <QRegExp>
#include <iostream>
#include <QRegularExpression>

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
    //ui->fightTE->setReadOnly(true);
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

        QString testStr(backArray);
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
        //testStr.remove('\r');
        testStr.remove(QRegularExpression("\\033\\[\\d+(;\\d+)*m"));
        //testStr.remove(QRegularExpression("\\r\\n$"));
        qDebug()<<lowNum++<<"****"<<testStr;
        QTextCursor adf=ui->fightTE->cursorForPosition(QPoint(0,0));
        adf.movePosition(QTextCursor::End);
        adf.insertText(testStr);//使用上面那句减少空换行的问题，若是有问题，则注释上句使用此句
        backArray.clear();
    });
    testSocket->connectToHost("47.97.249.185",8081);


    // 列举qt支持的所有中文字体
    //QFontDatabase fontDatabase;
    //    for(auto it:fontDatabase.families(QFontDatabase::SimplifiedChinese))
    //    {
    //        qDebug()<<it;
    //}
    // 列出系统支持的所有字体
    //    for (auto it:fontDatabase.families())
    //    {qDebug()<<it;}

    //    QFont 为绘画文本提供制定的字体
    //    QFontComboBox 提供了选择字体族的下拉列表框
    //    QFontDatabase 提供了可以在Window 操作系统下能够使用的字体
    //    QFontDialog 用来选择一个指定的字体
    //    QFontEngineInfo 用来描述一个指定的字体引擎插件
    //    QFontEnginePlugin 累提供了字体仓库插件的基础累， 用于嵌入式linux
    //    QFontInfo 包含了一个字体的常规信息
    //    QFontDialog 用来弹出对话框 来获得指定的字体
    /*
    字体号数与像素对应关系
    英文字体的1磅，相当于1/72 英寸，约等于1/2.8mm。 12PT的字打印出来约为4.2mm。网页中12px的字才相当于12像素。

    DPI: Dot per inch，在显示器上也就是每英寸包含的像素。英尺的换算为 1 cm = 0.39 inch, 1 inch = 2.54 cm。
    DPI 可以通过如下计算得来：
    水平 dpi = 水平 resolution * 2.54 / 显示器宽度
    垂直 dpi = 垂直 resolution * 2.54 / 显示器高度
    pixel pitch（点距）: 像素点间距离。可以用25.4mm / DPI得到。
    字体在屏幕上的实际大小 = 字体像素大小 * 点距

    中文字号VS英文字号(磅)VS像素值的对应关系：
    八号＝5磅(5pt) ==(5/72)*96=6.67 =6px
    七号＝5.5磅 ==(5.5/72)*96=7.3 =7px
    小六＝6.5磅 ==(6.5/72)*96=8.67 =8px
    六号＝7.5磅 ==(7.5/72)*96=10px
    小五＝9磅 ==(9/72)*96=12px
    五号＝10.5磅 ==(10.5/72)*96=14px
    小四＝12磅 ==(12/72)*96=16px
    四号＝14磅 ==(14/72)*96=18.67 =18px
    小三＝15磅 ==(15/72)*96=20px
    三号＝16磅 ==(16/72)*96=21.3 =21px
    小二＝18磅 ==(18/72)*96=24px
    二号＝22磅 ==(22/72)*96=29.3 =29px
    小一＝24磅 ==(24/72)*96=32px
    一号＝26磅 ==(26/72)*96=34.67 =34px
    小初＝36磅 ==(36/72)*96=48px
    初号＝42磅 ==(42/72)*96=56px
    */
    /*QFont font = QFont("Microsoft YaHei",20,2);
    {
        font.setFamily("微软雅黑");//字体
        font.setPixelSize(25);//像素大小  如果指定了像素大小，则点大小属性的值就是 -1。
        font.setPointSize(20);//点大小  如果指定了点大小，则像素大小属性的值就是 -1
        font.setWeight(QFont::Light);//设置粗体属性实际上就是将字体的粗细设为一个确定的值
        font.setUnderline(true);//下划线
        font.setStrikeOut(true);//删除线
        font.setOverline(true);//上划线
        font.setItalic(true);//斜体
        font.setBold(true);//设置黑体 粗体
        font.setStyle(QFont::StyleOblique);//QFont::StyleItalic:斜体
        font.setCapitalization(QFont::Capitalize);//设置首个字母大写（跟参数有关，也可以设置全部大写AllUppercase）

        font.setKerning(true);//字距调整（用得少）
        //设置字间距像素值
        font.setLetterSpacing(QFont::AbsoluteSpacing,20);             //设置字间距为100像素
        font.setLetterSpacing(QFont::PercentageSpacing,300);        //300%,100为默认
    }
    QString msg = "1测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试";
    ui->fightTE->setFont(font);
    ui->fightTE->append(msg);
    // 选中该行文字
    QTextCursor cursor = ui->fightTE->textCursor();
    cursor.setPosition(cursor.position(),QTextCursor::MoveAnchor);
    cursor.setPosition(cursor.position()+msg.length(),QTextCursor::KeepAnchor);
    cursor.select(QTextCursor::WordUnderCursor);
    QTextCharFormat fmt;
    fmt.setForeground(Qt::blue);//设置选中行的字体颜色
    fmt.setFont(QFont("YouYuan",20,QFont::Bold,true));//参数依次是字体，大小，字体的粗细，以及是否斜体
    cursor.mergeCharFormat(fmt);
    cursor.clearSelection();
    cursor.movePosition(QTextCursor::EndOfLine);//cursor和anchor均移至末尾

    msg = "2测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试";
    ui->fightTE->append(msg);
    cursor.setPosition(cursor.position(),QTextCursor::MoveAnchor);
    cursor.setPosition(cursor.position()+msg.length(),QTextCursor::KeepAnchor);
    cursor.select(QTextCursor::WordUnderCursor);
    fmt.setForeground(Qt::red);
    fmt.setFont(QFont("Microsoft YaHei",8));
    cursor.mergeCharFormat(fmt);
    cursor.clearSelection();
    cursor.movePosition(QTextCursor::EndOfLine);//cursor和anchor均移至末尾

    msg = "2测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试";
    cursor.insertText(msg);
    ui->fightTE->append(msg);
    // 获取行数、字数，设置最大行数
    int lineCount = ui->fightTE->document()->lineCount();
    qDebug()<<"行数："<<lineCount;
    qDebug()<<"字数："<<ui->fightTE->document()->characterCount();
    ui->fightTE->document()->setMaximumBlockCount(5);*/
    /*QString bgColorStrHead=QString::fromLatin1("<span style=\"background-color: rgb(200, 200, 200); color:rgb(255, 0, 230)\">");  //设置文字颜色
    QString bgColorStrTail=QString::fromLatin1("</span>");
    QString bgColorStrHead2=QString::fromLatin1("<span style=\"background-color: rgb(230, 230, 230)\">");  //颜色可以自己改变
    QString bgColorStrTail2=QString::fromLatin1("</span>");
    QString strOne="00000000011111111112222222222333333333344444444445555555555666666666677777777778";
    strOne=bgColorStrHead+strOne+bgColorStrTail;
    ui->fightTE->append(strOne);*/
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
