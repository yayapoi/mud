QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 #console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    INI/inimanarge.cpp \
    ZHToEN/zhtopy.cpp \
    chatform.cpp \
    cmdMessageControl/cmdcontrol.cpp \
    cmdMessageControl/cmddo.cpp \
    configWidget/configform.cpp \
    configWidget/mapcreateconfigform.cpp \
    flowjson/jsoninter.cpp \
    fontwidget.cpp \
    globalhead.cpp \
    main.cpp \
    mainwindow.cpp \
    mapCreateWindow/mapcreatelineitem.cpp \
    mapCreateWindow/mapcreateroomitem.cpp \
    mapCreateWindow/mapcreateview.cpp \
    mapCreateWindow/mapcreatrecitem.cpp \
    mapmainwindow.cpp \
    regClass/parentwidget.cpp \
    regClass/regclass.cpp \
    regClass/regform.cpp \
    regClass/regwidget.cpp \
    showWidget/goform.cpp \
    showWidget/npcform.cpp \
    showWidget/outform.cpp \
    showWidget/roomwidget.cpp \
    statusBar/pointbar.cpp \
    statusBar/statusform.cpp \
    tcpControl/tcpconnect.cpp \
    tcpControl/tcpprotocoltrans.cpp \
    tcpControl/tcpservercontrol.cpp \
    tcpControl/tcpserverform.cpp \
    work/worksys.cpp

HEADERS += \
    INI/inimanarge.h \
    ZHToEN/zhtopy.h \
    chatform.h \
    cmdMessageControl/cmdcontrol.h \
    cmdMessageControl/cmddo.h \
    configWidget/configform.h \
    configWidget/mapcreateconfigform.h \
    flowjson/jsoninter.h \
    fontwidget.h \
    globalhead.h \
    mainwindow.h \
    mapCreateWindow/mapcreatelineitem.h \
    mapCreateWindow/mapcreateroomitem.h \
    mapCreateWindow/mapcreateview.h \
    mapCreateWindow/mapcreatrecitem.h \
    mapmainwindow.h \
    regClass/parentwidget.h \
    regClass/regclass.h \
    regClass/regform.h \
    regClass/regwidget.h \
    showWidget/goform.h \
    showWidget/npcform.h \
    showWidget/outform.h \
    showWidget/roomwidget.h \
    statusBar/pointbar.h \
    statusBar/statusform.h \
    tcpControl/tcpconnect.h \
    tcpControl/tcpprotocoltrans.h \
    tcpControl/tcpservercontrol.h \
    tcpControl/tcpserverform.h \
    work/worksys.h \
    zconf.h \
    zlib.h

FORMS += \
    chatform.ui \
    configWidget/configform.ui \
    configWidget/mapcreateconfigform.ui \
    fontwidget.ui \
    mainwindow.ui \
    mapmainwindow.ui \
    regClass/parentwidget.ui \
    regClass/regform.ui \
    regClass/regwidget.ui \
    showWidget/goform.ui \
    showWidget/npcform.ui \
    showWidget/outform.ui \
    showWidget/roomwidget.ui \
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
