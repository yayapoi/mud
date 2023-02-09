#include "chatform.h"
#include "ui_chatform.h"
#include <QScrollBar>
#include <QDebug>
#include <QTime>
#include <globalhead.h>

ChatForm::ChatForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatForm)
{
    ui->setupUi(this);
    ui->resizeBT->setCheckable(true);
    this->setStyleSheet("QMenu\
                        {\
                            color:black;\
                            background-color:rgb(255,255,255);\
                            border:none;\
                        }"
                         "QMenu::item\
                        {\
                            color:black;\
                            background-color:rgb(255,255,255);\
                        }"
                         "QMenu::item:selected\
                        {\
                            color:rgb(255,255,255);\
                            background-color:#1a9b81;\
                        }\
                        QMenu::separator\
                        {\
                            height:1px;\
                            background-color:rgba(255,255,255,1);\
                            margin-left:5px;\
                            margin-right:5px;\
                        }");
                        ui->chatWidget->setTabText(0,"任务");
            ui->chatWidget->setTabText(1,"谣言");
    ui->chatWidget->setTabText(2,"闲聊");
    ui->chatWidget->setTabText(3,"求助");
    ui->chatWidget->setTabText(4,"江湖");
    ui->chatWidget->setTabText(5,"北侠群");

    ui->renWuEdit->setReadOnly(true);
    ui->renWuEdit->setStyleSheet("background-color: rgb(0, 0, 0);");
    ui->renWuEdit->document()->setMaximumBlockCount(500);
    connect(ui->renWuEdit->verticalScrollBar(),&QScrollBar::rangeChanged,[&](int mixNum, int maxnum){
        renWuEditlowNum=maxnum;});
    connect(ui->renWuEdit->verticalScrollBar(),&QScrollBar::valueChanged,[&](int testnum){
        if(testnum<renWuEditlowNum){renWuEditScrollBar=true;}});

    ui->yaoYanEdit->setReadOnly(true);
    ui->yaoYanEdit->setStyleSheet("background-color: rgb(0, 0, 0);");
    ui->yaoYanEdit->document()->setMaximumBlockCount(500);
    connect(ui->yaoYanEdit->verticalScrollBar(),&QScrollBar::rangeChanged,[&](int mixNum, int maxnum){
        yaoYanEditlowNum=maxnum;});
    connect(ui->yaoYanEdit->verticalScrollBar(),&QScrollBar::valueChanged,[&](int testnum){
        if(testnum<yaoYanEditlowNum){yaoYanEditScrollBar=true;}});

    ui->xianLiaoEdit->setReadOnly(true);
    ui->xianLiaoEdit->setStyleSheet("background-color: rgb(0, 0, 0);");
    ui->xianLiaoEdit->document()->setMaximumBlockCount(500);
    connect(ui->xianLiaoEdit->verticalScrollBar(),&QScrollBar::rangeChanged,[&](int mixNum, int maxnum){
        xianLiaoEditlowNum=maxnum;});
    connect(ui->xianLiaoEdit->verticalScrollBar(),&QScrollBar::valueChanged,[&](int testnum){
        if(testnum<xianLiaoEditlowNum){xianLiaoEditScrollBar=true;}});

    ui->qiuZhuEdit->setReadOnly(true);
    ui->qiuZhuEdit->setStyleSheet("background-color: rgb(0, 0, 0);");
    ui->qiuZhuEdit->document()->setMaximumBlockCount(500);
    connect(ui->qiuZhuEdit->verticalScrollBar(),&QScrollBar::rangeChanged,[&](int mixNum, int maxnum){
        qiuZhuEditlowNum=maxnum;});
    connect(ui->qiuZhuEdit->verticalScrollBar(),&QScrollBar::valueChanged,[&](int testnum){
        if(testnum<qiuZhuEditlowNum){qiuZhuEditScrollBar=true;}});

    ui->jiangHuEdit->setReadOnly(true);
    ui->jiangHuEdit->setStyleSheet("background-color: rgb(0, 0, 0);");
    ui->jiangHuEdit->document()->setMaximumBlockCount(500);
    connect(ui->jiangHuEdit->verticalScrollBar(),&QScrollBar::rangeChanged,[&](int mixNum, int maxnum){
        jiangHuEditlowNum=maxnum;});
    connect(ui->jiangHuEdit->verticalScrollBar(),&QScrollBar::valueChanged,[&](int testnum){
        if(testnum<jiangHuEditlowNum){jiangHuEditScrollBar=true;}});

    ui->beiXiaQQQunEdit->setReadOnly(true);
    ui->beiXiaQQQunEdit->setStyleSheet("background-color: rgb(0, 0, 0);");
    ui->beiXiaQQQunEdit->document()->setMaximumBlockCount(500);
    connect(ui->beiXiaQQQunEdit->verticalScrollBar(),&QScrollBar::rangeChanged,[&](int mixNum, int maxnum){
        beiXiaQQQunEditlowNum=maxnum;});
    connect(ui->beiXiaQQQunEdit->verticalScrollBar(),&QScrollBar::valueChanged,[&](int testnum){
        if(testnum<beiXiaQQQunEditlowNum){beiXiaQQQunEditScrollBar=true;}});


    blockFormat1.setLineHeight(3, QTextBlockFormat::LineDistanceHeight);
    font1.setFamily("明黑等宽");//中文字体
    font1.setPointSize(11);//点大小  如果指定了点大小，则像素大小属性的值就是 -1
    fmt1.setFont(font1);
    fmt1.setForeground(Qt::lightGray);//设置选中行的字体颜色

    renWuEditinsertTextCursor=ui->renWuEdit->cursorForPosition(QPoint(0,0));
    renWuEditinsertTextCursor.movePosition(QTextCursor::End);
    renWuEditinsertTextCursor.mergeCharFormat(fmt1);//应用字体
    renWuEditinsertTextCursor.setBlockFormat(blockFormat1);//应用行间距

    yaoYanEditinsertTextCursor=ui->yaoYanEdit->cursorForPosition(QPoint(0,0));
    yaoYanEditinsertTextCursor.movePosition(QTextCursor::End);
    yaoYanEditinsertTextCursor.mergeCharFormat(fmt1);//应用字体
    yaoYanEditinsertTextCursor.setBlockFormat(blockFormat1);//应用行间距

    xianLiaoEditinsertTextCursor=ui->xianLiaoEdit->cursorForPosition(QPoint(0,0));
    xianLiaoEditinsertTextCursor.movePosition(QTextCursor::End);
    xianLiaoEditinsertTextCursor.mergeCharFormat(fmt1);//应用字体
    xianLiaoEditinsertTextCursor.setBlockFormat(blockFormat1);//应用行间距

    qiuZhuEditinsertTextCursor=ui->qiuZhuEdit->cursorForPosition(QPoint(0,0));
    qiuZhuEditinsertTextCursor.movePosition(QTextCursor::End);
    qiuZhuEditinsertTextCursor.mergeCharFormat(fmt1);//应用字体
    qiuZhuEditinsertTextCursor.setBlockFormat(blockFormat1);//应用行间距

    jiangHuEditinsertTextCursor=ui->jiangHuEdit->cursorForPosition(QPoint(0,0));
    jiangHuEditinsertTextCursor.movePosition(QTextCursor::End);
    jiangHuEditinsertTextCursor.mergeCharFormat(fmt1);//应用字体
    jiangHuEditinsertTextCursor.setBlockFormat(blockFormat1);//应用行间距

    beiXiaQQQunEditinsertTextCursor=ui->beiXiaQQQunEdit->cursorForPosition(QPoint(0,0));
    beiXiaQQQunEditinsertTextCursor.movePosition(QTextCursor::End);
    beiXiaQQQunEditinsertTextCursor.mergeCharFormat(fmt1);//应用字体
    beiXiaQQQunEditinsertTextCursor.setBlockFormat(blockFormat1);//应用行间距
    //on_resizeBT_clicked(true);
}

