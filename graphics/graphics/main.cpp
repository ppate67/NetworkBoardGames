#include "mainwindow.h"
#include "checker.h"
#include "chess.h"
#include "go.h"
#include "monopoly.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
   // w.show();
    MainWindow *me=new MainWindow();
    me->show();

    return a.exec();
}
