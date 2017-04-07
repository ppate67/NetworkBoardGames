#include "player.h"
#include "myserver.h"
#include "iostream"
#include "fstream"
using namespace std;
player::player(QObject *parent) : QObject(parent)
{
    for(int i =0; i<MAXNUMPLAYER; i++)
    {
        slist[i]=NULL;

    }
}
void player::SetSocket(int id){
	//launched when connection is orriginally established
	//static "slist" array is populated with the pointer to the socket object associated with this player 
socket = new QTcpSocket(this);
for(int i =0; i<MAXNUMPLAYER; i++){
    if((slist[i]==NULL)){
       slist[i]=socket;

       break;
    }

}
cout <<"test";
//signal and slot mechanisms that allow asynchronous behavior such as the ability for the server to handle 
//when a tcp message arrives on a socket connection
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
	//this method is called by the slot signal mechanism whenever a new TCP
	//message arrives to the server
	//The server then handles the TCP byte array by decomposing it into its header components
	// and its data payload components. Code branches off from there based on the header's type field.
	
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
    ofstream outputfile;
    outputfile.open("servergamelist.txt");

    for(int i =0; i<vecsize;i++){
		//the following is a set of server messages used for debugging purposes.
        int playsize= GameManager::games[i].size();
        for(int ii=0; ii<playsize;ii++){
            cout << "GameID " << i << endl;
            cout << "Gametype: " << GameManager::games[i][ii][0]<<endl;
            cout << "Playertype: " << GameManager::games[i][ii][1]<<endl;
            cout << "PlayerID: " << GameManager::games[i][ii][2]<<endl;
            outputfile <<  "GameID " << i << endl;
            outputfile << "Gametype: " << GameManager::games[i][ii][0]<<endl;
            outputfile << "Playertype: " << GameManager::games[i][ii][1]<<endl;
            outputfile << "PlayerID: " << GameManager::games[i][ii][2]<<endl;
        }
    }
    outputfile.close();
    for(int i=0; i<MAXNUMPLAYER; i++)
        if(&MyServer::plist[i]==this)
            ids=i;//finding the socket id of the client 
    if(type==8){
        handleRequest2(handledata,ids);//if the type is 8 then the server is dealing with a client request

        //broadcastGames();

    }
    else
        task(&msg);
}
void player::handleRequest2(int requestID[5],int playerID){

    if(requestID[0]==1){
        //do later
    }
    else if(requestID[0]==2){
		//handles request to add a player to a game based on gameid
		//if the gameid is larger than any currently in the vector then 
		//a new game is added
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




        }
        else{//on gametype
            int vecsize=GameManager::games.size();
            int gametype=requestID[4];
            int playertype = requestID[2];
            std::vector<int> newplayer={gametype,playertype,playerID};
            GameManager::games.push_back({newplayer});
        }
        broadcastGames();
    }
    else if(requestID[0]==3){
		//sends back a list of deliminited games (described by the player id, player type, and gametype)
        QByteArray output;
        ofstream outputfile;//debugging
        outputfile.open("messages.txt");//debugging purposes
        int gType=requestID[1];
        output.append(char(playerID));
        output.append(char(8));
        output.append(char(3));
        output.append(char(gType));
        outputfile<< 3 << gType;
        int counter=0;
        int vecsize=GameManager::games.size();

        for(int i =0; i<vecsize;i++){



            int playsize= GameManager::games[i].size();
            for(int ii=0; ii<playsize;ii++){
                output.append(GameManager::games[i][ii][2]);//player id
                output.append(GameManager::games[i][ii][1]);//player type
                output.append(GameManager::games[i][ii][0]);//gametype
                outputfile<<GameManager::games[i][ii][2]<<GameManager::games[i][ii][1]<<GameManager::games[i][ii][0];
            }
             output.append(char('i'));
             outputfile<<'i';

        }
        MyServer::plist[playerID].socket->write(output);
        MyServer::plist[playerID].socket->flush();

        MyServer::plist[playerID].socket->waitForBytesWritten(3000);
        cout << "Sent gameID list " << playerID <<endl;
    }
    else if(requestID[0]==4){
		//sends a list of players (described by their player id and player type) for a specific gameid
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
		//this is the response to the player requesting for its clientid
		//player wants to know their clientid so that they can know how to refer to themselves.
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
      //response to player request for a list of player usernames
	  
    }

}
void player::handleRequest(int requestID[5],int playerID){//fires if type of gamemsg was 8
    //removed and handleRequest2 is used instead
	//this used to do what handleRequest2 currently does but by using the pointer based data structure
	//instead of multidemsional vectors
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
    if(id>GameManager::games.size()){cout<<id<<"Error";return;}
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
                cout<<"Success";
            }
        }

    }
}
void player::broadcastGames(){
	//this method has not been implements yet but it
	//will be used to send a list of games to every player connected to the server
	//by doing this the client can maintain a constant up-to-date record of the games being played across the server
    for(int i=0; i<MAXNUMPLAYER; i++){
        int broadmsg[5]={3,1,1,1,1};
        if(MyServer::plist[i].filled!=0)
            handleRequest2(broadmsg,i);
    }
}
