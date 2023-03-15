#ifndef ROOMWIDGET_H
#define ROOMWIDGET_H

#include <QWidget>
#include "globalhead.h"
#include "showWidget/npcform.h"
#include <QVBoxLayout>

namespace Ui {
class RoomWidget;
}

class RoomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RoomWidget(QWidget *parent = nullptr);
    ~RoomWidget();

    ///清空 layout  界面  初始化nowClickNum
    void clearWidget();
    ///清空layout
    void clearLayout();
    ///已有保存数据，设置layout  界面
    void setWidger(roomInfo*infoList);
    ///已有保存数据，设置layout
    void seNpcList(roomInfo*infoList);

    ///将layout中npc数据保存
    void getNpcList(roomInfo*infoList);

    ///将房间数据保存
    void getRoomIfo(roomInfo*infoList);


    ///获取房间出口
    QString getRoomout();
    ///获取房间实际出口
    QString getRoomnowout();
    ///现在被选中的控件是第几房间
    int nowClickNum=-1;
private slots:
    void on_checkRoomName_clicked();

    //检查第一区域简拼是否重复
    void on_checkFirstEN_clicked();

private:
    Ui::RoomWidget *ui;
    QVBoxLayout* npcLayout;
    //QList<NPCForm*> npclist;
};

#endif // ROOMWIDGET_H
