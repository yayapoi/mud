#include "regclass.h"
#include <QRegularExpression>
#include <QDebug>

RegClass::RegClass(QObject *parent)
    : QObject{parent}
{
    RegPtr* newReg=new RegPtr;
    //newReg->oneReg.regStr="^#([A-Za-z0-9.-]+)(?:,([A-Za-z0-9.-]+))*\\r\\n#([A-Za-z0-9.-]+)(?:,([A-Za-z0-9.-]+))*\\r\\n#([A-Za-z0-9.-]+)(?:,([A-Za-z0-9.-]+))*\\r\\n$";
    newReg->oneReg.regStr="^#([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+)\\r\\n#([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+)\\r\\n#([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+)\\r\\n$";
    newReg->oneReg.regName="123";
    newReg->oneReg.row=3;

    QMap<QString, RegPtr*>* qqqqq=new QMap<QString, RegPtr*>;
    qqqqq->insert(newReg->oneReg.regName,newReg);
    regMap.insert(newReg->oneReg.parent,qqqqq);
}

void RegClass::getMessage(QByteArray inArray)
{
    //循环获取每行
    //消息list中加入最新的一行
    //遍历所有触发器行数+1
    //循环触发器
    //if（开启定时器）
    //有几行，拼凑
    //触发
    //if（成功）
    //{
    //if（多次触发）
    //{截取字符串，再次触发，循环递归}
    //else
    //{更新行数}
    //}
    //else
    //{
    //更新行数
    //}

    QString testStr(inArray);
    //qDebug()<<lowNum++<<"****"<<testStr;
    //qDebug()<<lowNum++<<"****"<<backArray;

    while (inArray.size()>0) {//循环截取出要打印的字符串  一行的那种
        QByteArray oneStr;
        getOneStrFromArray(inArray, oneStr);//截取出要打印的字符串  一行的那种
        {
            //消息list中加入最新的一行
            messageList.push_front(oneStr);
            //遍历所有触发器行数+1
            /*for(int Num=0; Num<regList.size(); Num++)
            {
                regList[Num].row++;
            }*/
            QMap<QString, QMap<QString, RegPtr*>*>::const_iterator firstMap = regMap.constBegin();
            while (firstMap != regMap.constEnd()) {
                QMap<QString, RegPtr*>::const_iterator secondMap = firstMap.value()->constBegin();
                while (secondMap != firstMap.value()->constEnd()) {
                    secondMap.value()->row++;
                    ++secondMap;
                }
                ++firstMap;
            }

            //循环触发器
            firstMap = regMap.constBegin();
            while (firstMap != regMap.constEnd()) {
                QMap<QString, RegPtr*>::const_iterator secondMap = firstMap.value()->constBegin();
                while (secondMap != firstMap.value()->constEnd()) {
                    getregfromList(secondMap.value());
                    ++secondMap;
                }
                ++firstMap;
            }
        }
    }
}

void RegClass::newReg(RegStr inReg)
{
    QMap<QString, QMap<QString, RegPtr*>*>::const_iterator firstMap = regMap.find(inReg.parent);
    if(firstMap!=regMap.end())//主分类存在
    {
        QMap<QString, RegPtr*>* secondMap=firstMap.value();
        QMap<QString, RegPtr*>::const_iterator secondMapIter = secondMap->find(inReg.regName);
        if(secondMapIter!=secondMap->end())//该名字存在
        {
            secondMapIter.value()->oneReg=inReg;
        }
        else//该名字不存在
        {
            RegPtr* newReg=new RegPtr;
            newReg->oneReg=inReg;
            secondMap->insert(inReg.regName,newReg);
        }
    }
    else//主分类不存在
    {
        QMap<QString, RegPtr*>* secondMap=new QMap<QString, RegPtr*>;
        RegPtr* newReg=new RegPtr;
        newReg->oneReg=inReg;
        secondMap->insert(inReg.regName,newReg);
        regMap.insert(inReg.parent,secondMap);
    }
}

void RegClass::deleteReg(RegStr inReg)
{
    deleteReg(inReg.parent, inReg.regName);
}

void RegClass::deleteReg(QString &parentName, QString &itemName)
{
    QMap<QString, QMap<QString, RegPtr*>*>::const_iterator firstMap = regMap.find(parentName);
    if(firstMap!=regMap.end())//主分类存在
    {
        QMap<QString, RegPtr*>* secondMap=firstMap.value();
        QMap<QString, RegPtr*>::const_iterator secondMapIter = secondMap->find(itemName);
        if(secondMapIter!=secondMap->end())//该名字存在
        {
            RegPtr* asdf=secondMapIter.value();
            secondMap->remove(itemName);
            delete asdf;
        }
    }
    firstMap = regMap.begin();
    QStringList deleteList;
    while (firstMap!=regMap.end()) {
        if(firstMap.value()->size()==0)
        {
            deleteList.append(firstMap.key());
            delete firstMap.value();
        }
        firstMap++;
    }
    while (!deleteList.isEmpty()) {
        QString firstStr=deleteList.first();
        regMap.remove(firstStr);
        deleteList.pop_front();
    }
}

