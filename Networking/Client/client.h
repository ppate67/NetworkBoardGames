#ifndef CLIENT_H
#define CLIENT_H
#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <iostream>
#include "Networking/Client/gamemsg.h"
#include "gamemanager.h"
#include "vector"
#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include <string.h>
#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <netdb.h>

using namespace std;
class Client : public QObject
{
    Q_OBJECT
private:
    Client(QObject *parent =0);
    public:
        static void makeClient(){
            if(client == nullptr){
                client = new Client();
            }
        }
        QTcpSocket *socket;
        static QTcpSocket *s;
        static Client* client;
        void Connect();
        void Connect(std::string address, int port);
        void pingpong();
        static void sendGameMsg(GameMsg m);
        static void makeRequest(int requestID[5],int playerid);
        void handleReply(vector<int>data,int size);
        void handleReply2(vector<char> data, int size);
        void SetPlayerName();
public slots:
    void readyRead();
private:


};

//void error(const char *errormsg)
//{     //standardize error messages
//    perror(errormsg);
//    exit(1);
//}

//void startChatClient(){ //this should eventually take the machine name as an argument
//  int sockfd, portnum, n;
//  struct sockaddr_in serv_addr;
//  struct hostent *server;

//  char buffer[256];
//  portnum = 51717;
//  sockfd = socket(AF_INET, SOCK_STREAM, 0);
//  if (sockfd < 0)
//      error("Error opening socket");

//  server = gethostbyname(localhost); //this needs to be the name of whatever machine is running the server, or localhost for you own machine

//  if (server == NULL) {

//      fprintf(stderr,"Error, no such host\n");
//      exit(0);
//  }
//  bzero((char *) &serv_addr, sizeof(serv_addr));
//  serv_addr.sin_family = AF_INET;
//  bcopy((char *)server->h_addr,
//       (char *)&serv_addr.sin_addr.s_addr,
//       server->h_length);
//  serv_addr.sin_port = htons(portnum);
//  if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
//      error("Error connecting");
//  printf("Please enter the message: ");
//  bzero(buffer,256);
//  fgets(buffer,255,stdin);
//  n = write(sockfd,buffer,strlen(buffer));
//  if (n < 0)
//       error("Error writing to socket");
//  bzero(buffer,256);
//  n = read(sockfd,buffer,255);
//  if (n < 0)
//       error("Error reading from socket");
//  printf("%s\n",buffer);
//  close(sockfd);
//  return 0;
//}
#endif // CLIENT_H