ChatForm::~ChatForm()
{
    delete ui;
}

void ChatForm::appendOneStr(int Num, QByteArray& inarray, QTextCharFormat& inFmt, QFont& inFont)
{
    showStrThisWidget(Num, inarray, inFmt, inFont);
}

void ChatForm::setSizes(int Width, int Height)
{
    width=Width;
    height=Height;
}

bool ChatForm::getHideStatus()
{
    return ui->resetBT->isHidden();
}

void ChatForm::on_renWuEdit_textChanged()
{
    if(renWuEditScrollBar==false)
    {
        ui->renWuEdit->verticalScrollBar()->setValue(ui->renWuEdit->verticalScrollBar()->maximum());
    }
}


void ChatForm::on_yaoYanEdit_textChanged()
{
    if(yaoYanEditScrollBar==false)
    {
        ui->yaoYanEdit->verticalScrollBar()->setValue(ui->yaoYanEdit->verticalScrollBar()->maximum());
    }
}


void ChatForm::on_xianLiaoEdit_textChanged()
{
    if(xianLiaoEditScrollBar==false)
    {
        ui->xianLiaoEdit->verticalScrollBar()->setValue(ui->xianLiaoEdit->verticalScrollBar()->maximum());
    }
}


void ChatForm::on_qiuZhuEdit_textChanged()
{
    if(qiuZhuEditScrollBar==false)
    {
        ui->qiuZhuEdit->verticalScrollBar()->setValue(ui->qiuZhuEdit->verticalScrollBar()->maximum());
    }
}


