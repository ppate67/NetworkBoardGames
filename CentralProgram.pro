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
    Go/main.cpp \
    Chess/chess.cpp \
    Chess/chessboard.cpp \
    Chess/pieces.cpp \
    Go/go.cpp \
    Go/goboard.cpp \
    Go/mainwindow.cpp \
    Networking/Client/client.cpp \
    Networking/Client/gamemanager.cpp \
    Networking/Client/gamemsg.cpp


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SUBDIRS += \
    Checkers/board1.pro \
    Chess/Test3.pro \
    Networking/Client/TestHost.pro

RESOURCES += \
    Checkers/checkers_pieces.qrc \
    Checkers/images.qrc \
    Checkers/kings.qrc \
    Chess/resources.qrc \
    Go/resources2.qrc

FORMS += \
    mainwindow.ui

DISTFILES += \
    Checkers/IMG_0114.JPG \
    Checkers/Black-Circle.png \
    Checkers/darkking.png \
    Checkers/lightking.png \
    Checkers/Red-circle.png \
    Chess/mainwindow.h.gch \
    Chess/Test3.pro.user \
    Chess/darkbishop.png \
    Chess/darkking.png \
    Chess/darkknight.png \
    Chess/darkpawn.png \
    Chess/darkqueen.png \
    Chess/darkrook.png \
    Chess/lightbishop.png \
    Chess/lightking.png \
    Chess/lightknight.png \
    Chess/lightpawn.png \
    Chess/lightqueen.png \
    Chess/lightrook.png \
    Go/blackstone.png \
    Go/bottomleft.png \
    Go/bottomright.png \
    Go/bottomside.png \
    Go/circlecross.png \
    Go/CROSS.png \
    Go/leftside.png \
    Go/rightside.png \
    Go/sqr.png \
    Go/topleft.png \
    Go/topright.png \
    Go/topside.png \
    Go/whitestone.png \
    Go/README \
    Networking/Client/README.txt

HEADERS += Chess/chess.h \
    Chess/chessboard.h \
    Chess/pieces.h \
    Go/go.h \
    Go/goboard.h \
    Go/mainwindow.h \
    Networking/Client/client.h \
    Networking/Client/gamemanager.h \
    Networking/Client/gamemsg.h
