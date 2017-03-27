#include "player.h"
#include "myserver.h"
#include "iostream"
using namespace std;
player::player(QObject *parent) : QObject(parent)
{
    for(int i =0; i<MAXNUMPLAYER; i++)
    {
        slist[i]=NULL;

    }
}
void player::SetSocket(int id){
socket = new QTcpSocket(this);
for(int i =0; i<MAXNUMPLAYER; i++){
    if((slist[i]==NULL)){
       slist[i]=socket;

       break;
    }

}
cout <<"test";
connect(socket, SIGNAL(connected()),this,SLOT(connected()));
connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
socket->setSocketDescriptor(id);


cout << " Client connected at " << id <<endl;
}

/*void player SetName(){
  string name;
  cout << "Please enter your player name." << endl;
  //make popup window for this, cin name and set playerName = name
  //add playername to vector of playernames at end of function
  addPlayerName(name);

}*/
void player :: connected(){}
void player :: disconnected(){}
void player :: readyRead(){

    QByteArray playerinput = socket->readAll();

    int length = playerinput.length();
    int gameid=int(playerinput[0]);
    int type = int(playerinput[1]);
    string data="";
    int handledata[5];
    string outputdata="";
    for(int i=2;i<length;i++){
        data += char(int(playerinput[i]));
        outputdata+=int(playerinput[i]);
        if(length==7){
            handledata[i-2]=int(playerinput[i]);
        }
    }
    cout << outputdata <<gameid<<endl;
    GameMsg msg(type,data,gameid,length);
    int ids=0;//id sender
    GameManager *temp = GameManager::head;
    int vecsize=GameManager::games.size();
    for(int i =0; i<vecsize;i++){

        int playsize= GameManager::games[i].size();
        for(int ii=0; ii<playsize;ii++){
            cout << "GameID " << i << endl;
            cout << "Gametype: " << GameManager::games[i][ii][0]<<endl;
            cout << "Playertype: " << GameManager::games[i][ii][1]<<endl;
            cout << "PlayerID: " << GameManager::games[i][ii][2]<<endl;
        }
    }
    for(int i=0; i<MAXNUMPLAYER; i++)
        if(&MyServer::plist[i]==this)
            ids=i;
    if(type==8)
        handleRequest2(handledata,ids);
    else
        task(&msg);
}
void player::handleRequest2(int requestID[5],int playerID){

    if(requestID[0]==1){
        //do later
    }
    else if(requestID[0]==2){
        if(requestID[3]==1){//on gameID
            int gameid=requestID[1];
            int gametype=requestID[4];
            int playertype = requestID[2];
            int vecsize=GameManager::games.size();
            for(int i=0; i<vecsize; i++){
                if(i==gameid){
                    std::vector<int> newplayer={gametype,playertype,playerID};
                    GameManager::games[i].push_back(newplayer);
                }
            }
            if(gameid>=vecsize || vecsize==0){
                std::vector<int> newplayer={gametype,playertype,playerID};
                GameManager::games.push_back({newplayer});
            }
        }
        else{//on gametype
            //do later
            cout << "OOPS Err must of occurred";
        }
    }
    else if(requestID[0]==3){
        QByteArray output;

        int gType=requestID[1];
        output.append(char(playerID));
        output.append(char(8));
        output.append(char(3));
        output.append(char(gType));
        int counter=0;
        int vecsize=GameManager::games.size();

        for(int i =0; i<vecsize;i++){



            int playsize= GameManager::games[i].size();
            for(int ii=0; ii<playsize;ii++){
                output.append(GameManager::games[i][ii][2]);
                output.append(GameManager::games[i][ii][1]);
                output.append(GameManager::games[i][ii][0]);
            }
             output.append(char('i'));
        }
        MyServer::plist[playerID].socket->write(output);
        MyServer::plist[playerID].socket->flush();

        MyServer::plist[playerID].socket->waitForBytesWritten(3000);
        cout << "Sent gameID list " << counter <<endl;
    }
    else if(requestID[0]==4){
        QByteArray output;
        output.append(char(playerID));
        output.append(char(8));
        output.append(char(4));//makes sure recipient handles as desired
        int gameid=requestID[1];
        output.append(char(gameid));

        int counter=0;
        int vecsize=GameManager::games.size();
        for(int i =0; i<vecsize; i++){
            int playsize= GameManager::games[i].size();
            for(int ii=0; ii<playsize;ii++){
                output.append(GameManager::games[i][ii][2]);
                output.append(GameManager::games[i][ii][1]);
            }
        }
        MyServer::plist[playerID].socket->write(output);
        MyServer::plist[playerID].socket->flush();
        cout<<"Sending player lists"<<counter<<endl;
        MyServer::plist[playerID].socket->waitForBytesWritten(3000);
    }
    else if(requestID[0]==5){
        int ids=0;//id sender
        QByteArray output;
        for(int i=0; i<MAXNUMPLAYER; i++)
            if(&MyServer::plist[i]==this)
                ids=i;
        output.append(char(0));
        output.append(char(8));
        output.append(char(5));
        output.append(char(ids));
        if(MyServer::plist[ids].filled==0) {}
        else{
            MyServer::plist[ids].socket->write(output);
            MyServer::plist[ids].socket->flush();

            MyServer::plist[ids].socket->waitForBytesWritten(3000);
            }
    }
    else if(requestID[0]==6){ //ID 6 for playername
      
    }

}
void player::handleRequest(int requestID[5],int playerID){//fires if type of gamemsg was 8
    if(requestID[0]==1){
        //remove player
        GameManager *temp;
        int gameid=GameManager::findGame1(playerID)->gameID;
        GameManager* gameptr=GameManager::findGame3(gameid);
        temp->removePlayer(GameManager::findGame1(playerID),gameptr);
        //requestID[1]->gameID
    }
    else if(requestID[0]==2){
        //add player requestID[1]->gameID or gametype
        //requestID[2]->player vs spectator
        //requestID[3]->base it on gameID vs gametype

            GameManager *newplayer=new GameManager();
            newplayer->playerid=playerID;
            GameManager* game;
            int counter=0;
            int gameID=0;
            if(requestID[3]==1){//on gameID
                game = GameManager::findGame3(requestID[1]);
                gameID=requestID[1];
            }
            else{//on gametype
                game = GameManager::findGame2(requestID[1]);
            }
            GameManager* temp = GameManager::head;
            while(temp!=nullptr)
                if(temp->gameID>counter)
                    counter=temp->gameID;

            counter++;
            int gameType=1;
            if(game==nullptr){
                game=new GameManager();
                counter--;
                gameID=counter;

            }
            newplayer->addPlayer(game,newplayer);
            newplayer->gameType=gameType;//needs to be changed
            newplayer->gameID=gameID;
            if(requestID[2]==1){//player
                newplayer->player=true;
            }
            else{//spectator
                newplayer->player=false;
            }

        }
    else if(requestID[0]==3){//client requests gameids based on gametype
        //sends gameids,
        //requestID[1]->gametype go->1 chess->2 checkers->3 mono->4
        int ids=0;//id sender
        QByteArray output;

        int gType=requestID[1];
        output.append(char(playerID));
        output.append(char(8));
        output.append(char(3));
        output.append(char(gType));
        int counter=0;
        GameManager* temp=GameManager::head;
        while(temp!=NULL){
            if(temp->gameID==gType){
                output.append(char(temp->gameID));
                counter++;
            }
            temp=temp->nextGame;
        }
        MyServer::plist[playerID].socket->write(output);
        MyServer::plist[playerID].socket->flush();

        MyServer::plist[playerID].socket->waitForBytesWritten(3000);
        cout << "Sent gameID list " << counter <<endl;

    }
    else if(requestID[0]==4){//client requests game info based on gameid
        //sends  playerids alt'd with player type (player vs spectator)
        int ids=0;//id sender
        QByteArray output;
        output.append(char(playerID));
        output.append(char(8));
        output.append(char(4));//makes sure recipient handles as desired
        int gameid=requestID[1];
        output.append(char(gameid));
        GameManager* temp;
        int counter=0;
        temp=GameManager::findGame3(gameid);
        while(temp!=NULL){
            if(temp->playerid!=playerID){
                output.append(char(playerID));
                counter++;
                if(temp->player==true)
                    output.append(char(1));
                else
                    output.append(char(0));
            }
            temp=temp->nextPlayer;
        }
        MyServer::plist[playerID].socket->write(output);
        MyServer::plist[playerID].socket->flush();
        cout<<"Sending player lists"<<counter<<endl;
        MyServer::plist[playerID].socket->waitForBytesWritten(3000);
    }
    }


void player::task(GameMsg* msg){
    string data=msg->data;
    int ids=0;//id sender
    QByteArray output;
    for(int i=0; i<MAXNUMPLAYER; i++)
        if(&MyServer::plist[i]==this)
            ids=i;
    int id = msg->gameid;//id of game
    output.append(char(id));
    output.append(char(msg->type));
    if(id>GameManager::games.size()){cout<<id<<"DOGS";return;}
    output.append(QString::fromStdString(data));
    //we want to send a msg to everyone with the game id that does not have the sender's player id
    int playsize=GameManager::games[id].size();
    for(int i =0; i<playsize; i++){
        if(GameManager::games[id][i][2]!=ids){
            int pid=GameManager::games[id][i][2];
            if(MyServer::plist[pid].filled==0) {}
            else{
                MyServer::plist[pid].socket->write(output);
                MyServer::plist[pid].socket->flush();

                MyServer::plist[pid].socket->waitForBytesWritten(3000);
                cout<<"CATS";
            }
        }

    }
}
void player::broadcastGames(){
    for(int i=0; i<MAXNUMPLAYER; i++){
        int broadmsg[5]={3,1,1,1,1};
        if(MyServer::plist[i].filled!=0)
            handleRequest2(broadmsg,i);
    }
}
