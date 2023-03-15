#ifndef MAPMAINWINDOW_H
#define MAPMAINWINDOW_H

#include <QMainWindow>
#include "globalhead.h"
#include "qboxlayout.h"
#include "qdatetime.h"
#include "qmenu.h"
#include "showWidget/goform.h"

namespace Ui {
class MapMainWindow;
}

class MapMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapMainWindow(QWidget *parent = nullptr);
    ~MapMainWindow();

    //等待命令结果
    OutInfo waitOut;
    bool waitGo=false;
    GoForm* waitgoForm=nullptr;

    ///传入房间号，初始化界面
    void setWidget(int roomNum);
    ///清空fromRoom  layout
    void clearFromRoom();
    ///清空toRoom  layout
    void clearToRoom();

    ///注册toRoom  layout
    void initToRoom();
    ///注册fromRoom  layout
    void initFromRoom();

    ///现在被选中的控件是第几房间
    int nowClickNum=-1;

    ///记录下最新的区域，若没有区域，则自动填充进
    void upRoomZhEn(int);
    QString fZH;
    QString fEn;
    QString sZH;
    QString sEn;
    QString srdZH;
    QString srdEh;
    ///更新from房间
    void updateFrom(roomInfo*);
    ///更新to房间
    void updateTo(roomInfo*);

    ///到一个房间有俩路径，应该不行, true:有俩出口房间同名
    bool checkTo();

    ///点击go成功
    void GoSuccess();

    ///预测出口
    void calculateTo();

    void mouseReleaseEvent(QMouseEvent *event) override;
signals:
    void mapCreateCmd(QString cmd);
private slots:
    void on_lookRoomBT_clicked();

    void on_saveRoomBT_clicked();

    void on_openMap_triggered();

    void on_saveMap_triggered();

    void on_adddll_triggered();

    void on_deleteDLL_triggered();

private:
    Ui::MapMainWindow *ui;

    QMenu MyMenu;
    QVBoxLayout* fromroomLayout=nullptr;
    QVBoxLayout* toroomLayout=nullptr;

    ///刚执行时时间
    QTime begintime;
    bool jishu=true;
    /*测试代码
    ///停止系统，随机时间开始走路
    QTimer* starttimer;
    ///返回成功失败，随机时间返回成功失败
    QList<QTimer*> backtimelist;*/
#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    HINSTANCE dlliter=nullptr;
#else
    void* dlliter=nullptr;
#endif
};

#endif // MAPMAINWINDOW_H
