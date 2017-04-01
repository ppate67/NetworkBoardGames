#include <iostream>
#include <Networking/Client/client.h>
 using namespace std;
 #include <QCoreApplication>
 #include <QtGui>
 #include <QApplication>
 #include <QWidget>
 #include "Go/mainwindow.h"
 int main(int argc, char *argv[])
 {
     QApplication a(argc, argv);
     Client client;
     client.Connect();
         MainWindow w;
         w.show();
 //       QWidget *myWidget = new QWidget();
 //       QScreen *screen = QGuiApplication::primaryScreen();
 //       QRect  screenGeometry = screen->geometry();
 //       int height = screenGeometry.height()/2;
 //       int width = screenGeometry.width()/2;
 //       myWidget->setGeometry(0,0,width,height);
        //myWidget->show();
 
        //GameMsg msg(1,"Dogs",0,4);
        //string data=msg.data;
        //QByteArray data2=QByteArray(data.c_str(),data.length());
 
        //int userid=1;
        //data2.push_front(userid);
        //data2.push_front(msg.type);
        //client.socket->write("da000000000000000000ta");
        //client.socket->waitForBytesWritten(1000);
        return a.exec();
 }
