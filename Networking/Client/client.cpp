#include "client.h"
#include "Go/go.h"
#include "Chess/chess.h"
#include "fstream"
#include "QMessageBox"
QTcpSocket* Client::s=NULL;
Client::Client(QObject *parent):QObject(parent)
{

}

void Client::Connect(){
    socket = new QTcpSocket(this);
    socket->connectToHost(QHostAddress("127.0.0.1"),1234);
    if(socket->waitForConnected(3000)){

        connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
        cout << "Client Connected" << endl;

    }
    else cout<<"Not Connected"<<endl;
    Client::s=socket;


}
void Client :: readyRead(){
    QByteArray message = socket->readAll();
    int id= int(message[0]);
    int type = int(message[1]);
    if(type==0){
    int datamessage[169];

    for(int i=2; i<message.length();i++){
        datamessage[i-2] = int(message[i]);
        std::cout <<datamessage[i-2];

        Go::receiveUpdates(datamessage[i-2],i-2);
    }
        Go::updateEntireBoard();

    }
    if(type==1){
        int datamessage[64];

        for(int i=2; i<message.length();i++){
            datamessage[i-2] = int(message[i]);
            std::cout <<datamessage[i-2];

            Chess::receiveUpdates(datamessage[i-2],i-2);
        }


    }
    if(type==8){
        int len=message.length()-2;
        vector <char> data;
        for(int i =0;i<(len);i++){
            data.push_back(char(message[i+2]));
        }
        handleReply2(data,data.size());

    }
}
void Client::handleReply2(vector<char> data, int size){
    string debugout="ff";
    debugout+=size;
    for(int i=0; i<size; i++)
        debugout+=char(int(data[i])+48);
    debugout+="f";
//    QMessageBox::information(
//        new QMessageBox(),
//        tr("Debug Window"),
//        QString::fromStdString(debugout));//debuging purposes delete
    if(int(data[0])==3){
        int counter=0;
        int checkifdelimited=0;
        GameManager::games.clear();
        for(int i=2; i<size; i+=3){
            if(data[i]=='i'){
                counter++;
                checkifdelimited=0;
            }
            else if(checkifdelimited==0){
                vector<int>player={int(data[i+2]),int(data[i+1]),int(data[i])};
                GameManager::games.push_back({player});
                checkifdelimited=1;
            }
            else if(i+2<size){
                vector<int> player = {int(data[i+2]),int(data[i+1]),int(data[i])};
                GameManager::games[counter].push_back(player);
            }
        }

    }
    else if(int(data[0])==4){

    }
    else if(int(data[0])==5){
        GameManager::clientID=int(data[1]);
        int pid1=GameManager::clientID;
        int request1[5]={3,1,0,0,0};
        makeRequest(request1,pid1);
    }
}
void Client::handleReply(vector<int> data,int size){
    //updates central ui to include things like
    //games avail per game type
    //and info about each of thus games such as who is spectating
    //and who is actually playing.
    if(data[0]==3){//getting gameids based on gametype
        int gType=data[1];
        //GameManager *temp1 = new GameManager();
        for(int i =2; i<size; i++){
            GameManager *temp=new GameManager();
            temp->addPlayer(temp,temp);
            temp->gameID=data[i];
            temp->gameType=gType;
            int gID=data[i];
            int requests[5]={4,gID,0,0,0};
            int pid=GameManager::clientID;
            makeRequest(requests,pid);

        }
    }
    else if(data[0]==4){
        int gID=data[1];
        GameManager *temp1;
        temp1=temp1->findGame3(gID);
        int gType= temp1->gameType;
        for(int i=2; i<size;i+=2){
            GameManager *temp=new GameManager();
            if(i!=2)
                temp->addPlayer(temp1,temp);
            temp->playerid=data[i];
            if(data[i+1]==1)
                temp->player=true;
            else
                temp->player=false;
            temp->gameID=gID;
            temp->gameType=gType;

        }
    }
    else if(data[0]==5){
        GameManager::clientID=data[1];
        int request1[5]={3,1,0,0};
        int request2[5]={3,2,0,0};
        int request3[5]={3,3,0,0};
        int request4[5]={3,4,0,0};
        int pid1=GameManager::clientID;

        makeRequest(request1,pid1);
        makeRequest(request2,pid1);
        makeRequest(request3,pid1);
        makeRequest(request4,pid1);
    }
}
void Client::makeRequest(int requestID[5],int playerid){
    QByteArray output;
    output.append(char(playerid));
    output.append(char(8));
    for(int i =0; i<5; i++){
        output.append((char(requestID[i])));

    }
    Client::s->write(output);
    Client::s->flush();
    Client::s->waitForBytesWritten(1000);
}
void Client::pingpong(){
    QByteArray message = socket->readAll();

    string datamessage;
    for(int i=2; i<message.length();i++){
        datamessage += char(message[i]);
    }
    cout << datamessage<<endl;
    GameMsg msg(int(message[1]),datamessage,int(message[0]),message.length());
    string data=msg.data;
    QByteArray output;

    int userid1=1;
    if(msg.userid==1) userid1=0;
    output.append(char(userid1));
    output.append(char(msg.type));

    output.append(QString::fromStdString(data));



    socket->write(output);
    socket->flush();
    socket->waitForBytesWritten(1000);
    //socket->waitForReadyRead(300);
}
void Client::sendGameMsg(GameMsg m){


}
