#ifndef LURENUI_H
#define LURENUI_H

#include <QWidget>
#include <QSet>

namespace Ui {
class lurenUI;
}

struct onemessage{
    QString alltext;
    QString name;
    QString nannv;
    QString gaodi;
    QString feishou;
    QString nianling;
    QString yifuyanse;
    QString yifu;
    QString xieziyanse;
    QString xiezi;
};

struct zhengcimessage{
    QString alltext;
    QSet<QString> zhengciList;
};

class lurenUI : public QWidget
{
    Q_OBJECT

public:
    explicit lurenUI(QWidget *parent = nullptr);
    ~lurenUI();

    void alltext(QString value);
    void name(QString value);
    void nannv(QString value);
    void nianling(QString value);
    void gaodi(QString value);
    void feishou(QString value);
    void yifu(QString value);
    void yifuyanse(QString value);
    void xiezi(QString value);
    void xieziyanse(QString value);
    void zhengci(QString value);
    void zhengjv(QString value);
private:
    Ui::lurenUI *ui;
};

struct oneman{
    onemessage* onemessage=nullptr;
    zhengcimessage* zhengcimessage=nullptr;
    lurenUI* showWidget=nullptr;
    bool daozei=true;
};
#endif // LURENUI_H
