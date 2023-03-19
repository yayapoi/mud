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
    ///使用上个房间的
    void uselastname(QString &fzh,QString &fen,QString &szh,QString &sen,QString &srdzh,QString &srden);

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

    ///设置当前房间名，颜色
    void setRoomNC(QString name,QString color);
    ///添加npc到列表
    void appendNpc(QString nameZH,QString nameEN,QString title);
    ///房间描述
    void setroommes(QString roomme);
    ///房间出口 以;分割
    void setroomout(QString roomout);

    void on_checkRoomName_clicked();
private slots:

    //检查第一区域简拼是否重复
    void on_checkFirstEN_clicked();

    void on_FirstZH_textChanged(const QString &arg1);

    void on_secondZH_textChanged(const QString &arg1);

    void on_srdZH_textChanged(const QString &arg1);

private:
    Ui::RoomWidget *ui;
    QVBoxLayout* npcLayout;
    //QList<NPCForm*> npclist;
};

#endif // ROOMWIDGET_H
