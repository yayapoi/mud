#ifndef OUTFORM_H
#define OUTFORM_H

#include <QWidget>

namespace Ui {
class OutForm;
}

class OutForm : public QWidget
{
    Q_OBJECT

public:
    explicit OutForm(QWidget *parent = nullptr);
    ~OutForm();

    void initWidget(QString comeRoom, QString roomName, QString outLe, QString cmdLe);
    void getWidget(QString &comeRoom, QString &roomName, QString &outLe, QString &cmdLe);
private:
    Ui::OutForm *ui;
};

#endif // OUTFORM_H
