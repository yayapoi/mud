#include "mainwindow.h"
#include "globalhead.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

enum NanDu{
    jiandan=0,
    putong=1,
    tiaozhan=2,
    kunnan=4
};
struct jueweiRenwuXinxi{
    QString bianhao;
    QString renwu;
    int nandu=NanDu::jiandan;
};
int nandu(QString nandu)
{
    if(nandu=="简单")
    {
        return NanDu::jiandan;
    }
    else if(nandu=="普通")
    {
        return NanDu::putong;
    }
    else if(nandu=="挑战")
    {
        return NanDu::tiaozhan;
    }
    else
    {
        return NanDu::kunnan;
    }
}
bool operator<(const jueweiRenwuXinxi& A, const jueweiRenwuXinxi& B) {//小于
    bool backbool=true;
    switch (A.nandu) {
    case NanDu::jiandan:
    {
        switch (B.nandu) {
        case NanDu::jiandan:
        {
            backbool=false;
            break;
        }
        case NanDu::putong:
        {
            backbool=true;
            break;
        }
        case NanDu::tiaozhan:
        {
            backbool=true;
            break;
        }
        case NanDu::kunnan:
        {
            backbool=true;
            break;
        }
        }
        break;
    }
    case NanDu::putong:
    {
        switch (B.nandu) {
        case NanDu::jiandan:
        {
            backbool=false;
            break;
        }
        case NanDu::putong:
        {
            backbool=false;
            break;
        }
        case NanDu::tiaozhan:
        {
            backbool=true;
            break;
        }
        case NanDu::kunnan:
        {
            backbool=true;
            break;
        }
        }
        break;
    }
    case NanDu::tiaozhan:
    {
        switch (B.nandu) {
        case NanDu::jiandan:
        {
            backbool=false;
            break;
        }
        case NanDu::putong:
        {
            backbool=false;
            break;
        }
        case NanDu::tiaozhan:
        {
            backbool=false;
            break;
        }
        case NanDu::kunnan:
        {
            backbool=true;
            break;
        }
        }
        break;
    }
    case NanDu::kunnan:
    {
        switch (B.nandu) {
        case NanDu::jiandan:
        {
            backbool=false;
            break;
        }
        case NanDu::putong:
        {
            backbool=false;
            break;
        }
        case NanDu::tiaozhan:
        {
            backbool=false;
            break;
        }
        case NanDu::kunnan:
        {
            backbool=false;
            break;
        }
        }
        break;
    }
    }
    return backbool;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    messageFile=new QFile("D:/renwumiaoshu.txt");
    if(messageFile->open(QIODevice::Append | QIODevice::WriteOnly))
    {
        //qDebug()<<"open";
    }
    privateTrans=new TcpProtocolTrans;
    connect(&clientSocket, &QTcpSocket::connected,this,[=](){
        qDebug()<<"成功和服务器建立好连接";
        //clientSocket.write("#newReg(\"爵位\",\"人物描述\",\"^#([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+)\\r\\n#([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+)\\r\\n#([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+),([A-Za-z0-9.-]+)\\r\\n$\",3,1,0,2323,1)");
    });

    //因为tcpSocket已经分配了空间，有指向，所以可以放在外面

    connect(&clientSocket, &QTcpSocket::readyRead,this,[=](){
        //获取对方发送的内容
        QByteArray array = clientSocket.readAll();
        qDebug() << "QTcpSocket::readyRead  array--"<<array;
        QList<QString> backList;
        privateTrans->tcpToRegStr(array, backList);
        if(!backList.empty())
        {
            qDebug() << "QTcpSocket::readyRead  backList--"<<backList;
            tcpgetall(backList[0]);
        }
    });
}

MainWindow::~MainWindow()
{
    if(messageFile!=nullptr)
    {
        messageFile->close();
    }
    delete ui;
}


void MainWindow::on_qingkong_clicked()
{
    QMap<QString,oneman*>::Iterator allmaniter=allman.begin();
    while (ui->tabWidget->count()!=0) {
        ui->tabWidget->removeTab(0);
    }
    while(allmaniter!=allman.end())
    {
        if(allmaniter.value()->onemessage!=nullptr)
        {
            delete allmaniter.value()->onemessage;
        }
        if(allmaniter.value()->showWidget!=nullptr)
        {
            allmaniter.value()->showWidget->deleteLater();
        }
        if(allmaniter.value()->zhengcimessage!=nullptr)
        {
            delete allmaniter.value()->zhengcimessage;
        }
        delete allmaniter.value();
        allmaniter++;
    }
    allman.clear();
    messageFile->write("\r\n==================================\r\n");
    messageFile->write("\r\n\r\n\r\n");
    //qDebug()<<":on_qingkong_clicked--"<<allman.count();
}


