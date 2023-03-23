#ifndef CMDCONTROL_H
#define CMDCONTROL_H

#include "qregularexpression.h"
#include <QObject>
#include <QQueue>
#include <QTimer>
#include <QMap>

class CmdControl : public QObject
{
    Q_OBJECT
public:
    explicit CmdControl(QObject *parent = nullptr);

    void appendMessage(QString);
    void appendMessage(QStringList);
    void appendMessage(QByteArray);

    /* @brief 给timer 和阻塞器用的，在命令行前插入命令*/
    void appendMessageFront(QString);
    /* @brief 给timer 和阻塞器用的，解析出所有命令，放入list*/
    void appendMessage(QString, QStringList&);
signals:
    /* @brief 发送命令，附带发送系统函数*/
    void newMessage(QQueue<QString>);
private:
    QQueue<QString> queueList;
    QTimer cmdTimer;
    QMap<QTimer*, QString> timerMap;
    //1ms加一
    int sendmessage=0;

    QRegularExpression regStr{"^#Timer\\((\\d+),\"([\\s\\S]*)\"\\)$"};
private:
    /* @brief 检查是否存在宏，并将宏要替代的东西替换*/
    bool getMessageFrom(QString& inStr, QString& backStr);
    /* @brief 发送命令，同时检查是否系统函数，若是系统函数，则附带发送*/
    void messageToList(QQueue<QString>& backList);
    /* @brief 检查是否系统函数，是则返回0,吞掉则返回1,不是则返回-1*/
    int checkMessage(QString& instr);
    /* @brief 检查是否括号匹配，例如#T(1,"c;#T(1,"c");c");,有完整句子返回句子尾端,没有完整句子返回-1*/
    int backStringIndex(QString& instr, int& from, int& kuohaoend);
    /* @brief 删除最前方空格*/
    void clearBlok(QString& instr);
    /* @brief 开始执行命令*/
    void doqueueList();
};

#endif // CMDCONTROL_H
