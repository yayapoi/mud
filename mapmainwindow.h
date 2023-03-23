#ifndef MAPMAINWINDOW_H
#define MAPMAINWINDOW_H

#include <QMainWindow>
#include "globalhead.h"
#include "qboxlayout.h"
#include "qdatetime.h"
#include "qmenu.h"
#include "qregularexpression.h"
#include "showWidget/goform.h"
#include "configWidget/mapcreateconfigform.h"

namespace Ui {
class MapMainWindow;
}

struct getroomInfo
{
    bool roomnamefind=false;
    bool RoomMessagebegin=false;
    bool RoomMessagefind=false;
    QByteArray RoomMessageArray;
    bool fangxiangfind=false;
    void clear(){
        roomnamefind=false;
        RoomMessagefind=false;
        fangxiangfind=false;
        RoomMessagebegin=false;
        RoomMessageArray.clear();
    }
};

class MapMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapMainWindow(QWidget *parent = nullptr);
    ~MapMainWindow();

    //等待命令结果
    OutInfo waitOut;
    //等待命令结果
    bool waitGo=false;
    GoForm* waitgoForm=nullptr;
    QRegularExpression nameRegStr{"^([\\(\\)a-zA-Z\u4e00-\u9fa5]+?) - [(?: ★)|(?: ☆)]*\\r\\n$"};
    QRegularExpression roomMesBeginRegStr{"^    (?:[*\u4e00-\u9fa5]+)"};
    QRegularExpression roomMesendRegStr{"(?:^\\r\\n)|(?:^    )"};
    QRegularExpression roomoutRegStr{"^    (?:这里[\u4e00-\u9fa5]*的(?:出口|方向)(?:是|有) *(.+)。|浓雾中你[\u4e00-\u9fa5]*觉得似乎[\u4e00-\u9fa5]*通往 *(.+)方向。)\\r\\n$"};
    QRegularExpression nooutRegStr{"^    这里没有任何明显的.*\\w*"};
    QRegularExpression npcReg{"^    ([\u4e00-\u9fa5 「]*?)」*([\u4e00-\u9fa5]+?)\\(([a-zA-Z ]*)\\)"};
    QRegularExpression endReg{"^>"};

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
    ///外部通过那个变量决定要不要传入
    void roomMessage(QByteArray roomMess);
    /* @brief 从输入数组中，截取出一行放入输出数组中*/
    void getOneStrFromArray(QByteArray &inArray, QByteArray &outArray);
    /* @brief 从数组中移除颜色结构*/
    bool removeColorFromArray(QByteArray &inArray);
    /* @brief 检查是否是房间名，true:是房间名*/
    void roomname(QByteArray &inArray);
    /* @brief 检查是否是房间描述*/
    void roommes(QByteArray &inArray);
    /* @brief 检查是否是出口描述*/
    void roomout(QByteArray &inArray);
    /* @brief 检查是否是npc或者结束*/
    void roomnpc(QByteArray &inArray);
    /* @brief 行走系统发送命令了，需要统计时间*/
    void startTime();
    /* @brief 获取roomid*/
    QString getroomID();

    void showEvent(QShowEvent *) override;
    void hideEvent(QHideEvent *) override;
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

    ///假如用户输入命令在出口有，才执行出口中的命令
    void on_cmdLE_returnPressed();

    void on_action_triggered();

private:
    Ui::MapMainWindow *ui;

    QMenu MyMenu;
    QVBoxLayout* fromroomLayout=nullptr;
    QVBoxLayout* toroomLayout=nullptr;

    MapCreateConfigForm configWidget;
    ///刚执行时时间
    QTime begintime;
    bool jishu=true;
    ///房间信息截取到哪里了
    getroomInfo roomifo;
    //测试代码
    ///停止系统，随机时间开始走路
    /*QTimer* starttimer;
    ///返回成功失败，随机时间返回成功失败
    QList<QTimer*> backtimelist;
    ///返回busy，随机时间返回busy
    QList<QTimer*> busytimelist;*/
#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    HINSTANCE dlliter=nullptr;
#else
    void* dlliter=nullptr;
#endif
};

#endif // MAPMAINWINDOW_H