void RegClass::changeReg(RegStr oldReg, RegStr newreg)
{
    deleteReg(oldReg);
    newReg(newreg);
}

bool RegClass::openOrCloseReg(QString &parentName, QString &itemName, bool &flag)
{
    bool backflag=false;
    QMap<QString, QMap<QString, RegPtr*>*>::const_iterator firstMap = regMap.find(parentName);
    if(firstMap!=regMap.end())//主分类存在
    {
        QMap<QString, RegPtr*>* secondMap=firstMap.value();
        QMap<QString, RegPtr*>::const_iterator secondMapIter = secondMap->find(itemName);
        if(secondMapIter!=secondMap->end())//该名字存在
        {
            secondMapIter.value()->oneReg.enable=flag;
            backflag=true;
        }
        else//该名字不存在
        {
            backflag=false;
        }
    }
    else//主分类不存在
    {
        backflag=false;
    }
    return backflag;
}

bool RegClass::regIsEmpty(RegStr &checkReg)
{
    bool flag=regIsEmpty(checkReg.parent, checkReg.regName);
    return flag;
}

bool RegClass::regIsEmpty(QString &parentName, QString &itemName)
{
    bool flag=false;
    QMap<QString, QMap<QString, RegPtr*>*>::const_iterator firstMap = regMap.find(parentName);
    if(firstMap!=regMap.end())//主分类存在
    {
        QMap<QString, RegPtr*>* secondMap=firstMap.value();
        QMap<QString, RegPtr*>::const_iterator secondMapIter = secondMap->find(itemName);
        if(secondMapIter!=secondMap->end())//该名字存在
        {
            flag=true;
        }
        else//该名字不存在
        {
            flag=false;
        }
    }
    else//主分类不存在
    {
        flag=false;
    }
    return flag;
}

void RegClass::newRegStr(QString)
{
    RegStr testReg;
    newReg(testReg);
}

void RegClass::openOrCloseRegStr(QString)
{
    //
}

void RegClass::getOneStrFromArray(QByteArray &inArray, QByteArray &outArray)
{
    bool findStr=false;//找到回车换行
    int charNum=0;//没找到回车换行，但是到尾部了
    for(; charNum<inArray.size()-1; charNum++)
    {
        if(uchar(inArray[charNum])==0x0D && uchar(inArray[charNum+1])==0x0A)
        {
            findStr=true;
            charNum++;
            break;
        }
    }

    if(findStr)//找到回车换行
    {
        outArray=inArray.mid(0, charNum+1);
        inArray=inArray.mid(charNum+1);
        //qDebug()<<"outArray--"<<QString(outArray)<<"  backArray--"<<QString(backArray);
    }
    else
    {
        if(charNum+1 == inArray.size())//没找到回车换行，但是到尾部了
        {
            outArray=inArray;
            inArray=inArray.mid(charNum+1);
            //qDebug()<<"outArray--"<<QString(outArray)<<"  backArray--"<<QString(backArray);
        }
        else
        {
            //qDebug()<<"error  backArray--"<<QString(backArray);
        }
    }
}

void RegClass::getregfromList(RegPtr *Reg)
{
    if(Reg->oneReg.enable==true)//开启触发器
    {
        if(Reg->oneReg.row<=messageList.size())
        {
            QByteArray regArray;
            for(int Num=Reg->oneReg.row-1; Num>-1; Num--)
            {
                regArray.append(messageList[Num]);
            }
            regFromArray(regArray, Reg);
        }
    }
}

void RegClass::regFromArray(QByteArray &inArray, RegPtr *Reg)
{
    //有几行，拼凑
    //触发
    //if（成功）
    //{
    //if（多次触发）
    //{截取字符串，再次触发，循环递归}
    //else
    //{更新行数}
    //}
    //else
    //{
    //更新行数
    //}
    int index=0;
    //qDebug()<<"RegClass::regFromArray--"<<inArray;
    while(index<inArray.size())
    {
        QRegularExpression regStr(Reg->oneReg.regStr);
        QRegularExpressionMatch regularmatch=regStr.match(inArray, index);
        if(regularmatch.hasMatch())
        {
            QByteArray checkStr=regularmatch.captured(0).toUtf8();
            int row= -1, beginPoint= -1, length= -1;
            getAllFromArray(inArray, checkStr, Reg->oneReg.row, row, beginPoint, length);
            //qDebug()<<"checkStr--"<<checkStr;
            if(row<Reg->row || (row=Reg->row && ((beginPoint>Reg->beginPoint) ||(beginPoint=Reg->beginPoint && length>Reg->strLength))))//有效匹配，判断是否循环
            {
                Reg->row=row;
                Reg->beginPoint=beginPoint;
                Reg->strLength=length;
                //获取正常的结果 须填
                if(Reg->oneReg.oneStrOneReg)//最新数据只匹配一次
                {
                    //qDebug()<<"Reg->oneReg.oneStrOneReg true";
                    sendAllMessage(regularmatch, Reg);
                    break;
                }
                else//最新数据可匹配多次
                {
                    sendAllMessage(regularmatch, Reg);
                    //qDebug()<<"Reg->oneReg.oneStrOneReg false";
                    index=inArray.indexOf(checkStr)+checkStr.length();
                }
            }
            else//无效匹配，删除并开始再次判断
            {
                //qDebug()<<"row<Reg->row || (row=Reg->row && ((beginPoint>Reg->beginPoint) ||(beginPoint=Reg->beginPoint && leng";
                index=inArray.indexOf(checkStr)+checkStr.length();
            }
        }
        else
        {
            //qDebug()<<"regularmatch.hasMatch() false";
            break;
        }
    }
}

