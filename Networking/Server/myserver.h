#ifndef MYSERVER_H
#define MYSERVER_H
#include <string>
#include "vector"
#include <QObject>
#include <QDebug>
#include <QStringList>
#include <QTcpSocket>
#include <QtNetwork/QTcpServer>
#include <player.h>
#include <QMap>
#include <QSet>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
//winsock2.h should replace netinet.h for windows socket functionality
#include <winsock2.h>
#include <sys/types.h>
//winsock2 should also work for sys/socket.h
//#include <sys/socket.h>

//#include <iostream>

//using namespace std;
class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);
    vector<string> playerList; //List of playernames to be called from server
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

//void newconnection (int sock)
//{
//   int n;
//   char buffer[256];

//   bzero(buffer,256);
//   n = read(sock,buffer,255);
//   if (n < 0) error("Error reading from socket");
//   printf("playerName: %s\n",buffer); // playername in quotes here will be replaeced wiht actual playername
//   //n = write(sock,"Message sent",18); this needs to go to the UI eventually

//   //this is where we pass n to the message board and append the username to the beginning
//   //of the string. ie, username:message
//}

//void error(const char *errormsg)
//{     //standardize error messages
//    perror(errormsg);
//    exit(1);
//}

//void StartChatServer(){
//  int sockfd, newsockfd, pid;
//  int portnum = 51717;
//  socklen_t clientlength;
//  struct sockaddr_in serv_addr, cli_addr;
//  sockfd = socket(AF_INET, SOCK_STREAM, 0);

//  if (sockfd < 0)
//     error("Error opening socket");

//  bzero((char *) &serv_addr, sizeof(serv_addr));
//  serv_addr.sin_family = AF_INET;
//  serv_addr.sin_addr.s_addr = INADDR_ANY;
//  serv_addr.sin_port = htons(portnum);

//  if (bind(sockfd, (struct sockaddr *) &serv_addr,
//           sizeof(serv_addr)) < 0)
//           error("Error on binding");
//  listen(sockfd,5);

//  clientlength = sizeof(cli_addr);

//  while (1) {
//      newsockfd = accept(sockfd,
//            (struct sockaddr *) &cli_addr, &clientlength);
//      if (newsockfd < 0)
//          error("Error on accept");
//      pid = fork();
//      if (pid < 0)
//          error("Error on fork");
//      if (pid == 0)  {
//          close(sockfd);
//          newconnection(newsockfd);
//          exit(0);
//      }
//      else close(newsockfd);
//  }
//  close(sockfd);
//  return 0;
//}

#endif // MYSERVER_H
