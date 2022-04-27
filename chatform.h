#ifndef CHATFORM_H
#define CHATFORM_H

#include <QWidget>
#include <QTextCharFormat>
#include <QTextBlockFormat>
#include <QTextCursor>

namespace Ui {
class ChatForm;
}

enum Colors { close_all=0,//关闭所有属性
              Bold_Color,//设置高亮度
              underline=4,//下划线
              Italic,//闪烁
              Overline=7,//反白显示
              StrikeOut,//不可见
              font_darkgray = 30,
              font_red,
              font_green,
              font_yellow,//【任务】
              font_cyan,
              font_magenta,//【谣言】
              font_darkgrren,//【闲聊】
              font_white,//【求助】【江湖】【北侠QQ群】
              back_darkgray = 40,
              back_red,
              back_green,
              back_yellow,
              back_cyan,
              back_magenta,
              back_darkgrren,
              back_white};

enum StrType{
    renWu = 0,
    yaoYan,
    xianLiao,
    qiuZhu,
    jiangHu,
    beiXiaQun
};

class ChatForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChatForm(QWidget *parent = nullptr);
    ~ChatForm();

    void appendOneStr(int Num, QByteArray& inarray, QTextCharFormat& inFmt, QFont& inFont);
private slots:
    void on_renWuEdit_textChanged();

    void on_yaoYanEdit_textChanged();

    void on_xianLiaoEdit_textChanged();

    void on_qiuZhuEdit_textChanged();

    void on_jiangHuEdit_textChanged();

    void on_beiXiaQQQunEdit_textChanged();

    void on_resetBT_clicked();

private:
    Ui::ChatForm *ui;
    bool renWuEditScrollBar=false;
    bool yaoYanEditScrollBar=false;
    bool xianLiaoEditScrollBar=false;
    bool qiuZhuEditScrollBar=false;
    bool jiangHuEditScrollBar=false;
    bool beiXiaQQQunEditScrollBar=false;

    int renWuEditlowNum=0;
    int yaoYanEditlowNum=0;
    int xianLiaoEditlowNum=0;
    int qiuZhuEditlowNum=0;
    int jiangHuEditlowNum=0;
    int beiXiaQQQunEditlowNum=0;

    QTextCharFormat fmt1;//字体背景色
    QFont font1;//字体
    QTextBlockFormat blockFormat1;//行间距
    QTextCursor renWuEditinsertTextCursor;
    QTextCursor yaoYanEditinsertTextCursor;
    QTextCursor xianLiaoEditinsertTextCursor;
    QTextCursor qiuZhuEditinsertTextCursor;
    QTextCursor jiangHuEditinsertTextCursor;
    QTextCursor beiXiaQQQunEditinsertTextCursor;

    void showStrThisWidget(int Num, QByteArray& inarray, QTextCharFormat& inFmt, QFont& inFont);
    /* @brief 从输入数组中，设置当前光标的背景颜色*/
    void getCursorStyleFromArray(int Num, QByteArray& inarray, QTextCharFormat& inFmt, QFont& inFont);
    /* @brief 从输入数组中，设置当前光标的背景颜色*/
    void setTextCursorFromArray(int, QFont&, QTextCharFormat&);
    /* @brief 从输入数组中获取 当前光标颜色下应该显示的文字*/
    void getShowStrFromArray(QByteArray &inArray, QByteArray &outArray);
};

#endif // CHATFORM_H
