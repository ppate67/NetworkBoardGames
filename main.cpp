#include "mainwindow.h"
#include "chessboard.h"
#include <QtGui>
#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget *myWidget = new QWidget();
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    myWidget->setGeometry(0,0,width,height);
    chessboard c;
    Chess *tile[8][8]={{NULL}};
    c.display(myWidget,tile);
    myWidget->showFullScreen();
    return a.exec();
}