void MainWindow::on_kaishi_clicked()
{
    QMap<QString,oneman*>::Iterator allmaniter=allman.begin();
    while(allmaniter!=allman.end())
    {
        if(allmaniter.value()->zhengcimessage!=nullptr)
        {
            for(QString zhengci:allmaniter.value()->zhengcimessage->zhengciList)
            {
                if(backzijifuhe(zhengci,allmaniter.value()->onemessage))//自己提供特征X，而自身符合特征X，则自己不是盗贼，特征X为真。
                {
                    allmaniter.value()->daozei=false;
                }
                //遍历路人，不符合这个证词的都不是盗贼
                QMap<QString,oneman*>::Iterator seciter=allman.begin();
                while(seciter!=allman.end())
                {
                    if(seciter.value()->onemessage!=nullptr && seciter.value()!=allmaniter.value())
                    {
                        if(backzijifuhe(zhengci,seciter.value()->onemessage)==false)//自己提供特征X，而自身符合特征X，则自己不是盗贼，特征X为真。
                        {
                            //qDebug()<<"mingzi--"<<seciter.key()<<"  zhengci--"<<zhengci;
                            seciter.value()->daozei=false;
                        }
                    }
                    seciter++;
                }
            }
        }
        allmaniter++;
    }

    allmaniter=allman.begin();
    ui->lineEdit->clear();
    QString daozeo;
    while(allmaniter!=allman.end())
    {
        //qDebug()<<"name--"<<allmaniter.key()<<"  daozhe--"<<allmaniter.value()->daozei;
        if(allmaniter.value()->daozei==true)
        {
            daozeo=daozeo+"  "+allmaniter.key();
        }
        allmaniter++;
    }
    ui->lineEdit->setText(daozeo);
    messageFile->write("\r\n");
    messageFile->write(daozeo.toUtf8());
    messageFile->write("\r\n");
}


