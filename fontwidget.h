#ifndef FONTWIDGET_H
#define FONTWIDGET_H

#include <QWidget>
#include <qtextcursor.h>
#include <chatform.h>
#include <QRegularExpression>
#include <statusBar/statusform.h>

namespace Ui {
class FontWidget;
}

class FontWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FontWidget(QWidget *parent = nullptr);
    ~FontWidget();

    /* @brief 外部告诉此窗口要添加文本*/
    void appendNewText(QByteArray);

    /* @brief 外部告诉此窗口要滚动下去*/
    void setClickScrollBar();
    /* @brief 设置状态，血量*/
    void setHpMpStatus(QString);
    /* @brief 切换原始文本和显示文本*/
    void setShowText(bool);
    ///传入新的status或者buff字符串
    void setStatus(QByteArray& newstring, GMCPType type);
    ///传入玩家自己的名字和id
    void setMyId(QString name, QString id);
protected:
    virtual void resizeEvent(QResizeEvent *event) override;
private slots:

    void on_fightEdit_textChanged();

    void on_tmpEdit_textChanged();

    void on_allFightEdit_textChanged();

private:
    Ui::FontWidget *ui;

    ChatForm *chatForm=nullptr;
    StatusForm* myStatusForm=nullptr;

    QRegularExpression tabRegular{"\\t"};
    QRegularExpression regular{"\\033\\[\\d+(;\\d+)*m"};//对比的是字符串，不是传入的数组，导致获得的起点不是真正的起点
    QRegularExpression Numregular{"\\d+"};
    QRegularExpression regular1{"\\033\\[1;33m【任务】"};
    QRegularExpression regular2{"\\033\\[1;35m【谣言】"};
    QRegularExpression regular3{"\\033\\[1;36m【闲聊】"};
    QRegularExpression regular4{"\\033\\[1;37m【求助】"};
    QRegularExpression regular5{"\\033\\[1;37m【江湖】"};
    QRegularExpression regular6{"\\033\\[37m【北侠QQ群】"};

    QTextCursor insertTextCursor;
    QTextCursor allInsertTextCursor;//给带颜色的信息界面看的
    QTextCursor tmpInsertTextCursor;
    QTextCharFormat fmt;//字体背景色
    QFont font;//字体
    QTextBlockFormat blockFormat;//行间距
    /* @brief 点击滚动条后禁止滚动*/
    bool clickScrollBar=false;
    /* @brief 记录有几行滚动条*/
    int lowNum=0;
    /* @brief 记录allmessage有几行滚动条*/
    int allLowNum=0;

    /* @brief 从输入数组中，截取出一行放入输出数组中*/
    void getOneStrFromArray(QByteArray &inArray, QByteArray &outArray);
    /* @brief 从输入数组中，设置当前光标的背景颜色并返回颜色字符串*/
    bool getCursorStyleFromArray(QByteArray &inArray, QString& backColorStr);
    /* @brief 从输入数组中，设置当前光标的背景颜色*/
    void setTextCursorFromArray(int, QFont&, QTextCharFormat&);
    /* @brief 从输入数组中获取 当前光标颜色下应该显示的文字*/
    void getShowStrFromArray(QByteArray &inArray, QByteArray &outArray);
    void showStrThisWidget(QByteArray& inArray);
};

#endif // FONTWIDGET_H
