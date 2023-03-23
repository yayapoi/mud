#ifndef CMDDO_H
#define CMDDO_H

#include <QObject>
#include <QQueue>

class CmdDo : public QObject
{
    Q_OBJECT
public:
    explicit CmdDo(QObject *parent = nullptr);

signals:
    /* @brief 发送给触发类*/
    void newRegStr(QString);
    /* @brief 发送给触发类*/
    void deleteRegStr(QString);
    /* @brief 发送给触发类*/
    void enableRegStr(QString);

    /* @brief 发送给服务器*/
    void sendToServer(QString);

    /* @brief 发送给显示界面*/
    void cmdShowInWindow(QString);

    /* @brief 发送给主界面显示并触发*/
    void pritf(QString);

    /* @brief 发送给血条*/
    void setHPBar(QString);

    /* @brief 发送给行走系统 解析并使用路径*/
    void Path(QString);
    /* @brief 发送给行走系统 暂停*/
    void Pause();
    /* @brief 发送给行走系统 继续*/
    void Walk();
    /* @brief 发送给行走系统 行走room校验*/
    void MoveRoom(QString);
    /* @brief 发送给行走系统 行走gmcp校验*/
    void MoveGMCP(QString);

    /* @brief 发送给战斗系统 kill npc*/
    void KillSomeNpc(QString);
public slots:
    /* @brief 收到命令，附带有系统函数*/
    void newMessage(QQueue<QString>);

private:
    /* @brief 检查是否系统函数，是则使用并返回true*/
    bool checkMessage(QString& instr);

};

#endif // CMDDO_H
