#ifndef REGCLASS_H
#define REGCLASS_H

#include <QObject>
#include <QMap>

/* @brief 用户自定义的触发器*/
struct RegStr
{
    QString regStr="";//触发正则
    int coldTime=0;//冷却时间？
    QString color=0;//颜色触发？
    QString parent="默认分组";//名字唯一
    QString regName="";//组内唯一
    int row=1;//这个触发器用户想让他匹配几行
    bool oneStrOneReg=true;//一行仅触发一次
    bool enable=true;
};

/* @brief 记录一个触发器，有触发器的已经触发行，开始点，和长度*/
struct RegPtr
{
    RegStr oneReg;
    int row=0;//这个触发器在第几行已经触发过了
    int beginPoint=-1;//在第几号位触发了
    int strLength=-1;//触发长度
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
    QMap<QString, QMap<QString, RegPtr*>> regMap;

    /* @brief 从输入数组中，截取出一行放入输出数组中*/
    void getOneStrFromArray(QByteArray &inArray, QByteArray &outArray);
    /* @brief 获取需要触发的文本*/
    void getregfromList(RegPtr* Reg);
    /* @brief 循环截取匹配*/
    void regFromArray(QByteArray &inArray, RegPtr* Reg);
    /* @brief 获取当前匹配到的字符串最晚出现在 第几行 最后位置，最后行的长度*/
    void getAllFromArray(QByteArray &inArray, QByteArray &regArray, int maxrow, int& row, int& beginPoint, int& length);
};

#endif // REGCLASS_H
