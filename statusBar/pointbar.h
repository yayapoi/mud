#ifndef POINTBAR_H
#define POINTBAR_H

#include <QLabel>
#include <QObject>

enum pointStatus
{
    hp = 0,
    mp
};

class PointBar : public QLabel
{
    Q_OBJECT
public:
    explicit PointBar(QWidget *parent=nullptr);

    void setPointNum(int now, int end, int max);
    void setPointStatus(int);
    void setPointNowNum(int now);
    void setPointEndNum(int end);
    void setPointMaxNum(int max);
protected:
    void paintEvent(QPaintEvent *) override;

private:
    int maxNum=1;
    int lastMaxNum=1;
    int nowNum=1;
    int status=pointStatus::hp;
};

#endif // POINTBAR_H