void MainWindow::xieru(QString RegStr, QJsonArray& allmiaoshu)
{
    qDebug()<<"MainWindow::xieru()  asdf--"<<allmiaoshu;
    //qDebug()<<"("<<regularmatch.capturedStart()<<","<<index<<")"<<regularmatch.captured(0);
    //int end=regularmatch.capturedEnd();
    //int start=regularmatch.capturedStart();
    //QString checkStr=regularmatch.captured(0);
    //qDebug()<<"old checkStr--"<<checkStr;
    //checkStr.remove(QRegularExpression("\\033\\["));
    //inArray.remove(regularmatch.capturedStart(),regularmatch.capturedEnd()-regularmatch.capturedStart());
    //qDebug()<<"start--"<<start<<"  end--"<<end<<"  new checkStr--"<<checkStr<<"  inArray--"<<inArray;
    QString name=allmiaoshu[0].toString();
    QString nannv=allmiaoshu[1].toString();
    QString nianling=allmiaoshu[2].toString();
    QString gaodi;
    QString feishou;
    QString yifuyanse=backshenqian(allmiaoshu[4].toString())+"衣服";
    QString yifu=backyifu(allmiaoshu[5].toString());
    QString xieziyanse=backshenqian(allmiaoshu[6].toString())+"鞋子";
    QString xiezi=backxiezi(allmiaoshu[7].toString());

    backfeishounannv(allmiaoshu[3].toString(), nannv, gaodi, feishou);

    QMap<QString,oneman*>::Iterator back=allman.find(name);
    if(back!=allman.end())//找到了
    {
        if(back.value()->onemessage!=nullptr)//已经存在了，更新吧
        {
            back.value()->onemessage->alltext=RegStr;
            back.value()->onemessage->feishou=feishou;
            back.value()->onemessage->gaodi=gaodi;
            back.value()->onemessage->name=name;
            back.value()->onemessage->nannv=nannv;
            back.value()->onemessage->nianling=nianling;
            back.value()->onemessage->xiezi=xiezi;
            back.value()->onemessage->yifu=yifu;
            back.value()->onemessage->yifuyanse=yifuyanse;
            back.value()->onemessage->xieziyanse=xieziyanse;
            back.value()->showWidget->alltext(RegStr);
            back.value()->showWidget->name(name);
            back.value()->showWidget->feishou(feishou);
            back.value()->showWidget->gaodi(gaodi);
            back.value()->showWidget->nannv(nannv);
            back.value()->showWidget->nianling(nianling);
            back.value()->showWidget->xiezi(xiezi);
            back.value()->showWidget->yifu(yifu);
            back.value()->showWidget->yifuyanse(yifuyanse);
            back.value()->showWidget->xieziyanse(xieziyanse);
        }
        else//不存在了，new
        {
            onemessage* newmedd=new onemessage;
            back.value()->onemessage=newmedd;
            back.value()->onemessage->alltext=RegStr;
            back.value()->onemessage->feishou=feishou;
            back.value()->onemessage->gaodi=gaodi;
            back.value()->onemessage->name=name;
            back.value()->onemessage->nannv=nannv;
            back.value()->onemessage->nianling=nianling;
            back.value()->onemessage->xiezi=xiezi;
            back.value()->onemessage->yifu=yifu;
            back.value()->onemessage->yifuyanse=yifuyanse;
            back.value()->onemessage->xieziyanse=xieziyanse;
            if(back.value()->showWidget!=nullptr)//已经存在了界面
            {
                back.value()->showWidget->alltext(RegStr);
                back.value()->showWidget->name(name);
                back.value()->showWidget->feishou(feishou);
                back.value()->showWidget->gaodi(gaodi);
                back.value()->showWidget->nannv(nannv);
                back.value()->showWidget->nianling(nianling);
                back.value()->showWidget->xiezi(xiezi);
                back.value()->showWidget->yifu(yifu);
                back.value()->showWidget->yifuyanse(yifuyanse);
                back.value()->showWidget->xieziyanse(xieziyanse);
            }
            else//不存在
            {
                lurenUI* newUI=new lurenUI;
                back.value()->showWidget=newUI;
                back.value()->showWidget->alltext(RegStr);
                back.value()->showWidget->name(name);
                back.value()->showWidget->feishou(feishou);
                back.value()->showWidget->gaodi(gaodi);
                back.value()->showWidget->nannv(nannv);
                back.value()->showWidget->nianling(nianling);
                back.value()->showWidget->xiezi(xiezi);
                back.value()->showWidget->yifu(yifu);
                back.value()->showWidget->yifuyanse(yifuyanse);
                back.value()->showWidget->xieziyanse(xieziyanse);
                ui->tabWidget->addTab(newUI,name);
            }
        }
    }
    else//没找到
    {
        oneman* newoneman=new oneman;
        onemessage* newmedd=new onemessage;
        newoneman->onemessage=newmedd;
        newoneman->onemessage->alltext=RegStr;
        newoneman->onemessage->feishou=feishou;
        newoneman->onemessage->gaodi=gaodi;
        newoneman->onemessage->name=name;
        newoneman->onemessage->nannv=nannv;
        newoneman->onemessage->nianling=nianling;
        newoneman->onemessage->xiezi=xiezi;
        newoneman->onemessage->yifu=yifu;
        newoneman->onemessage->yifuyanse=yifuyanse;
        newoneman->onemessage->xieziyanse=xieziyanse;
        lurenUI* newUI=new lurenUI;
        newoneman->showWidget=newUI;
        newoneman->showWidget->alltext(RegStr);
        newoneman->showWidget->name(name);
        newoneman->showWidget->feishou(feishou);
        newoneman->showWidget->gaodi(gaodi);
        newoneman->showWidget->nannv(nannv);
        newoneman->showWidget->nianling(nianling);
        newoneman->showWidget->xiezi(xiezi);
        newoneman->showWidget->yifu(yifu);
        newoneman->showWidget->yifuyanse(yifuyanse);
        newoneman->showWidget->xieziyanse(xieziyanse);
        ui->tabWidget->addTab(newUI,name);
        allman.insert(name,newoneman);
    }
}

