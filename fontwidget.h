#ifndef FONTWIDGET_H
#define FONTWIDGET_H

#include <QWidget>
#include <qtextcursor.h>

namespace Ui {
class FontWidget;
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
              font_yellow,
              font_blue,
              font_magenta,
              font_darkgrren,
              font_white,
              back_darkgray = 40,
              back_red,
              back_green,
              back_yellow,
              back_blue,
              back_magenta,
              back_darkgrren,
              back_white};

class FontWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FontWidget(QWidget *parent = nullptr);
    ~FontWidget();

    void appendNewText(QByteArray);
private slots:

private:
    Ui::FontWidget *ui;
    QTextCursor insertTextCursor;
    QTextCharFormat fmt;//字体背景色
    QFont font;//字体
    QTextBlockFormat blockFormat;//行间距


    int lowNum=0;
    /**
     * @brief 通过用户传入的样式字符串，初始化指针，用户使用指针进行插入
     * @param styleStr  用户传入的样式
     * @param cursor  用户使用此进行插入数值
     */
    void getStyleFormStr(QString& styleStr, QTextCursor& cursor);

    /* @brief 从输入数组中，截取出一行放入输出数组中*/
    void getOneStrFromArray(QByteArray &inArray, QByteArray &outArray);
    /* @brief 从输入数组中，设置当前光标的背景颜色*/
    void getCursorStyleFromArray(QByteArray &inArray);
    /* @brief 从输入数组中，设置当前光标的背景颜色*/
    void setTextCursorFromArray(int, QFont&, QTextCharFormat&);
    /* @brief 从输入数组中获取 当前光标颜色下应该显示的文字*/
    void getShowStrFromArray(QByteArray &inArray, QByteArray &outArray);
};

#endif // FONTWIDGET_H
