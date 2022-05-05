#include "regclass.h"
#include <QRegularExpression>

RegClass::RegClass(QObject *parent)
    : QObject{parent}
{

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
            QMap<QString, QMap<QString, RegPtr*>>::const_iterator firstMap = regMap.constBegin();
            while (firstMap != regMap.constEnd()) {
                QMap<QString, RegPtr*>::const_iterator secondMap = firstMap.value().constBegin();
                while (secondMap != firstMap.value().constEnd()) {
                    secondMap.value()->row++;
                    ++secondMap;
                }
                ++firstMap;
            }

            //循环触发器
            firstMap = regMap.constBegin();
            while (firstMap != regMap.constEnd()) {
                QMap<QString, RegPtr*>::const_iterator secondMap = firstMap.value().constBegin();
                while (secondMap != firstMap.value().constEnd()) {
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

}

void RegClass::deleteReg(RegStr inReg)
{

}

void RegClass::changeReg(RegStr oldReg, RegStr newReg)
{

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
                if(Reg->oneReg.oneStrOneReg)
                {
                    break;
                }
                else
                {
                    index=inArray.indexOf(checkStr)+checkStr.length();
                }
            }
            else//无效匹配，删除并开始再次判断
            {
                index=inArray.indexOf(checkStr)+checkStr.length();
            }
        }
        else
        {
            break;
        }
    }
}

void RegClass::getAllFromArray(QByteArray &inArray, QByteArray &regArray, int maxrow, int &row, int &beginPoint, int &length)
{
    /*if(maxrow==1)
    {
        row=0;
        beginPoint=inArray.indexOf(regArray);
        length=regArray.size();
    }
    else
    {
        int index=inArray.indexOf(regArray);
        if(index<inArray.size()-1)
        {
            d
        }
        else
        {
            d
        }
    }*/
}
