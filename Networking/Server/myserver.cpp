#include "myserver.h"
#include "iostream"
using namespace std;
 player MyServer::plist[MAXNUMPLAYER];
MyServer::MyServer(QObject *parent) :
    QTcpServer(parent)
{


    if(!listen(QHostAddress::Any, 1234))
    {
       cout << "Server could not start!";
    }
    else
    {
        cout << "Server started!";
        QHostInfo info;
        QNetworkInterface qinterface = QNetworkInterface::interfaceFromName(info.hostName());
        cout << qinterface.allAddresses()[3].toString().toStdString();
    }
}
QTcpSocket* MyServer::getuserlist(int userid){
    return (plist[userid].socket);
}
void MyServer::incomingConnection(qintptr handle)
{

    for(int i=0; i<MAXNUMPLAYER; i++)
    {

        if(plist[i].filled==0){


            plist[i].SetSocket(handle);

            plist[i].filled=1;

            cout << "Player id: " << i << endl;
            break;
    }

    }
}
void addPlayerName(string name){
  playerList.push_back (string name);
}
int getNumGoGames(){
    return 0;
}
int getGoGamePeer(int game){//gameID in playerID out
    return 0;
}
int getNumChessGames(){
    return 0;
}
int getChessGamePeer(int game){//gameID in playerID out
    return 0;
}
int getNumCheckGames(){
    return 0;
}
int getCheckGamePeer(int game){//gameID in playerID out
    return 0;
}
int getNumMonoGames(){
    return 0;
}
