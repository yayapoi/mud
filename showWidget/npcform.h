#ifndef NPCFORM_H
#define NPCFORM_H

#include <QWidget>

namespace Ui {
class NPCForm;
}

class NPCForm : public QWidget
{
    Q_OBJECT

public:
    explicit NPCForm(QWidget *parent = nullptr);
    ~NPCForm();

    void initWidget(QString title, QString nameZH, QString nameEn);
    void getWidget(QString &title, QString &nameZH, QString &nameEn);
private:
    Ui::NPCForm *ui;
signals:
    void deleteNpc(NPCForm*);
private slots:
    void on_deletBT_clicked();
};

#endif // NPCFORM_H