void RegClass::getAllFromArray(QByteArray &inArray, QByteArray &regArray, int maxrow, int &row, int &beginPoint, int &length)
{
    if(maxrow==1)
    {
        row=0;
        beginPoint=inArray.indexOf(regArray);
        length=regArray.size();
    }
    else
    {
        int arrayBegin=inArray.indexOf(regArray);
        int maxNum=arrayBegin+regArray.length();
        bool findKey=false;
        for(int Num=0; Num<maxNum; Num++)
        {
            if(Num<=arrayBegin)
            {
                beginPoint=arrayBegin;
                length=0;
            }
            if(findKey)
            {
                findKey=false;
                row++;
                beginPoint=0;
                length=0;
            }
            if(inArray[Num]=='\n')
            {
                findKey=true;
            }
            length++;
        }
        row=maxrow-row;
        //qDebug()<<"row--"<<row;
        //qDebug()<<"beginPoint--"<<beginPoint;
        //qDebug()<<"length--"<<length;
    }
}

void RegClass::sendAllMessage(QRegularExpressionMatch &matchReg, RegPtr *Reg)
{
    if(Reg->oneReg.sysOrUser)
    {
        if(Reg->oneReg.sysStr=="hp")
        {
            QStringList backList=matchReg.capturedTexts();
            backList.pop_front();
            //qDebug()<<"backList--"<<backList;
            emit getHp(backList);
        }
    }
    else
    {
        //须填
    }
}

void RegClass::getNewRegFromStr(QString &inStr, RegStr &backReg)
{
    {
        QString regStr="";//触发正则
        int coldTime=0;//冷却时间？
        QString color=0;//颜色触发？
        QString parent="默认分组";//名字唯一
        QString regName="";//组内唯一
        int row=1;//这个触发器用户想让他匹配几行
        bool oneStrOneReg=true;//一行仅触发一次
        bool enable=true;

        bool sysOrUser=true;//用户类则使用端口，系统类则使用关键词
        int port=8080;//用户指定触发成功后发送给哪个tcp端口
        QString sysStr="hp";
    }//类，名字，触发，匹配行，是否开启，
    QRegularExpression regStr("#newReg\(\"([\s\S]+)\",\"([\s\S]+)\",\"([\s\S]+)\",\)");
    QRegularExpressionMatch regularmatch=regStr.match(inArray, index);
    if(regularmatch.hasMatch())
    {
        QByteArray checkStr=regularmatch.captured(0).toUtf8();
        int row= -1, beginPoint= -1, length= -1;
        getAllFromArray(inArray, checkStr, Reg->oneReg.row, row, beginPoint, length);
        //qDebug()<<"checkStr--"<<checkStr;
        if(row<Reg->row || (row=Reg->row && ((beginPoint>Reg->beginPoint) ||(beginPoint=Reg->beginPoint && length>Reg->strLength))))//有效匹配，判断是否循环
        {
            Reg->row=row;
            Reg->beginPoint=beginPoint;
            Reg->strLength=length;
            //获取正常的结果 须填
            if(Reg->oneReg.oneStrOneReg)//最新数据只匹配一次
            {
                //qDebug()<<"Reg->oneReg.oneStrOneReg true";
                sendAllMessage(regularmatch, Reg);
                break;
            }
            else//最新数据可匹配多次
            {
                sendAllMessage(regularmatch, Reg);
                //qDebug()<<"Reg->oneReg.oneStrOneReg false";
                index=inArray.indexOf(checkStr)+checkStr.length();
            }
        }
        else//无效匹配，删除并开始再次判断
        {
            //qDebug()<<"row<Reg->row || (row=Reg->row && ((beginPoint>Reg->beginPoint) ||(beginPoint=Reg->beginPoint && leng";
            index=inArray.indexOf(checkStr)+checkStr.length();
        }
    }
    else
    {
        //qDebug()<<"regularmatch.hasMatch() false";
        break;
    }
}
