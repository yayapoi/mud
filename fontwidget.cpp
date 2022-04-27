/*
 * // 列举qt支持的所有中文字体
    //QFontDatabase fontDatabase;
    //    for(auto it:fontDatabase.families(QFontDatabase::SimplifiedChinese))
    //    {
    //qDebug()<<it;
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

    QFont font = QFont("Microsoft YaHei",20,2);
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
//qDebug()<<"行数："<<lineCount;
//qDebug()<<"字数："<<ui->fightTE->document()->characterCount();
    ui->fightTE->document()->setMaximumBlockCount(5);


    html方式
    QString bgColorStrHead=QString::fromLatin1("<span style=\"background-color: rgb(200, 200, 200); color:rgb(255, 0, 230)\">");  //设置文字颜色
    QString bgColorStrTail=QString::fromLatin1("</span>");
    QString bgColorStrHead2=QString::fromLatin1("<span style=\"background-color: rgb(230, 230, 230)\">");  //颜色可以自己改变
    QString bgColorStrTail2=QString::fromLatin1("</span>");
    QString strOne="00000000011111111112222222222333333333344444444445555555555666666666677777777778";
    strOne=bgColorStrHead+strOne+bgColorStrTail;
    ui->fightTE->append(strOne);



    可以看看这篇机翻
    https://blog.csdn.net/hitzsf/article/details/113761608?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522165050834416782094855343%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=165050834416782094855343&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-5-113761608.142^v9^control,157^v4^control&utm_term=QFont&spm=1018.2226.3001.4187
*/


/*
 * 0x0D \n
 * 0x0A \r
 * 0X5B [
 * 0X3B ;
 * 0X1B \033
 * 0X6D m
*/

#include "fontwidget.h"
#include "ui_fontwidget.h"
#include <QTextDocument>
#include <QTextBlock>
#include <qdebug.h>
#include <QRegularExpression>
#include <QScrollBar>

FontWidget::FontWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FontWidget)
{
    ui->setupUi(this);
    ui->fightEdit->setReadOnly(true);
    ui->fightEdit->setStyleSheet("background-color: rgb(0, 0, 0);");
    ui->fightEdit->document()->setMaximumBlockCount(2000);
    ui->tmpEdit->setEnabled(false);
    ui->tmpEdit->setStyleSheet("background-color: rgb(0, 0, 0);");
    ui->tmpEdit->document()->setMaximumBlockCount(2000);
    ui->tmpEdit->hide();

    chatForm=new ChatForm(this);
    chatForm->setGeometry(1000,0,500,500);
    chatForm->show();

    connect(ui->fightEdit->verticalScrollBar(),&QScrollBar::rangeChanged,[&](int mixNum, int maxnum){
        //鼠标滚动或者向上拉滚动条时，开启滚动条不滚动
        //qDebug()<<"mixNum--"<<mixNum<<"  maxnum--"<<maxnum;
        lowNum=maxnum;
    });
    connect(ui->fightEdit->verticalScrollBar(),&QScrollBar::valueChanged,[&](int testnum){
        //鼠标滚动或者向上拉滚动条时，开启滚动条不滚动
        //qDebug()<<"testnum--"<<testnum<<"  lowNum--"<<lowNum;
        if(testnum<lowNum)
        {
            clickScrollBar=true;
            ui->tmpEdit->show();
        }
    });

    insertTextCursor=ui->fightEdit->cursorForPosition(QPoint(0,0));
    insertTextCursor.movePosition(QTextCursor::End);
    blockFormat.setLineHeight(3, QTextBlockFormat::LineDistanceHeight);
    font.setFamily("宋体");//中文字体
    font.setPointSize(11);//点大小  如果指定了点大小，则像素大小属性的值就是 -1
    fmt.setFont(font);
    //font.setLetterSpacing(QFont::AbsoluteSpacing,1);//字间距
    fmt.setForeground(Qt::lightGray);//设置选中行的字体颜色
    insertTextCursor.mergeCharFormat(fmt);//应用字体
    insertTextCursor.setBlockFormat(blockFormat);//应用行间距

    tmpInsertTextCursor=ui->tmpEdit->cursorForPosition(QPoint(0,0));
    tmpInsertTextCursor.movePosition(QTextCursor::End);
    tmpInsertTextCursor.mergeCharFormat(fmt);//应用字体
    tmpInsertTextCursor.setBlockFormat(blockFormat);//应用行间距
}

FontWidget::~FontWidget()
{
    delete ui;
}

