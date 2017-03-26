#include "mainwindow.h"
#include "checkersboard.h"
#include <QtGui>
#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    QWidget *myWidget = new QWidget();
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    myWidget->setGeometry(0,0,width,height);

    checkersboard c;
    c.setup(myWidget);

    myWidget->showFullScreen();

    return a.exec();
}
