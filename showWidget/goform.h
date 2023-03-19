#ifndef GOFORM_H
#define GOFORM_H

#include <QWidget>

namespace Ui {
class GoForm;
}

class GoForm : public QWidget
{
    Q_OBJECT

public:
    explicit GoForm(QWidget *parent = nullptr);
    ~GoForm();

    void initWidget(QString outCB, QString cmd, QString time, QString room);
    void getWidget(QString &outCB, QString &cmd, QString &time, QString &room);
    void setRoomWidget(QString room2);
    void setRoomTime(QString time1);
private slots:
    void on_deleteRoom_clicked();

    void on_go_clicked();

    void on_outCombox_currentTextChanged(const QString &arg1);

signals:
    void deleteGo(GoForm*);
    void GoFormGo(GoForm*);
private:
    Ui::GoForm *ui;
};

#endif // GOFORM_H
