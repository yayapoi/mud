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
};

#endif // CHATFORM_H