void MainWindow::xinxi(QString RegStr, QJsonArray &allmiaoshu)
{
    qDebug()<<"MainWindow::xinxi()  asdf--"<<allmiaoshu;
    //qDebug()<<"("<<regularmatch.capturedStart()<<","<<index<<")"<<regularmatch.captured(0);
    //int end=regularmatch.capturedEnd();
    //int start=regularmatch.capturedStart();
    //QString checkStr=regularmatch.captured(0);
    //qDebug()<<"old checkStr--"<<checkStr;
    //checkStr.remove(QRegularExpression("\\033\\["));
    //inArray.remove(regularmatch.capturedStart(),regularmatch.capturedEnd()-regularmatch.capturedStart());
    //qDebug()<<"start--"<<start<<"  end--"<<end<<"  new checkStr--"<<checkStr<<"  inArray--"<<inArray;
    QString name=allmiaoshu[0].toString();
    QString nannv=allmiaoshu[1].toString();
    QString miaoshu=allmiaoshu[3].toString();
    if(miaoshu.indexOf("错人了")==-1)
    {
        QMap<QString,oneman*>::Iterator back=allman.find(name);
        if(back!=allman.end())//找到了名字
        {
            if(nannv=="公公")
            {
                if(back.value()->onemessage!=nullptr)
                {
                    back.value()->onemessage->nannv="公公";
                }
                if(back.value()->showWidget!=nullptr)
                {
                    back.value()->showWidget->nannv("公公");
                }
            }
            if(back.value()->zhengcimessage!=nullptr)//有证词了
            {
                backzhengci(miaoshu,back.value()->zhengcimessage->zhengciList);
            }
            else//没证词
            {
                zhengcimessage* newone=new zhengcimessage;
                back.value()->zhengcimessage=newone;
                back.value()->zhengcimessage->alltext=RegStr;
                backzhengci(miaoshu,back.value()->zhengcimessage->zhengciList);
            }
            QString backall;
            for(auto onestr:back.value()->zhengcimessage->zhengciList)
            {
                backall=backall+onestr;
            }
            if(back.value()->showWidget!=nullptr)//有界面
            {
                back.value()->showWidget->zhengci(RegStr);
                back.value()->showWidget->zhengjv(backall);
            }
            else//没界面
            {
                lurenUI* nreUI=new lurenUI;
                back.value()->showWidget=nreUI;
                back.value()->showWidget->zhengci(RegStr);
                back.value()->showWidget->zhengjv(backall);
                ui->tabWidget->addTab(nreUI,name);
            }
        }
        else//没找到名字
        {
            oneman* newallone=new oneman;
            zhengcimessage* newone=new zhengcimessage;
            newallone->zhengcimessage=newone;
            newallone->zhengcimessage->alltext=RegStr;
            backzhengci(miaoshu,newallone->zhengcimessage->zhengciList);
            lurenUI* nreUI=new lurenUI;
            newallone->showWidget=nreUI;
            newallone->showWidget->zhengci(RegStr);
            QString backall;
            for(auto onestr:newallone->zhengcimessage->zhengciList)
            {
                backall=backall+onestr;
            }
            newallone->showWidget->zhengjv(backall);
            ui->tabWidget->addTab(nreUI,name);
            allman.insert(name,newallone);
        }
    }
    else//找错人了
    {
        QMap<QString,oneman*>::Iterator back=allman.find(name);
        if(back!=allman.end())//找到了名字
        {
            if(back.value()->onemessage!=nullptr)
            {
                delete back.value()->onemessage;
            }
            if(back.value()->showWidget!=nullptr)
            {
                for(int num=0; num<ui->tabWidget->count(); num++)
                {
                    if(ui->tabWidget->tabText(num)==name)
                    {
                        ui->tabWidget->removeTab(num);
                        break;
                    }
                }
                back.value()->showWidget->deleteLater();
            }
            allman.remove(name);
        }
    }
}

void MainWindow::lingrenwu(QString RegStr, QJsonArray &value)
{
    /*目前15个值  编号 难度(简单|普通|困难|挑战) 接受人(没接受为0) 5排*/
    qDebug()<<"MainWindow::lingrenwu()  value--"<<value;

    QList<jueweiRenwuXinxi> aaaList;
    for(int num=0; num<5; num++)
    {
        jueweiRenwuXinxi firstone;
        firstone.bianhao=value[0+num*3].toString();
        firstone.nandu=nandu(value[1+num*3].toString());
        firstone.renwu=value[2+num*3].toString();
        if(firstone.renwu=="0")
        {
            aaaList.append(firstone);
        }
    }
    if(aaaList.count()>0)
    {
        int nownum=0;
        for(int num=0; num<aaaList.count(); num++)
        {
            if(aaaList[nownum]<aaaList[num])
            {
                nownum=num;
            }
        }

        QByteArray backArray;
        backArray.append('B');
        backArray.append('e');
        backArray.append('G');
        backArray.append('i');
        backArray.append('N');
        backArray.append('0');
        backArray.append('0');
        backArray.append('0');
        backArray.append("record 1_"+aaaList[nownum].bianhao);
        globalCheck::int2Bytes(backArray.size()-8, backArray,5);

        clientSocket.write(backArray);
    }
}

