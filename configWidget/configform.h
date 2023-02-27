#ifndef CONFIGFORM_H
#define CONFIGFORM_H

#include <QWidget>

namespace Ui {
class ConfigForm;
}

class ConfigForm : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigForm(QWidget *parent = nullptr);
    ~ConfigForm();
    ///外界获取设定的名字，id
    void getNameAndID(QString& name, QString& id);
signals:
    void closeWidget();
private slots:
    void on_OKBT_clicked();

    ///2勾选  0没勾
    void on_allGMCPset_stateChanged(int arg1);

    void on_buffCB_stateChanged(int arg1);

    void on_moveCB_stateChanged(int arg1);

    void on_combatCB_stateChanged(int arg1);

    void on_statusCB_stateChanged(int arg1);

    void on_messageCB_stateChanged(int arg1);

private:
    Ui::ConfigForm *ui;

    void enableGB(bool flag);
};

#endif // CONFIGFORM_H
