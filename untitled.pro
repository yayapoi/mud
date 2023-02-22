QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatform.cpp \
    cmdMessageControl/cmdcontrol.cpp \
    cmdMessageControl/cmddo.cpp \
    configWidget/configform.cpp \
    fontwidget.cpp \
    globalhead.cpp \
    main.cpp \
    mainwindow.cpp \
    regClass/parentwidget.cpp \
    regClass/regclass.cpp \
    regClass/regform.cpp \
    regClass/regwidget.cpp \
    statusBar/pointbar.cpp \
    statusBar/statusform.cpp \
    tcpControl/tcpconnect.cpp \
    tcpControl/tcpprotocoltrans.cpp \
    tcpControl/tcpservercontrol.cpp \
    tcpControl/tcpserverform.cpp

HEADERS += \
    chatform.h \
    cmdMessageControl/cmdcontrol.h \
    cmdMessageControl/cmddo.h \
    configWidget/configform.h \
    fontwidget.h \
    globalhead.h \
    mainwindow.h \
    regClass/parentwidget.h \
    regClass/regclass.h \
    regClass/regform.h \
    regClass/regwidget.h \
    statusBar/pointbar.h \
    statusBar/statusform.h \
    tcpControl/tcpconnect.h \
    tcpControl/tcpprotocoltrans.h \
    tcpControl/tcpservercontrol.h \
    tcpControl/tcpserverform.h \
    zconf.h \
    zlib.h

FORMS += \
    chatform.ui \
    configWidget/configform.ui \
    fontwidget.ui \
    mainwindow.ui \
    regClass/parentwidget.ui \
    regClass/regform.ui \
    regClass/regwidget.ui \
    statusBar/statusform.ui \
    tcpControl/tcpserverform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/./ -llibzlib.dll

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

RESOURCES += \
    res.qrc
