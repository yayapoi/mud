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
              font_black = 30,
              font_red,
              font_green,
              font_yellow,
              font_blue,
              font_magenta,
              font_darkgrren,
              font_white,
              back_black = 40,
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

    void appendNewText(QString&);
    void appendNewText(QByteArray);
private slots:

private:
    Ui::FontWidget *ui;
    QTextCursor insertTextCursor;



    int lowNum=0;
    /**
     * @brief 通过用户传入的样式字符串，初始化指针，用户使用指针进行插入
     * @param styleStr  用户传入的样式
     * @param cursor  用户使用此进行插入数值
     */
    void getStyleFormStr(QString& styleStr, QTextCursor& cursor);

    /* @brief 从输入数组中，截取出一行放入输出数组中*/
    void getOneStrFromArray(QByteArray &inArray, QByteArray &outArray);
};

#endif // FONTWIDGET_H
