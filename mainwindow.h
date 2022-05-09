#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qtcpsocket.h>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include "zlib.h"
#include <qfile.h>
#include <regClass/regclass.h>
#include <cmdMessageControl/cmddo.h>
#include <cmdMessageControl/cmdcontrol.h>

/*
 * MCCP2 协议

MCCP2 是一种压缩协议，它允许 MUD 服务器使用 zlib 压缩库将输出压缩到接收客户端。这通常会将服务器使用的带宽量减少 75% 到 90%。
MCCP2 实现为 Telnet 选项RFC854、RFC855。服务器和客户端协商 MCCP2 的使用，就像他们使用任何其他 telnet 选项一样。一旦就选项的使用达成一致，就使用选项子协商来开始压缩。

服务器命令
IAC WILL MCCP2 表示服务器支持 MCCP2。

客户端命令
IAC DO MCCP2 表示客户端支持 MCCP2。
IAC DONT MCCP2 表示客户端不支持 MCCP2。
                    如果服务器启用了压缩，它应该禁用它。

握手
当客户端连接到服务器时，服务器应发送 IAC WILL MCCP2。客户端应使用 IAC DO MCCP2 或 IAC DONT MCCP2 进行响应。如果服务器收到 IAC DO MCCP2，它应该响应：IAC SB MCCP2 IAC SE，然后立即开始压缩数据。

MCCP2 定义
MCCP2 86

压缩格式
在服务器发送 IAC SB MCCP2 IAC SE 之后，服务器应该立即创建一个 zlib 流RFC1950。
一旦建立压缩，所有服务器端通信，包括远程登录协商，都在压缩流中进行。
服务器可以在任何时候通过发送一个有序的流结束（Z_FINISH）来终止压缩。在此之后，连接继续作为正常的 telnet 连接。

压缩错误
如果客户端zlib报解压错误，客户端可以停止解压并发送IAC DONT MCCP2. 反过来，服务器应在收到 IAC DONT MCCP2 后禁用压缩，连接继续作为正常的 telnet 连接。
或者，客户端可以在检测到流错误时关闭连接。
*/

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_cmdLE_returnPressed();

    void on_toolButton_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *testSocket=nullptr;

    //发送客户端内容至服务器，若需要压缩，则压缩
    void socketWrite(QString);
    //检查字符串中是否有协议，有协议则发送接受mccp2，若接受mccp2后，则解压后判断，停止也应该解压后发送停止
    void checkStr(QByteArray);
    /* @brief 检查解压的大小，决定输出数组的大小*/
    int checkOutSize(int);

    z_stream mZstream;
    bool compressed=false;
    QByteArray zbuffer;
    QByteArray backArray;
    /*@brief 上次没有处理完的非一行数据*/
    QByteArray halfStrArray;
    z_stream zstrm;
    QByteArray zout;
    int zoutSize=10000;//废弃
    int lowNum=0;
    bool tsetadf=false;

    RegClass testRegClass;
    CmdDo cmdDo;
    CmdControl cmdControl;
    QFile* messageFile;
    //QRegularExpression *regular=nullptr;//使用下面的正则表达式，不使用这段 ***
};

#endif // MAINWINDOW_H