void ChatForm::on_jiangHuEdit_textChanged()
{
    if(jiangHuEditScrollBar==false)
    {
        ui->jiangHuEdit->verticalScrollBar()->setValue(ui->jiangHuEdit->verticalScrollBar()->maximum());
    }
}


void ChatForm::on_beiXiaQQQunEdit_textChanged()
{
    if(beiXiaQQQunEditScrollBar==false)
    {
        ui->beiXiaQQQunEdit->verticalScrollBar()->setValue(ui->beiXiaQQQunEdit->verticalScrollBar()->maximum());
    }
}


void ChatForm::on_resetBT_clicked()
{
    renWuEditScrollBar=false;
    ui->renWuEdit->verticalScrollBar()->setValue(ui->renWuEdit->verticalScrollBar()->maximum());

    yaoYanEditScrollBar=false;
    ui->yaoYanEdit->verticalScrollBar()->setValue(ui->yaoYanEdit->verticalScrollBar()->maximum());

    xianLiaoEditScrollBar=false;
    ui->xianLiaoEdit->verticalScrollBar()->setValue(ui->xianLiaoEdit->verticalScrollBar()->maximum());

    qiuZhuEditScrollBar=false;
    ui->qiuZhuEdit->verticalScrollBar()->setValue(ui->qiuZhuEdit->verticalScrollBar()->maximum());

    jiangHuEditScrollBar=false;
    ui->jiangHuEdit->verticalScrollBar()->setValue(ui->jiangHuEdit->verticalScrollBar()->maximum());

    beiXiaQQQunEditScrollBar=false;
    ui->beiXiaQQQunEdit->verticalScrollBar()->setValue(ui->beiXiaQQQunEdit->verticalScrollBar()->maximum());
}

