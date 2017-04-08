#-------------------------------------------------
#
# Project created by QtCreator 2013-04-08T21:22:43
#
#-------------------------------------------------

QT       += core
QT       += network
QT += sql
QT       -= gui

TARGET = MyFirstServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    myserver.cpp \
    player.cpp \
    gamemsg.cpp \
    database.cpp \
    dataline.cpp \
    #chatmsg.cpp \
    gamemanager.cpp \
   # chatmainwindow.cpp

HEADERS += \
    myserver.h \
    player.h \
    gamemsg.h \
    database.h \
    dataline.h \
    #chatmsg.h \
    gamemanager.h \
    #chatmainwindow.h

FORMS += \
    #chatmainwindow.ui
