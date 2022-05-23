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
    maxNum=max<=0?1:max;
}

void PointBar::setPointStatus(int statur)
{
    status=statur;
}

void PointBar::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    bool nowMaxFlag=false;//有可能现在的数值超过最大值
    QRect maxRect = QRect(0, 0, width(), height());
    QRect lastRect = QRect(0, 0, width()*lastMaxNum/maxNum, height());

    QRect nowMax,nowRect;
    if(nowNum>maxNum)
    {
        nowMax = QRect(0, 0, width()*(nowNum-maxNum)/maxNum, height());
        nowRect = QRect(0, 0, width(), height());
        nowMaxFlag=true;
    }
    else
    {
        nowRect = QRect(0, 0, width()*nowNum/maxNum, height());
    }



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

    if(nowMaxFlag)
    {
        linear.setColorAt(1, Qt::cyan);
        painter.setBrush(linear);
        painter.drawRect(nowMax);
    }

    painter.setPen(QPen(Qt::red, 2));
    QString showStr=QString(" %1% ( %2 / %3 / %4 )").arg(QString::number(100.0*nowNum/maxNum, 'f', 2)).arg(nowNum).arg(lastMaxNum).arg(maxNum);
    painter.drawText(maxRect,Qt::AlignCenter,showStr);
    QLabel::paintEvent(e);
}
