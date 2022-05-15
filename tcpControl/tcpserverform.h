#ifndef TCPSERVERFORM_H
#define TCPSERVERFORM_H

#include <QWidget>
#include <tcpControl/tcpservercontrol.h>

namespace Ui {
class TcpServerForm;
}

class TcpServerForm : public QWidget
{
    Q_OBJECT

public:
    explicit TcpServerForm(QWidget *parent = nullptr);
    ~TcpServerForm();

private slots:
    void on_listenPortBT_clicked(bool checked);

private:
    Ui::TcpServerForm *ui;
    TcpServerControl tcpServerControl;
};

#endif // TCPSERVERFORM_H
