#include "myserver.h"
#include "iostream"
#include <QTcpSocket>
#include <QRegExp>
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

void MyServer::sendUserList()
{
    QStringList userList;
    foreach(QString user, users.values())
        userList << user;

    foreach(QTcpSocket *client, clients)
        client->write(QString("/users:" + userList.join(",") + "\n").toUtf8());
}

void MyServer::disconnected()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    qDebug() << "Client disconnected:" << client->peerAddress().toString();

    clients.remove(client);

    QString user = users[client];
    users.remove(client);

    sendUserList();
    foreach(QTcpSocket *client, clients)
        client->write(QString("Server:" + user + " has left.\n").toUtf8());
}

void MyServer::readyRead()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    while(client->canReadLine())
    {
        QString line = QString::fromUtf8(client->readLine()).trimmed();
        qDebug() << "Read line:" << line;

        QRegExp meRegex("^/me:(.*)$");

        if(meRegex.indexIn(line) != -1)
        {
            QString user = meRegex.cap(1);
            users[client] = user;
            foreach(QTcpSocket *client, clients)
                client->write(QString("Server:" + user + " has joined.\n").toUtf8());
            sendUserList();
        }
        else if(users.contains(client))
        {
            QString message = line;
            QString user = users[client];
            qDebug() << "User:" << user;
            qDebug() << "Message:" << message;

            foreach(QTcpSocket *otherClient, clients)
                otherClient->write(QString(user + ":" + message + "\n").toUtf8());
        }
        else
        {
            qWarning() << "Got bad message from client:" << client->peerAddress().toString() << line;
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
