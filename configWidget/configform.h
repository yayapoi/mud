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

private:
    Ui::ConfigForm *ui;
};

#endif // CONFIGFORM_H
