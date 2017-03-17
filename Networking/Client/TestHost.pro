QT += core
QT += gui
QT+=network
QT+=core
CONFIG += c++11

TARGET = TestHost
QT += widgets
CONFIG += app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    gamemsg.cpp \
    client.cpp \
    mainwindow.cpp \
    go.cpp \
    goboard.cpp \
    gamemanager.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    gamemsg.h \
    client.h \
    mainwindow.h \
    go.h \
    goboard.h \
    gamemanager.h

FORMS += \
    mainwindow.ui
RESOURCES += \
    resources.qrc \
    resources.qrc

DISTFILES += \
    TestHost.pro.user \
    blackstone.png \
    whitestone.png \
    Icons/blackstone.png \
    Icons/whitestone.png \
    Icons/bottomleft.png \
    Icons/bottomright.png \
    Icons/bottomside.png \
    Icons/circlecross.png \
    Icons/CROSS.png \
    Icons/leftside.png \
    Icons/rightside.png \
    Icons/topleft.png \
    Icons/topright.png \
    Icons/topside.png
