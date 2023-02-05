#include "regclass.h"
#include <QDebug>

RegClass::RegClass(QObject *parent)
    : QObject{parent}
{
    /*RegPtr* newReg=new RegPtr;//血量触发  自用
    //newReg->oneReg.regStr="^#([A-Za-z0-9.-]+)(?:,([A-Za-z0-9.-]+))*\\r\\n#([A-Za-z0-9.-]+)(?:,([A-Za-z0-9.-]+))*\\r\\n#([A-Za-z0-9.-]+)(?:,([A-Za-z0-9.-]+))*\\r\\n$";
    newReg->oneReg.regStr="^#([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+)\\r\\n#([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+)\\r\\n#([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+)\\r\\n$";
    newReg->oneReg.regName="123";
    newReg->oneReg.sysStr="#setHpBar(\"%1\",\"%2\",\"%3\",\"%4\",\"%5\",\"%6\",\"%7\",\"%8\",\"%9\",\"%10\",\"%11\",\"%12\",\"%13\",\"%14\",\"%15\",\"%16\",\"%17\",\"%18\")";
    newReg->oneReg.row=3;

    RegPtr* fightReg=new RegPtr;//战斗  自用
    //newReg->oneReg.regStr="^#([A-Za-z0-9.-]+)(?:,([A-Za-z0-9.-]+))*\\r\\n#([A-Za-z0-9.-]+)(?:,([A-Za-z0-9.-]+))*\\r\\n#([A-Za-z0-9.-]+)(?:,([A-Za-z0-9.-]+))*\\r\\n$";
    fightReg->oneReg.regStr="流氓头\\(Liumang tou\\)";
    fightReg->oneReg.regName="fight";
    fightReg->oneReg.sysStr="fight liumang tou;look liumang tou";
    fightReg->oneReg.row=1;

    RegPtr* mapReg=new RegPtr;//  自用
    mapReg->oneReg.regStr="你终于完全从紧张地战斗氛围中解脱出来";
    mapReg->oneReg.regName="234";
    mapReg->oneReg.sysStr="#enableReg(\"默认分组\",\"fight\",0);";
    mapReg->oneReg.row=1;

    RegPtr* dontReg=new RegPtr;//  自用
    dontReg->oneReg.regStr="不想跟你较量";
    dontReg->oneReg.regName="345";
    dontReg->oneReg.sysStr="#enableReg(\"默认分组\",\"fight\",0);";
    dontReg->oneReg.row=1;

    RegPtr* tcpReg=new RegPtr;//tcp触发  自用
    tcpReg->oneReg.regStr="^#([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+)\\r\\n#([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+)\\r\\n#([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+)\\r\\n$";
    tcpReg->oneReg.regName="tcp";
    tcpReg->oneReg.row=3;
    tcpReg->oneReg.sysOrUser=false;

    QMap<QString, RegPtr*>* qqqqq=new QMap<QString, RegPtr*>;
    qqqqq->insert(newReg->oneReg.regName,newReg);
    qqqqq->insert(fightReg->oneReg.regName,fightReg);
    qqqqq->insert(mapReg->oneReg.regName,mapReg);
    qqqqq->insert(dontReg->oneReg.regName,dontReg);
    qqqqq->insert(tcpReg->oneReg.regName,tcpReg);

    regMap.insert(newReg->oneReg.parent,qqqqq);*/
}

