#ifndef REGCLASS_H
#define REGCLASS_H

#include <QObject>
#include <QMap>
#include <globalhead.h>
#include <QRegularExpression>

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
    /* @brief 删除一个触发器*/
    void deleteReg(QString& parentName, QString& itemName);

    /* @brief 改一个触发器*/
    void changeReg(RegStr oldReg, RegStr newReg);
    /* @brief 开关一个触发器*/
    bool openOrCloseReg(QString& parentName, QString& itemName, bool& flag);

    /* @brief 检查一个触发器是否存在*/
    bool regIsEmpty(RegStr &checkReg);
    /* @brief 检查一个触发器是否存在*/
    bool regIsEmpty(QString& parentName, QString& itemName);
signals:
    /* @brief 发给命令解析类*/
    void regStrSend(QString);
public slots:
    void newRegStr(QString);
    void deleteRegStr(QString);
    void changeRegStr(QString);
    void openOrCloseRegStr(QString);
private:
    QList<QByteArray> messageList;
    QMap<QString, QMap<QString, RegPtr*>*> regMap;

    /* @brief 从输入数组中，截取出一行放入输出数组中*/
    void getOneStrFromArray(QByteArray &inArray, QByteArray &outArray);
    /* @brief 获取需要触发的文本*/
    void getregfromList(RegPtr* Reg);
    /* @brief 循环截取匹配*/
    void regFromArray(QByteArray &inArray, RegPtr* Reg);
    /* @brief 获取当前匹配到的字符串最晚出现在 第几行 最后位置，最后行的长度*/
    void getAllFromArray(QByteArray &inArray, QByteArray &regArray, int maxrow, int& row, int& beginPoint, int& length);

    /* @brief 当获取到触发信息后，发送给该送的地方*/
    void sendAllMessage(QRegularExpressionMatch& matchReg, RegPtr *Reg);

    /* @brief 从字符串中获取新增触发器的属性*/
    bool getNewRegFromStr(QString& inStr, RegStr &backReg);
    /* @brief 从字符串中获取删除触发器的名字和类*/
    bool getDeleteRegFromStr(QString& inStr, QString& backParent, QString& backRegName);
    /* @brief 从字符串中获取开关触发器的名字 类 状态*/
    bool getOpenOrCloseRegFromStr(QString& inStr, QString& backParent, QString& backRegName, bool& flag);

    /* @brief 从数组中移除颜色结构*/
    bool removeColorFromArray(QByteArray &inArray);
};

#endif // REGCLASS_H
