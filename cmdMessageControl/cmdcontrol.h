#ifndef CMDCONTROL_H
#define CMDCONTROL_H

#include <QObject>
#include <QQueue>
#include <QTimer>

class CmdControl : public QObject
{
    Q_OBJECT
public:
    explicit CmdControl(QObject *parent = nullptr);

    void appendMessage(QString);
    void appendMessage(QStringList);
    void appendMessage(QByteArray);
signals:
    /* @brief 发送命令，附带发送系统函数*/
    void newMessage(QQueue<QString>);
private:
    QQueue<QString> queueList;
    QTimer cmdTimer;

private:
    /* @brief 检查是否存在宏，并将宏要替代的东西替换*/
    bool getMessageFrom(QString& inStr, QString& backStr);
    /* @brief 发送命令，同时检查是否系统函数，若是系统函数，则附带发送*/
    void messageToList(QQueue<QString>& backList);
    /* @brief 检查是否系统函数，是则返回true*/
    bool checkMessage(QString& instr);
};

#endif // CMDCONTROL_H
