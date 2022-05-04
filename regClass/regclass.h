#ifndef REGCLASS_H
#define REGCLASS_H

#include <QObject>

/* @brief 用户自定义的触发器*/
struct RegStr
{
    QString regStr="";
    int coldTime=0;
    QString color=0;
    QString parent="默认分组";
    QString regName="";
    int row=1;
    bool oneStrOneReg=true;
};

/* @brief 记录一个触发器，有触发器的已经触发行，开始点，和长度*/
struct RegPtr
{
    RegStr oneReg;
    int row=0;
    int beginPoint=-1;
    int strLength=-1;
};

class RegClass : public QObject
{
    Q_OBJECT
public:
    explicit RegClass(QObject *parent = nullptr);

    /* @brief 从tcp中获取最新的消息，将其分解为一句句话放入链表*/
    void getMessage(QByteArray inArray);
    /* @brief 获取一个新的触发器，加入进来*/
    void newReg(RegStr inReg);
    /* @brief 删除一个触发器*/
    void deleteReg(RegStr inReg);
    /* @brief 改一个触发器*/
    void changeReg(RegStr oldReg, RegStr newReg);
signals:
private:
    QList<QByteArray> messageList;

};

#endif // REGCLASS_H
