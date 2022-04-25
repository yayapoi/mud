#include "mainwindow.h"
#include <fontwidget.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //FontWidget w;
    w.show();
    return a.exec();
}
