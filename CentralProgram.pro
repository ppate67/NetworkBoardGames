QT += core
QT += gui
QT+=network
QT+=core
CONFIG += c++11

TARGET = TestHost
QT += widgets
CONFIG += app_bundle

TEMPLATE = app
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3
# add the desired -O3 if not present
QMAKE_CXXFLAGS_RELEASE *= -O3
QMAKE_LFLAGS_RELEASE -= -O1
SOURCES += Networking/main.cpp \
    Chess/chess.cpp \
    Chess/chessboard.cpp \
    Chess/pieces.cpp \
    Go/go.cpp \
    Go/goboard.cpp \
    Go/mainwindow.cpp \
    Networking/Client/client.cpp \
    Networking/Client/gamemanager.cpp \
    Networking/Client/gamemsg.cpp \
    Checkers1/checkers.cpp \
    Checkers1/checkersboard.cpp \
    Checkers1/pieces2.cpp \
    Monopoly/Monopoly_graphics/monopolyboard.cpp


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
    Networking/Client/TestHost.pro \
    Checkers1/board1.pro \
    Monopoly/Monopoly_graphics/monopoly.pro

RESOURCES += \
    Chess/resources.qrc \
    Go/resources2.qrc \
    Checkers1/checkers_pieces.qrc \
    Checkers1/images.qrc \
    Checkers1/kings.qrc \
    Monopoly/Monopoly_graphics/resources.qrc

FORMS += \
    Networking/mainwindow.ui \
    Monopoly/Monopoly_graphics/monopolyboard.ui

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
    Networking/Client/README.txt \
    Checkers1/board1.pro.user \
    Checkers1/Black-Circle.png \
    Checkers1/darkking.png \
    Checkers1/lightking.png \
    Checkers1/Red-circle.png \
    Monopoly/Monopoly_graphics/board.jpg \
    Monopoly/Monopoly_graphics/piece1.png \
    Monopoly/Monopoly_graphics/piece2.png

HEADERS += Chess/chess.h \
    Chess/chessboard.h \
    Chess/pieces.h \
    Go/go.h \
    Go/goboard.h \
    Go/mainwindow.h \
    Networking/Client/client.h \
    Networking/Client/gamemanager.h \
    Networking/Client/gamemsg.h \
    Checkers1/checkers.h \
    Checkers1/checkersboard.h \
    Checkers1/pieces2.h \
    Monopoly/Monopoly_graphics/boardspace.h \
    Monopoly/Monopoly_graphics/cards.h \
    Monopoly/Monopoly_graphics/player.h \
    Monopoly/Monopoly_graphics/monopolyboard.h
