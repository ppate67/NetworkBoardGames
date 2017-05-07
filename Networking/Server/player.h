#ifndef PLAYER_H
#define PLAYER_H
#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QThreadPool>
#include <QHostInfo>
#include <QNetworkInterface>
//#include <iostream>
#include "gamemanager.h"
#include "gamemsg.h"
const int MAXNUMPLAYER = 32;
//using namespace std;
class player : public QObject
{
    Q_OBJECT
public:
    explicit player(QObject *parent =0);
    string playerName;
    void SetSocket(int id);
    int filled=0;
    QTcpSocket *slist[MAXNUMPLAYER];
    friend void incomingConnection(int handle);
     QTcpSocket *socket;
signals:
public slots:
    void connected();
    void disconnected();
    void readyRead();
    void task(GameMsg* msg);
    void handleRequest(int requestID[4], int playerID);
    void handleRequest2(int requestID[5], int playerID);
    void broadcastGames();
    void setUserName(const string& name);
    /*
    requestID[0]->gamemanager function
    requestID[1]->options1
    requestID[2]->options2
    requestID[3]->options3



    */
private:

 };
#endif // PLAYER_H
