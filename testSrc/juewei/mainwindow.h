#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegularExpression>
#include "lurenui.h"
#include <QTcpSocket>
#include <tcpprotocoltrans.h>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTcpSocket clientSocket;
    TcpProtocolTrans* privateTrans;
    QFile* messageFile;
private slots:
    void on_qingkong_clicked();

    void on_kaishi_clicked();

    /** @brief 爵位人物描述*/
    void xieru(QString RegStr, QJsonArray&);

    /** @brief 每个人证据*/
    void xinxi(QString RegStr, QJsonArray&);

    /** @brief 接任务啦*/
    void lingrenwu(QString RegStr, QJsonArray& value);

    void on_connectbt_clicked();

private:
    Ui::MainWindow *ui;//\u001B[([0-9]*)m([\s\S]*?)\u001B[(?:[\s\S]*?)m脚蹬一双\u001B[([0-9]*)m([\s\S]*?)\u001B[(?:[\s\S]*?)m
    //QRegularExpression miaoshuRegular{"^(?:[ \\f\\t\\v\\S]*?)LV(?:[ \\f\\t\\v\\S]*?)\\n(?:[ \\f\\t\\v\\S]*)0m([ \\f\\t\\v\\S]*?)\\((?:[ \\f\\t\\v\\S]*?)\\n(?:[ \\f\\t\\v\\S]*?)[他她]看起来约([\\s\\S]*?)多岁(?:[\\s\\S]*?)这是一[位个]([\\s\\S]*?)的行人(?:[\\s\\S]*?)身穿一件([\\s\\S]*?)\((?:[\\s\\S]*?)脚蹬一双([\\s\\S]*?)\\("};
    QRegularExpression miaoshuRegular{"^(?:[ \\f\\t\\v\\S]*?)LV(?:[ \\f\\t\\v\\S]*?)\\n(?:[ \\f\\t\\v\\S]*)0m([ \\f\\t\\v\\S]*?)\\((?:[ \\f\\t\\v\\S]*?)\\n(?:[ \\f\\t\\v\\S]*?)([他她])看起来约([\\s\\S]*?)多岁(?:[\\s\\S]*?)这是一[位个]([\\s\\S]*?)的行人(?:[\\s\\S]*?)身穿一件\u001B\\[(?:[0-9]*;)*([0-9]*)m([\\s\\S]*?)\u001B\\[(?:[\\s\\S]*?)脚蹬一双\u001B\\[(?:[0-9]*;)*([0-9]*)m([\\s\\S]*?)\u001B\\["};
    QRegularExpression xinxiRegular{"^你向([\\s\\S]*?)问道：这位([\\s\\S]*?)，不知最近有没有听说什么消息？\\n([\\s\\S]*?)说道：「([\\s\\S]*?)」"};

    QMap<QString,oneman*> allman;

    /**
     * @brief 返回衣服或者鞋子颜色
     * @return 深色或浅色
     */
    QString backshenqian(QString);

    /**
     * @brief 返回衣服类型
     * @return 丝绸衣服、布衣或夹袄
     */
    QString backyifu(QString);

    /**
     * @brief 返回鞋子类型
     * @return 靴子、布鞋或凉鞋
     */
    QString backxiezi(QString);

    /**
     * @brief 根据描述返回高低肥瘦 男女
     */
    void backfeishounannv(QString entermiaoshu, QString& nannv, QString& gaodi, QString& feishou);

    /**
     * @brief 根据证据返回关键证词
     */
    void backzhengci(QString enter, QSet<QString> &back);

    /**
     * @brief 传入证词，人物
     * @return true:符合 false:不符合
     */
    bool backzijifuhe(QString tezheng, onemessage* renwu);


    /**
     * @brief 从tcp那边传来的所有东西
     */
    void tcpgetall(QString jsonstr);
};
#endif // MAINWINDOW_H
