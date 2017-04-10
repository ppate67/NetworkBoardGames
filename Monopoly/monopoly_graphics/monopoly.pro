QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = monopoly
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    player.h \
    boardspace.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
