#ifndef FONTWIDGET_H
#define FONTWIDGET_H

#include <QWidget>
#include <qtextcursor.h>
#include <chatform.h>

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

protected:
    virtual void resizeEvent(QResizeEvent *event) override;
private slots:

    void on_fightEdit_textChanged();

    void on_tmpEdit_textChanged();

private:
    Ui::FontWidget *ui;

    ChatForm *chatForm=nullptr;

    QTextCursor insertTextCursor;
    QTextCursor tmpInsertTextCursor;
    QTextCharFormat fmt;//字体背景色
    QFont font;//字体
    QTextBlockFormat blockFormat;//行间距
    /* @brief 点击滚动条后禁止滚动*/
    bool clickScrollBar=false;
    /* @brief 记录有几行滚动条*/
    int lowNum=0;

    /* @brief 从输入数组中，截取出一行放入输出数组中*/
    void getOneStrFromArray(QByteArray &inArray, QByteArray &outArray);
    /* @brief 从输入数组中，设置当前光标的背景颜色*/
    void getCursorStyleFromArray(QByteArray &inArray);
    /* @brief 从输入数组中，设置当前光标的背景颜色*/
    void setTextCursorFromArray(int, QFont&, QTextCharFormat&);
    /* @brief 从输入数组中获取 当前光标颜色下应该显示的文字*/
    void getShowStrFromArray(QByteArray &inArray, QByteArray &outArray);
    void showStrThisWidget(QByteArray& inArray);
};

#endif // FONTWIDGET_H
