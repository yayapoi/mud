#ifndef MAPCREATECONFIGFORM_H
#define MAPCREATECONFIGFORM_H

#include <QWidget>

namespace Ui {
class MapCreateConfigForm;
}

class MapCreateConfigForm : public QWidget
{
    Q_OBJECT

public:
    explicit MapCreateConfigForm(QWidget *parent = nullptr);
    ~MapCreateConfigForm();

private slots:
    void on_timeCB_toggled(bool checked);

    void on_errorTimeCB_toggled(bool checked);

private:
    Ui::MapCreateConfigForm *ui;
};

#endif // MAPCREATECONFIGFORM_H
