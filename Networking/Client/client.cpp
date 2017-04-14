#include "client.h"
#include "Go/go.h"
#include "Chess/chess.h"
#include "Checkers1/checkers.h"
#include "fstream"
#include "QMessageBox"
QTcpSocket* Client::s=NULL;
Client* Client::client=nullptr;
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
void Client::Connect(std::string address, int port){
    socket = new QTcpSocket(this);
    socket->connectToHost(QHostAddress(QString::fromStdString(address)),port);
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
    int clientid = GameManager::clientID;
    int vecsize=GameManager::games.size();
    ofstream outputfile;
    string path = "client";
    path+=char(clientid+48);
    path+="gamelist.txt";
    outputfile.open(path);

    for(int i =0; i<vecsize;i++){
        //the following is a set of server messages used for debugging purposes.
        int playsize= GameManager::games[i].size();
        for(int ii=0; ii<playsize;ii++){

            outputfile <<  "GameID " << i << endl;
            outputfile << "Gametype: " << GameManager::games[i][ii][0]<<endl;
            outputfile << "Playertype: " << GameManager::games[i][ii][1]<<endl;
            outputfile << "PlayerID: " << GameManager::games[i][ii][2]<<endl;
        }
    }
    outputfile.close();

    if(type==0){//go message
    int datamessage[169];

    for(int i=2; i<message.length();i++){
        datamessage[i-2] = int(message[i]);
        std::cout <<datamessage[i-2];

        Go::receiveUpdates(datamessage[i-2],i-2);
    }
        Go::updateEntireBoard();

    }
    if(type==1){//chess message
        int datamessage[64];


        for(int i=2; i<message.length();i++){
            datamessage[i-2] = int(message[i]);
            std::cout <<datamessage[i-2];
            Chess::receiveUpdates(datamessage[i-2],i-2);
        }


    }
    if(type==2){//checkers message
        int datamessage[64];
        for(int i=2; i<message.length(); i++){
            datamessage[i-2]=int(message[i]);//this is not optimal we could just use message[i] everywhere
            //make this change asap
            std:cout <<datamessage[i-2];
            Checkers::receiveUpdates(datamessage[i-2],i-2);

        }

    }
    if(type==8){
        int len=message.length()-2;
        vector <char> data;
        for(int i =0;i<(len);i++){
            data.push_back(char(message[i+2]));
        }
        handleReply2(data,len);

    }
}
void Client::handleReply2(vector<char> data, int size){
	//updates central ui to include things like
    //games avail per game type
    //and info about each of thus games such as who is spectating
    //and who is actually playing.
    string debugout="";
    for(int i=0; i<size; i++)
        debugout+=char(int(data[i])+48);

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
                i++;
            }
            if(checkifdelimited==0 && i+2<size){
                if(0*int(data[i+2])/4!=0)
                    ;//don't add to vector if it isn't a gametype between 0 and 3. Some error occurred
                else{
                    vector<int>player={int(data[i+2]),int(data[i+1]),int(data[i])};
                    GameManager::games.push_back({player});
                    checkifdelimited=1;
                }
            }
            else if(i+2<size){
                if(0*int(data[i+2])/4!=0)
                    ;//don't add to vector if it isn't a gametype between 0 and 3. Some error occurred
                else{
                    vector<int> player = {int(data[i+2]),int(data[i+1]),int(data[i])};
                    GameManager::games[counter].push_back(player);
                }
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
//not used anymore. Need to investigate if using a data structure full
//of pointers would make for a more efficient handleReply
}
void Client::makeRequest(int requestID[5],int playerid){
    QByteArray output;
    output.append(char(playerid));
    output.append(char(8));
    string debugout="";
    for(int i =0; i<5; i++){
        output.append((char(requestID[i])));
        debugout+=char(requestID[i]+48);
    }
//        QMessageBox::information(
//            new QMessageBox(),
//            tr("Debug Window"),
//            QString::fromStdString(debugout));//debuging purposes delete
    Client::s->write(output);
    Client::s->flush();
    Client::s->waitForBytesWritten(1000);


}
void Client::pingpong(){
    //method to pingpong data between two clients
	//deleted because it is no longer needed
}
void Client::sendGameMsg(GameMsg m){


}

//void Client::SetPlayerName(int requestID[6],int playerid){ //requestID 6 for settingplayername
//    bool ok;
//    QString name = QInputDialog::getText(this, tr("QInputDialog::getText()"),
//                                         tr("User name:"), QLineEdit::Normal,
//                                         QDir::home().dirName(), &ok);
//    if (ok && !text.isEmpty())
//        textLabel->setText(text);

//    //add playername to vector of playernames at end of function
//    addPlayerName(name);
//}