void ChatForm::showStrThisWidget(int Num, QByteArray &inarray, QTextCharFormat &inFmt, QFont &inFont)
{
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("MM-dd ");
    QString current_time = current_date_time.toString("hh:mm:ss: ");
    QByteArray showStr;
    showStr.append(current_date.toUtf8());
    showStr.append(current_time.toUtf8());
    while (inarray.size()>0) {
        getCursorStyleFromArray(Num, inarray, inFmt, inFont);//设置光标颜色
        getShowStrFromArray(inarray, showStr);//从数组中获取 当前光标颜色下应该显示的文字

        QString showStrStr(showStr);
        showStrStr.replace(tabRegular,"        ");
        switch (Num) {
        case StrType::renWu:
        {
            renWuEditinsertTextCursor.insertText(showStrStr);//应用字体
            break;
        }
        case StrType::yaoYan:
        {
            yaoYanEditinsertTextCursor.insertText(showStrStr);//应用字体
            break;
        }
        case StrType::xianLiao:
        {
            xianLiaoEditinsertTextCursor.insertText(showStrStr);//应用字体
            break;
        }
        case StrType::qiuZhu:
        {
            qiuZhuEditinsertTextCursor.insertText(showStrStr);//应用字体
            break;
        }
        case StrType::jiangHu:
        {
            jiangHuEditinsertTextCursor.insertText(showStrStr);//应用字体
            break;
        }
        case StrType::beiXiaQun:
        {
            beiXiaQQQunEditinsertTextCursor.insertText(showStrStr);//应用字体
            break;
        }
        default:
            break;
        }
        showStr.clear();
    }
}

void ChatForm::getCursorStyleFromArray(int Num, QByteArray &inarray, QTextCharFormat &inFmt, QFont &inFont)
{
    QRegularExpressionMatch regularmatch=regular.match(inarray);
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
            inarray.remove(regularmatch.capturedStart(),regularmatch.capturedLength());
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

                    setTextCursorFromArray(regularmatch1.captured(0).toInt(), inFont, inFmt);
                    inFmt.setFont(inFont);
                    renWuEditinsertTextCursor.mergeCharFormat(inFmt);//应用字体
                    yaoYanEditinsertTextCursor.mergeCharFormat(inFmt);//应用字体
                    xianLiaoEditinsertTextCursor.mergeCharFormat(inFmt);//应用字体
                    qiuZhuEditinsertTextCursor.mergeCharFormat(inFmt);//应用字体
                    jiangHuEditinsertTextCursor.mergeCharFormat(inFmt);//应用字体
                    beiXiaQQQunEditinsertTextCursor.mergeCharFormat(inFmt);//应用字体
                }
                else
                {
                    break;
                }
            }
        }
    }
}

void ChatForm::setTextCursorFromArray(int fontStyle, QFont& backFont, QTextCharFormat& backCharFormat)
{
    switch (fontStyle) {
    case Colors::close_all:
    {
        backFont.setFamily("明黑等宽");//字体
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
    case Colors::font_blue:
    {
        backCharFormat.setForeground(Qt::blue);
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
    case Colors::back_blue:
    {
        backCharFormat.setBackground(Qt::blue);
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

void ChatForm::getShowStrFromArray(QByteArray &inArray, QByteArray &outArray)
{
    QRegularExpressionMatch regularmatch=regular.match(inArray);
    if(regularmatch.hasMatch())//检测出颜色切换
    {
        QByteArray backStrArray=regularmatch.captured(0).toUtf8();
        int Num=inArray.indexOf(backStrArray);

        //qDebug()<<"old inArray--"<<inArray;
        //qDebug()<<"start--"<<Num;
        outArray.append(inArray.mid(0,Num));
        //qDebug()<<"outArray--"<<outArray;
        inArray.remove(0,Num);
        //qDebug()<<"new inArray--"<<inArray;
        //qDebug();
    }
    else
    {
        outArray.append(inArray);
        inArray.clear();
    }
}


void ChatForm::on_resizeBT_clicked(bool checked)
{
    ui->chatWidget->setHidden(checked);
    ui->resetBT->setHidden(checked);
    if(checked)
    {
        resize(30,30);
    }
    else
    {
        resize(width,height);
    }
    emit ChatFormHide(checked);
}