QString MainWindow::backshenqian(QString yanse)
{
    QString backcolor="浅色";
    switch (yanse.toInt()) {
    case 30:
    {
        backcolor="深色";
        break;
    }
    case 31:
    {
        backcolor="深色";
        break;
    }
    case 32:
    {
        backcolor="浅色";
        break;
    }
    case 33:
    {
        backcolor="浅色";
        break;
    }
    case 34:
    {
        backcolor="深色";
        break;
    }
    case 35:
    {
        backcolor="深色";
        break;
    }
    case 36:
    {
        backcolor="浅色";
        break;
    }
    case 37:
    {
        backcolor="浅色";
        break;
    }
    }
    return backcolor;
}

QString MainWindow::backyifu(QString value)
{
    QString back="夹袄";
    if(value=="丝织长衫" || value=="丝绸短襦" || value=="绸袍" || value=="丝织儒衫" || value=="轻罗纱" || value=="旗袍")
    {
        back="丝绸衣服";
    }
    else if(value=="坎肩" || value=="圆领衫" || value=="灰布衫" || value=="灰马褂" || value=="百褶裙" || value=="蓝马褂" || value=="短打劲装" || value=="天蓝锦袍")
    {
        back="布衣";
    }
    else if(value=="鹤氅" || value=="长袄" || value=="棉袄" || value=="狼皮袄" || value=="短袄" || value=="比甲")
    {
        back="夹袄";
    }
    else
    {
        ;
    }
    return back;
}

QString MainWindow::backxiezi(QString value)
{
    QString back="凉鞋";
    if(value=="木屐" || value=="草鞋" || value=="破鞋")
    {
        back="凉鞋";
    }
    else if(value=="绣花鞋" || value=="锦鞋" || value=="凤鞋" || value=="布鞋" || value=="麻鞋" || value=="千层底布鞋")
    {
        back="布鞋";
    }
    else if(value=="牛皮短靴" || value=="马靴" || value=="女式短靴" || value=="女式长靴" || value=="薄底快靴" || value=="七星剑靴")
    {
        back="靴子";
    }
    else
    {
        ;
    }
    return back;
}

void MainWindow::backfeishounannv(QString entermiaoshu, QString &nannv, QString &gaodi, QString &feishou)
{
    QString linshiNANNV=nannv;
    if(entermiaoshu.indexOf("身材异常魁梧高大")!=-1)
    {
        gaodi="高";
        feishou="胖";
        nannv="女";
    }
    else if(entermiaoshu.indexOf("娇小玲珑")!=-1)
    {
        gaodi="矮";
        feishou="廋";
        nannv="女";
    }
    else if(entermiaoshu.indexOf("丰满矮小")!=-1)
    {
        gaodi="矮";
        feishou="胖";
        nannv="女";
    }
    else if(entermiaoshu.indexOf("丰胸细腰")!=-1)
    {
        gaodi="高";
        feishou="廋";
        nannv="女";
    }
    else if(entermiaoshu.indexOf("竹竿")!=-1)
    {
        gaodi="高";
        feishou="廋";
        nannv="男";
    }
    else if(entermiaoshu.indexOf("矮小粗胖")!=-1)
    {
        gaodi="矮";
        feishou="胖";
        nannv="男";
    }
    else if(entermiaoshu.indexOf("高大魁梧")!=-1)
    {
        gaodi="高";
        feishou="胖";
        nannv="男";
    }
    else if(entermiaoshu.indexOf("矮小灵活")!=-1)
    {
        gaodi="矮";
        feishou="廋";
        nannv="男";
    }


    if(linshiNANNV=="她")//她
    {
        if(nannv=="男")
        {
            nannv="公公";
        }
    }
    else//他
    {
        if(nannv=="女")
        {
            nannv="公公";
        }
    }
}

