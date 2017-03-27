#ifndef CLIENT_H
#define CLIENT_H
#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <iostream>
#include "Networking/Client/gamemsg.h"
#include "gamemanager.h"
#include "vector"
using namespace std;
class Client : public QObject
{
    Q_OBJECT
    public:
        Client(QObject *parent =0);
        QTcpSocket *socket;
        static QTcpSocket *s;
        void Connect();
        void pingpong();
        static void sendGameMsg(GameMsg m);
        static void makeRequest(int requestID[5],int playerid);
        void handleReply(vector<int>data,int size);
        void handleReply2(vector<char> data, int size);
public slots:
    void readyRead();
private:


};

#endif // CLIENT_H
