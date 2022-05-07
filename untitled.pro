QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatform.cpp \
    cmdMessageControl/cmdcontrol.cpp \
    cmdMessageControl/cmddo.cpp \
    fontwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    regClass/regclass.cpp \
    statusBar/pointbar.cpp \
    statusBar/statusform.cpp

HEADERS += \
    chatform.h \
    cmdMessageControl/cmdcontrol.h \
    cmdMessageControl/cmddo.h \
    fontwidget.h \
    mainwindow.h \
    regClass/regclass.h \
    statusBar/pointbar.h \
    statusBar/statusform.h \
    zconf.h \
    zlib.h

FORMS += \
    chatform.ui \
    fontwidget.ui \
    mainwindow.ui \
    statusBar/statusform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/./ -llibzlib.dll

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

RESOURCES += \
    res.qrc
