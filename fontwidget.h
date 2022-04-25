#ifndef FONTWIDGET_H
#define FONTWIDGET_H

#include <QWidget>

namespace Ui {
class FontWidget;
}

enum Colors { close_all=0,//关闭所有属性
              light_Color,//设置高亮度
              under_line=4,//下划线
              StrikeOut,//闪烁
              StrikeOut=7,//反白显示
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
              back_white,};

class FontWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FontWidget(QWidget *parent = nullptr);
    ~FontWidget();

    void appendNewText(QString&);
private slots:
    void on_pushButton_clicked();

private:
    Ui::FontWidget *ui;
};

#endif // FONTWIDGET_H
