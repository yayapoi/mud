#include <QDebug>
#include "pointbar.h"
#include <QPainter>


PointBar::PointBar(QWidget *parent):QLabel(parent)
{
}

void PointBar::setPointNum(int now, int end, int max)
{
    nowNum=now;
    lastMaxNum=end;
    maxNum=max;
}

void PointBar::setPointStatus(int statur)
{
    status=statur;
}

void PointBar::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QRect maxRect = QRect(0, 0, width(), height());
    QRect lastRect = QRect(0, 0, width()*lastMaxNum/maxNum, height());
    QRect nowRect = QRect(0, 0, width()*nowNum/maxNum, height());

    //线性渐变
    // 反走样
    painter.setRenderHint(QPainter::Antialiasing, true);
    // 设置渐变色
    QLinearGradient linear(QPointF(0,0), QPointF(0, height()));
    linear.setColorAt(0, Qt::darkGray);
    linear.setColorAt(1, Qt::gray);
    // 设置显示模式
    linear.setSpread(QGradient::PadSpread);
    // 设置画笔颜色、宽度
    painter.setPen(QPen(Qt::black, 2));
    // 设置画刷填充
    painter.setBrush(linear);
    // 绘制椭圆
    painter.drawRect(maxRect);

    linear.setColorAt(1, Qt::white);
    painter.setBrush(linear);
    painter.drawRect(lastRect);

    if(status==pointStatus::hp)
        linear.setColorAt(1, Qt::green);
    else
        linear.setColorAt(1,Qt::blue);
    painter.setBrush(linear);
    painter.drawRect(nowRect);
    QLabel::paintEvent(e);
}