void FontWidget::appendNewText(QByteArray backArray)
{
    //QString testStr(backArray);
    //qDebug()<<lowNum++<<"****"<<testStr;

    while (backArray.size()>0) {//循环截取出要打印的字符串  一行的那种
        QByteArray oneStr;
        getOneStrFromArray(backArray, oneStr);//截取出要打印的字符串  一行的那种
        {
            QRegularExpression regular1("\\033\\[1;33m【任务】");
            QRegularExpression regular2("\\033\\[1;35m【谣言】");
            QRegularExpression regular3("\\033\\[1;36m【闲聊】");

            QRegularExpression regular4("\\033\\[1;37m【求助】");
            QRegularExpression regular5("\\033\\[1;37m【江湖】");
            QRegularExpression regular6("\\033\\[37m【北侠QQ群】");
            QRegularExpressionMatch regularmatch=regular1.match(oneStr);
            if(regularmatch.hasMatch())//字符串一开始就是颜色设置
            {
                //qDebug()<<"("<<regularmatch.capturedStart()<<","<<regularmatch.capturedEnd()<<")"<<regularmatch.captured(0);
                //qDebug()<<"  【任务】--"<<QString(oneStr);
                //qDebug()<<"  【任务】--"<<oneStr;
                fmt.setForeground(Qt::yellow);
                chatForm->appendOneStr(0,oneStr,fmt,font);
            }
            else
            {
                QRegularExpressionMatch regularmatch2=regular2.match(oneStr);
                if(regularmatch2.hasMatch())//字符串一开始就是颜色设置
                {
                    //qDebug()<<"("<<regularmatch2.capturedStart()<<","<<regularmatch2.capturedEnd()<<")"<<regularmatch2.captured(0);
                    //qDebug()<<"  【谣言】--"<<QString(oneStr);
                    //qDebug()<<"  【谣言】--"<<oneStr;
                    fmt.setForeground(Qt::yellow);
                    chatForm->appendOneStr(1,oneStr,fmt,font);
                }
                else
                {
                    QRegularExpressionMatch regularmatch3=regular3.match(oneStr);
                    if(regularmatch3.hasMatch())//字符串一开始就是颜色设置
                    {
                        //qDebug()<<"("<<regularmatch3.capturedStart()<<","<<regularmatch3.capturedEnd()<<")"<<regularmatch3.captured(0);
                        //qDebug()<<"  【闲聊】--"<<QString(oneStr);
                        //qDebug()<<"  【闲聊】--"<<oneStr;
                        fmt.setForeground(Qt::yellow);
                        chatForm->appendOneStr(2,oneStr,fmt,font);
                    }
                    else
                    {
                        QRegularExpressionMatch regularmatch4=regular4.match(oneStr);
                        if(regularmatch4.hasMatch())//字符串一开始就是颜色设置
                        {
                            //qDebug()<<"("<<regularmatch4.capturedStart()<<","<<regularmatch4.capturedEnd()<<")"<<regularmatch4.captured(0);
                            //qDebug()<<"  【求助】--"<<QString(oneStr);
                            //qDebug()<<"  【求助】--"<<oneStr;
                            fmt.setForeground(Qt::yellow);
                            chatForm->appendOneStr(3,oneStr,fmt,font);
                        }
                        else
                        {
                            QRegularExpressionMatch regularmatch5=regular5.match(oneStr);
                            if(regularmatch5.hasMatch())//字符串一开始就是颜色设置
                            {

                                //qDebug()<<"("<<regularmatch5.capturedStart()<<","<<regularmatch5.capturedEnd()<<")"<<regularmatch5.captured(0);
                                //qDebug()<<"  【江湖】--"<<QString(oneStr);
                                //qDebug()<<"  【江湖】--"<<oneStr;
                                fmt.setForeground(Qt::yellow);
                                chatForm->appendOneStr(4,oneStr,fmt,font);
                            }
                            else
                            {
                                QRegularExpressionMatch regularmatch6=regular6.match(oneStr);
                                if(regularmatch6.hasMatch())//字符串一开始就是颜色设置
                                {
                                    //qDebug()<<"("<<regularmatch6.capturedStart()<<","<<regularmatch6.capturedEnd()<<")"<<regularmatch6.captured(0);
                                    //qDebug()<<"  【北侠QQ群】--"<<QString(oneStr);
                                    //qDebug()<<"  【北侠QQ群】--"<<oneStr;
                                    fmt.setForeground(Qt::yellow);
                                    chatForm->appendOneStr(5,oneStr,fmt,font);
                                }
                                else
                                {
                                    showStrThisWidget(oneStr);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void FontWidget::setClickScrollBar()
{
    clickScrollBar=false;
    ui->tmpEdit->hide();
    ui->tmpEdit->clear();
    ui->fightEdit->verticalScrollBar()->setValue(ui->fightEdit->verticalScrollBar()->maximum());
}

void FontWidget::resizeEvent(QResizeEvent *event)
{
    //qDebug()<<"FontWidget::resizeEvent";
    if(clickScrollBar==false)
    {
        ui->fightEdit->verticalScrollBar()->setValue(ui->fightEdit->verticalScrollBar()->maximum());
    }
    QWidget::resizeEvent(event);
}

void FontWidget::getOneStrFromArray(QByteArray &inArray, QByteArray &outArray)
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

void FontWidget::getCursorStyleFromArray(QByteArray &inArray)
{
    QRegularExpression regular("\\033\\[\\d+(;\\d+)*m");
    QRegularExpression regular1("\\d+");
    QRegularExpressionMatch regularmatch=regular.match(inArray);
    if(regularmatch.hasMatch())//字符串一开始就是颜色设置
    {
        //qDebug()<<"("<<regularmatch.capturedStart()<<","<<index<<")"<<regularmatch.captured(0);
        //int end=regularmatch.capturedEnd();
        //int start=regularmatch.capturedStart();
        //QString checkStr=regularmatch.captured(0);
        //qDebug()<<"old checkStr--"<<checkStr;
        //checkStr.remove(QRegularExpression("\\033\\["));
        //inArray.remove(regularmatch.capturedStart(),regularmatch.capturedEnd()-regularmatch.capturedStart());
        //qDebug()<<"start--"<<start<<"  end--"<<end<<"  new checkStr--"<<checkStr<<"  inArray--"<<inArray;
        if(regularmatch.capturedStart()==0)
        {
            QString checkStr=regularmatch.captured(0);
            inArray.remove(regularmatch.capturedStart(),regularmatch.capturedLength());
            checkStr.remove(QRegularExpression("\\033\\["));
            //qDebug()<<"checkStr--"<<checkStr;
            int index=0;
            while (index<checkStr.size()) {
                QRegularExpressionMatch regularmatch1=regular1.match(checkStr, index);
                if(regularmatch1.hasMatch())
                {
                    index=regularmatch1.capturedEnd();
                    //qDebug()<<"("<<regularmatch1.capturedStart()<<","<<regularmatch1.capturedEnd()<<")"<<regularmatch1.captured(0).toInt();
                    //获取每种颜色设置

                    setTextCursorFromArray(regularmatch1.captured(0).toInt(), font, fmt);
                    fmt.setFont(font);
                    //insertTextCursor.setBlockFormat(blockFormat);//应用行间距
                    tmpInsertTextCursor.mergeCharFormat(fmt);//应用字体
                    insertTextCursor.mergeCharFormat(fmt);//应用字体
                }
                else
                {
                    break;
                }
            }
        }
    }
}

void FontWidget::setTextCursorFromArray(int fontStyle, QFont& backFont, QTextCharFormat& backCharFormat)
{
    switch (fontStyle) {
    case Colors::close_all:
    {
        backFont.setFamily("宋体");//字体
        backFont.setPointSize(11);//点大小  如果指定了点大小，则像素大小属性的值就是 -1
        backFont.setWeight(QFont::Normal);//设置粗体属性实际上就是将字体的粗细设为一个确定的值
        backFont.setUnderline(false);//下划线
        backFont.setStrikeOut(false);//删除线
        backFont.setOverline(false);//上划线
        backFont.setItalic(false);//斜体
        backFont.setBold(false);//设置黑体 粗体
        backCharFormat.setForeground(Qt::lightGray);
        backCharFormat.setBackground(Qt::black);
        break;
    }
    case Colors::Bold_Color:
    {
        backFont.setBold(true);//设置黑体 粗体
        break;
    }
    case Colors::underline:
    {
        backFont.setUnderline(true);//下划线
        break;
    }
    case Colors::Italic:
    {
        backFont.setItalic(true);//斜体
        break;
    }
    case Colors::Overline:
    {
        backFont.setOverline(true);//上划线
        break;
    }
    case Colors::StrikeOut:
    {
        backFont.setStrikeOut(true);//删除线
        break;
    }
    case Colors::font_darkgray:
    {
        backCharFormat.setForeground(Qt::darkGray);
        break;
    }
    case Colors::font_red:
    {
        backCharFormat.setForeground(Qt::red);
        break;
    }
    case Colors::font_green:
    {
        backCharFormat.setForeground(Qt::green);
        break;
    }
    case Colors::font_yellow:
    {
        backCharFormat.setForeground(Qt::yellow);
        break;
    }
    case Colors::font_cyan:
    {
        backCharFormat.setForeground(Qt::cyan);
        break;
    }
    case Colors::font_magenta:
    {
        backCharFormat.setForeground(Qt::magenta);
        break;
    }
    case Colors::font_darkgrren:
    {
        backCharFormat.setForeground(Qt::darkGreen);
        break;
    }
    case Colors::font_white:
    {
        backCharFormat.setForeground(Qt::white);
        break;
    }
    case Colors::back_darkgray:
    {
        backCharFormat.setBackground(Qt::darkGray);
        break;
    }
    case Colors::back_red:
    {
        backCharFormat.setBackground(Qt::red);
        break;
    }
    case Colors::back_green:
    {
        backCharFormat.setBackground(Qt::green);
        break;
    }
    case Colors::back_yellow:
    {
        backCharFormat.setBackground(Qt::yellow);
        break;
    }
    case Colors::back_cyan:
    {
        backCharFormat.setBackground(Qt::cyan);
        break;
    }
    case Colors::back_magenta:
    {
        backCharFormat.setBackground(Qt::magenta);
        break;
    }
    case Colors::back_darkgrren:
    {
        backCharFormat.setBackground(Qt::darkGreen);
        break;
    }
    case Colors::back_white:
    {
        backCharFormat.setBackground(Qt::white);
        break;
    }
    default:
        break;
    }
}

void FontWidget::getShowStrFromArray(QByteArray &inArray, QByteArray &outArray)
{
    /*int Num=0;
    bool fandStr=false;
    for(; Num<inArray.size()-1; Num++)
    {
        if(uchar(inArray[Num])==0X1B && uchar(inArray[Num+1])==0X5B && uchar(inArray[Num+3])!='z' )
        {
            //qDebug()<<"old inArray--"<<inArray;
            outArray=inArray.mid(0,Num);
            //qDebug()<<"start--"<<Num;
            //qDebug()<<"outArray--"<<outArray;
            inArray.remove(0,Num);
            fandStr=true;
            //qDebug()<<"new inArray--"<<inArray;
            //qDebug();
            break;
        }
    }
    if(fandStr==false)
    {
        outArray=inArray;
        inArray.clear();
    }*/
    QRegularExpression regular("\\033\\[\\d+(;\\d+)*m");//对比的是字符串，不是传入的数组，导致获得的起点不是真正的起点
    QRegularExpressionMatch regularmatch=regular.match(inArray);
    if(regularmatch.hasMatch())//检测出颜色切换
    {
        QByteArray backStrArray=regularmatch.captured(0).toUtf8();
        int Num=inArray.indexOf(backStrArray);

        //qDebug()<<"old inArray--"<<inArray;
        //qDebug()<<"start--"<<Num;
        outArray=inArray.mid(0,Num);
        //qDebug()<<"outArray--"<<outArray;
        inArray.remove(0,Num);
        //qDebug()<<"new inArray--"<<inArray;
        //qDebug();
    }
    else
    {
        outArray=inArray;
        inArray.clear();
    }
}

void FontWidget::showStrThisWidget(QByteArray &inArray)
{
    while (inArray.size()>0) {
        getCursorStyleFromArray(inArray);//设置光标颜色
        QByteArray showStr;
        getShowStrFromArray(inArray, showStr);//从数组中获取 当前光标颜色下应该显示的文字

        //QString asdfasdfasdf(oneStr);
        //asdfasdfasdf.remove(QRegularExpression("\\033\\[\\d+(;\\d+)*m"));
        if(clickScrollBar)
        {
            tmpInsertTextCursor.insertText(showStr);//插入字符
        }
        insertTextCursor.insertText(showStr);//插入字符
    }
}

//通过光标获取选中的文本，并且获取字体的属性
/*
     * QTextCursor cursor=ui->writeEdit->document()->find("dddd");
    QTextBlock textBlock = ui->writeEdit->document()->findBlockByLineNumber(cursor.blockNumber());//通过行号找到指定行 数据块
    QVector<QTextLayout::FormatRange> vectora=textBlock.textFormats();
    for(auto asdfasdf:vectora)
//qDebug()<<asdfasdf.start<<"--"<<asdfasdf.length<<"--"<<asdfasdf.format;
    ui->showEdit->clear();
    ui->showEdit->appendPlainText(textBlock.text());
*/


void FontWidget::on_fightEdit_textChanged()
{
    if(clickScrollBar==false)
    {
        ui->fightEdit->verticalScrollBar()->setValue(ui->fightEdit->verticalScrollBar()->maximum());
    }
}


void FontWidget::on_tmpEdit_textChanged()
{
    ui->tmpEdit->verticalScrollBar()->setValue(ui->fightEdit->verticalScrollBar()->maximum());
}