void MainWindow::backzhengci(QString enter, QSet<QString> &back)
{
    if(enter.indexOf("你已经问过了")==-1)
    {
        back.clear();
        if(enter.indexOf("男")!=-1)
        {
            back.insert("男");
        }
        if(enter.indexOf("女")!=-1)
        {
            back.insert("女");
        }
        if(enter.indexOf("流浪汉")!=-1)
        {
            back.insert("男");
        }
        if(enter.indexOf("发福")!=-1)
        {
            back.insert("胖");
        }
        if(enter.indexOf("发胖")!=-1)
        {
            back.insert("胖");
        }
        if(enter.indexOf("有点胖")!=-1)
        {
            back.insert("胖");
        }
        if(enter.indexOf("偏")!=-1)
        {
            back.insert("廋");
        }
        if(enter.indexOf("猴子")!=-1)
        {
            back.insert("廋");
        }
        if(enter.indexOf("竹竿")!=-1)
        {
            back.insert("廋");
        }
        if(enter.indexOf("不太高")!=-1)
        {
            back.insert("矮");
        }
        if(enter.indexOf("矮个子")!=-1)
        {
            back.insert("矮");
        }
        if(enter.indexOf("高个子")!=-1)
        {
            back.insert("高");
        }
        if(enter.indexOf("凉鞋")!=-1)
        {
            back.insert("凉鞋");
        }
        if(enter.indexOf("布鞋")!=-1)
        {
            back.insert("布鞋");
        }
        if(enter.indexOf("靴子")!=-1)
        {
            back.insert("靴子");
        }
        if(enter.indexOf("丝绸衣服")!=-1)
        {
            back.insert("丝绸衣服");
        }
        if(enter.indexOf("布衣")!=-1)
        {
            back.insert("布衣");
        }
        if(enter.indexOf("夹袄")!=-1)
        {
            back.insert("夹袄");
        }
        if(enter.indexOf("深色衣服")!=-1)
        {
            back.insert("深色衣服");
        }
        if(enter.indexOf("浅色衣服")!=-1)
        {
            back.insert("浅色衣服");
        }
        if(enter.indexOf("深色鞋子")!=-1)
        {
            back.insert("深色鞋子");
        }
        if(enter.indexOf("浅色鞋子")!=-1)
        {
            back.insert("浅色鞋子");
        }
    }
}

bool MainWindow::backzijifuhe(QString tezheng, onemessage *renwu)
{
    //qDebug()<<"MainWindow::backzijifuhe mingzi--"<<renwu->name<<"  tezheng--"<<tezheng;
    if(renwu->nannv==tezheng)
    {
        //qDebug()<<"MainWindow::backzijifuhe nannv--"<<renwu->nannv;
        return true;
    }
    if(renwu->feishou==tezheng)
    {
        //qDebug()<<"MainWindow::backzijifuhe feishou--"<<renwu->feishou;
        return true;
    }
    if(renwu->gaodi==tezheng)
    {
        //qDebug()<<"MainWindow::backzijifuhe gaodi--"<<renwu->gaodi;
        return true;
    }
    if(renwu->xiezi==tezheng)
    {
        //qDebug()<<"MainWindow::backzijifuhe xiezi--"<<renwu->xiezi;
        return true;
    }
    if(renwu->xieziyanse==tezheng)
    {
        //qDebug()<<"MainWindow::backzijifuhe xieziyanse--"<<renwu->xieziyanse;
        return true;
    }
    if(renwu->yifu==tezheng)
    {
        //qDebug()<<"MainWindow::backzijifuhe yifu--"<<renwu->yifu;
        return true;
    }
    if(renwu->yifuyanse==tezheng)
    {
        //qDebug()<<"MainWindow::backzijifuhe yifuyanse--"<<renwu->yifuyanse;
        return true;
    }
    return false;
}

void MainWindow::tcpgetall(QString jsonstr)
{
    QJsonObject allobj=QJsonDocument::fromJson(jsonstr.toUtf8()).object();
    if(allobj.find("Class")!=allobj.end() && allobj.find("Name")!=allobj.end() && allobj.find("RegStrList")!=allobj.end() && allobj.find("RegStr")!=allobj.end())
    {
        QString classname=allobj.value("Class").toString();
        QString regName=allobj.value("Name").toString();
        QJsonArray RegStrList=allobj.value("RegStrList").toArray();
        QString RegStr=allobj.value("RegStr").toString();
        messageFile->write(RegStr.toUtf8());
        if(classname=="爵位" && regName=="人物")
        {
            xieru(RegStr, RegStrList);
        }
        else if(classname=="爵位" && regName=="证据")
        {
            xinxi(RegStr, RegStrList);
        }
        else if(classname=="爵位" && regName=="领任务")
        {
            lingrenwu(RegStr, RegStrList);
            on_qingkong_clicked();
        }
    }
}


void MainWindow::on_connectbt_clicked()
{
    int portnum=ui->port->text().toInt();
    clientSocket.connectToHost(QHostAddress::LocalHost, portnum);
}

