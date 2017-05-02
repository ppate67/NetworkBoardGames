#include <iostream>
#include <cstdlib>
#include "mainwindow.h"
#include <QApplication>
#include "boardspace.h"
#include "cards.h"
#include "player.h"

using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}
