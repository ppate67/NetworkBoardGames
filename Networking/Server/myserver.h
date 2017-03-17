#ifndef MYSERVER_H
#define MYSERVER_H
#include <string>
#include "vector"
#include <QObject>
#include <QDebug>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <player.h>
//#include <iostream>

//using namespace std;
class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);
    static player plist[MAXNUMPLAYER];
    QTcpSocket* getuserlist(int userid);
    int getNumGoGames();
    int getGoGamePeer(int game);
    int getNumChessGames();
    int getChessGamePeer(int game);
    int getNumCheckGames();
    int getCheckGamePeer(int game);
    int getNumMonoGames();

    vector<int> getMonoGamePeer(int game);
protected:
    void incomingConnection(qintptr handle);
signals:

public slots:


private:
    int numGo,numChess,numCheck,numMono;

};

#endif // MYSERVER_H
