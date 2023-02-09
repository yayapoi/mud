#ifndef CHATFORM_H
#define CHATFORM_H

#include <QWidget>
#include <QTextCharFormat>
#include <QTextBlockFormat>
#include <QTextCursor>
#include <QRegularExpression>

namespace Ui {
class ChatForm;
}

class ChatForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChatForm(QWidget *parent = nullptr);
    ~ChatForm();

    void appendOneStr(int Num, QByteArray& inarray, QTextCharFormat& inFmt, QFont& inFont);
    ///界面隐藏至只剩按钮时，界面依旧占用很大面积，不能点击主界面，所以记录下宽高，改变本界面大小
    void setSizes(int Width, int Height);
    ///主界面获取这界面是否缩小状态 true:隐藏  false:不隐藏
    bool getHideStatus();
private slots:
    void on_renWuEdit_textChanged();

    void on_yaoYanEdit_textChanged();

    void on_xianLiaoEdit_textChanged();

    void on_qiuZhuEdit_textChanged();

    void on_jiangHuEdit_textChanged();

    void on_beiXiaQQQunEdit_textChanged();

    void on_resetBT_clicked();

    void on_resizeBT_clicked(bool checked);

private:
    Ui::ChatForm *ui;
    ///隐藏后的宽高
    int width=0;
    ///隐藏后的宽高
    int height=0;
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

    QRegularExpression tabRegular{"\\t"};
    QRegularExpression regular{"\\033\\[\\d+(;\\d+)*m"};//对比的是字符串，不是传入的数组，导致获得的起点不是真正的起点
    QRegularExpression regular1{"\\d+"};

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
signals:
    /* @brief 告诉主界面自己是否隐藏，挪动自己*/
    void ChatFormHide(bool);
};

#endif // CHATFORM_H