void RegClass::getMessage(QByteArray inArray)
{
    //循环获取每行
    //消息list中加入最新的一行
    //遍历所有触发器行数+1
    //循环触发器

    //QString testStr(inArray);
    //qDebug()<<"testStr****"<<testStr;
    //qDebug()<<"inArray****"<<inArray;

    while (inArray.size()>0) {//循环截取出要打印的字符串  一行的那种
        QByteArray oneStr;
        getOneStrFromArray(inArray, oneStr);//截取出要打印的字符串  一行的那种
        {
            //qDebug()<<"str=="<<QString(oneStr);
            //qDebug()<<"inArray=="<<oneStr;
            allmessageList.push_front(oneStr);
            if(allmessageList.size()>200)
            {
                allmessageList.pop_back();
            }
            removeColorFromArray(oneStr);
            //qDebug()<<"str=="<<QString(oneStr);
            //qDebug()<<"inArray=="<<oneStr;
            //消息list中加入最新的一行
            messageList.push_front(oneStr);
            if(messageList.size()>200)
            {
                messageList.pop_back();
            }
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

bool RegClass::enableReg(QString &parentName, QString &itemName, bool &flag)
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
            //qDebug()<<"RegClass::enableReg--";
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

void RegClass::newRegStr(QString inStr)
{
    RegStr testReg;
    if(getNewRegFromStr(inStr,testReg))
    {
        newReg(testReg);
    }
}

void RegClass::deleteRegStr(QString inStr)
{
    QString parentName;
    QString RegName;
    if(getDeleteRegFromStr(inStr, parentName, RegName))
    {
        deleteReg(parentName, RegName);
    }
}

void RegClass::changeRegStr(QString)
{
    //未实现，可使用先删，后加的方式实现
}

void RegClass::enableRegStr(QString inStr)
{
    QString parentName;
    QString RegName;
    bool flag;
    if(getEnableRegFromStr(inStr, parentName, RegName, flag))
    {
        enableReg(parentName, RegName, flag);
    }
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
        //qDebug()<<"outArray--"<<QString(outArray)<<"  backArray--"<<outArray;
    }
    else
    {
        if(charNum+1 == inArray.size())//没找到回车换行，但是到尾部了
        {
            outArray=inArray;
            inArray=inArray.mid(charNum+1);
            //qDebug()<<"outArray--"<<QString(outArray)<<"  backArray--"<<outArray;
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
        if(Reg->oneReg.serverText)//颜色触发则用全文模式
        {
            if(Reg->oneReg.row<=allmessageList.size())
            {
                QByteArray regArray;
                for(int Num=Reg->oneReg.row-1; Num>-1; Num--)
                {
                    regArray.append(allmessageList[Num]);
                }
                regFromArray(regArray, Reg);
            }
        }
        else
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
    //qDebug()<<"RegClass::inArray--"<<inArray;
    //qDebug()<<"RegClass::regFromArray--"<<QString(inArray);
    //qDebug()<<"Reg->oneReg.regStr--"<<Reg->oneReg.regStr;
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
                //获取正常的结果
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
    QStringList backList=matchReg.capturedTexts();
    if(Reg->oneReg.sysOrUser)
    {
        backList.pop_front();
        //qDebug()<<"backList--"<<backList;
        QString backStr=Reg->oneReg.sysStr;
        for(int Num=0; Num<backList.size(); Num++)
        {
            backStr = backStr.arg(backList[Num]);
        }
        emit regStrSend(backStr);
    }
    else
    {
        //tcp传输
        emit regStrSendToTcp(Reg->oneReg.port, Reg->oneReg.parent, Reg->oneReg.regName, backList);
    }
}

bool RegClass::getNewRegFromStr(QString &inStr, RegStr &backReg)
{
    bool flag=false;//类string，名字string，触发string，匹配行int，是否开启int，系统或者用户int，端口int，一行仅触一次int,干的事string
    //QString testStr="#newReg(\"lei\",\"name\",\"^#newReg\\(\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",\"([\\s\\S]+?)\",([\\d]+),([\\d]+),([\\d]+),([\\d]+),([\\d]+)\\)$\",3,1,0,8080,1,"aaa")";
    QRegularExpressionMatch regularmatch=NewRegregStr.match(inStr);
    if(regularmatch.hasMatch())
    {
        QStringList backList=regularmatch.capturedTexts();
        if(backList.size()>=9)
        {
            backReg.parent=backList[1];
            backReg.regName=backList[2];
            backReg.regStr=backList[3];
            backReg.row=backList[4].toInt();
            backReg.enable=backList[5].toInt()==1?true:false;
            backReg.sysOrUser=backList[6].toInt()==1?true:false;
            backReg.port=backList[7].toInt();
            backReg.oneStrOneReg=backList[8].toInt()==1?true:false;
            backReg.sysStr=backList[9];
            flag=true;
        }
    }
    else
    {
        //qDebug()<<"getNewRegFromStr.hasMatch() false";
    }
    return flag;
}

bool RegClass::getDeleteRegFromStr(QString &inStr, QString &backParent, QString &backRegName)
{
    bool flag=false;//类string，名字string，触发string，匹配行int，是否开启int，系统或者用户int，端口int，一行仅触一次int
    //QString testStr="#deleteReg(\"asd\",\"asd\")";
    QRegularExpressionMatch regularmatch=DeleteRegregStr.match(inStr);
    if(regularmatch.hasMatch())
    {
        QStringList backList=regularmatch.capturedTexts();
        if(backList.size()>=3)
        {
            backParent=backList[1];
            backRegName=backList[2];
            flag=true;
        }
    }
    else
    {
        //qDebug()<<"getDeleteRegFromStr.hasMatch() false";
    }
    return flag;
}

bool RegClass::getEnableRegFromStr(QString &inStr, QString &backParent, QString &backRegName, bool &backflag)
{
    bool flag=false;//类string，名字string，触发string，匹配行int，是否开启int，系统或者用户int，端口int，一行仅触一次int
    //QString testStr="#enableReg(\"asd\",\"asd\",1)";
    QRegularExpressionMatch regularmatch=enableRegregStr.match(inStr);
    if(regularmatch.hasMatch())
    {
        QStringList backList=regularmatch.capturedTexts();
        if(backList.size()>=4)
        {
            backParent=backList[1];
            backRegName=backList[2];
            backflag=backList[3].toInt()==1?true:false;
            flag=true;
        }
    }
    else
    {
        //qDebug()<<"getenableRegFromStr.hasMatch() false";
    }
    return flag;
}

bool RegClass::removeColorFromArray(QByteArray &inArray)
{
    //QRegularExpression regular{"\\033\\[\\d+(;\\d+)*m"};//去除颜色
    //\x1B
    bool found=false;
    int Num=0;
    while(Num<inArray.size()-1)
    {
        if(inArray[Num]=='\x1B')
        {
            int key=Num+1;
            if(key<inArray.size() && inArray[key]=='[')//\x1B 后必是 [
            {
                key++;
                while(key<inArray.size())
                {
                    if(inArray[key]==';' || ('0'<=inArray[key] && inArray[key]<='9') || inArray[key]=='m')
                    {
                        if(inArray[key]=='m')//M结尾
                        {
                            found=true;
                            break;
                        }
                    }
                    else
                    {
                        found=false;
                        break;
                    }
                    key++;
                }
            }
            if(found)//数组中移除
            {
                inArray.remove(Num,key-Num+1);
                Num--;
            }
        }
        Num++;
    }
    return found;
}

