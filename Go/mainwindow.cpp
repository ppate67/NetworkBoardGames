#include "Go/mainwindow.h"
#include "ui_mainwindow.h"
#include "QGraphicsScene"
#include <QtGui>
#include <QApplication>
#include "iostream"
#include "QRadioButton"
#include "QHBoxLayout"
#include "QGraphicsOpacityEffect"
#include "QMessageBox"
#include "QTextEdit"
#include "QGroupBox"
#include "QInputDialog"
#include "QScrollArea"
#include "Monopoly/Monopoly_graphics/monopolyboard.h"
int gameidtojoin=-1;
int MainWindow::offline=0;
bool MainWindow::victory=false;
monopolyboard* m =nullptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int requestID[5]={5,0,0,0,0};
    int playerid=GameManager::clientID;//doesn't matter because the purpose of this request is to find the client's player id from the server
    Client::makeRequest(requestID,playerid);
    GameManager::games.clear();
    populateList(5);
    connect(ui->action,SIGNAL(triggered()),this,SLOT(changeServer()));
    connect(ui->actionChat,SIGNAL(triggered()),this,SLOT(initiateChat()));

}

MainWindow::~MainWindow()
{
    Client::s->close();
    delete ui;
}
Go *tile[13][13]={{NULL}};
GoBoard *cc;
void MainWindow::populateList2(int size){
    //populates the listWidget that users click on to join a game with someone over the server
    ui->listWidget->clear();
    int vecsize=GameManager::games.size();
    for(int i=0; i<vecsize;i++){
        string rowtitle="Player: ";
        string rowtitlepart2=" Spectators: ";
        string game="";
        if(GameManager::games[i][0][0]==0)//go
            game="Go: ";
        else if(GameManager::games[i][0][0]==1)//chess
            game="Chess: ";
        else if(GameManager::games[i][0][0]==2)//checkers
            game="Checkers: ";
        else if(GameManager::games[i][0][0]==3)//monopoly
            game="Monopoly: ";
        else{
            string debug="";
            debug+="Failure: ";debug+=GameManager::games[i][0][0];
            QMessageBox::information(
                    new QMessageBox(),
                   tr("Debug Window"),
                    QString::fromStdString(debug));//debuging purposes delete
        }
        int playsize = GameManager::games[i].size();
        for(int ii=0;ii<playsize; ii++){
            if(GameManager::games[i][ii][1]==1)
                rowtitle += " "+char(GameManager::games[i][ii][2]+48);
            else
                rowtitlepart2+=" "+char(GameManager::games[i][ii][2]+48);
        }
        string title = game + rowtitle + rowtitlepart2;
        const char* title1= title.c_str();
        QListWidgetItem *radbutton=new QListWidgetItem(ui->listWidget);
        radbutton->setData(Qt::UserRole,i);

        ui->listWidget->setItemWidget(radbutton, new QRadioButton(tr((title1))));

    }
}
void MainWindow::populateList(int size){
//    GameManager* temp = GameManager::head;

//    ui->listWidget->clear();
//    while(temp!=nullptr){
//        GameManager* ptemp=temp;
//        string rowtitle="Player: ";
//        string rowtitlepart2=" Spectators: ";
//        string game="";
//        if(ptemp->gameType==0)//go
//            game="Go: ";
//        else if(ptemp->gameType==1)//chess
//            game="Chess: ";
//        else if(ptemp->gameType==2)//checkers
//            game="Checkers: ";
//        else//monopoly
//            game="Monopoly: ";

//        while(ptemp!=nullptr){
//            if(ptemp->player==true)
//                rowtitle += " "+ptemp->playerid;
//            else
//                rowtitlepart2+=" "+ptemp->playerid;
//            ptemp=ptemp->nextPlayer;
//        }
//        string title = game + rowtitle + rowtitlepart2;
//        const char* title1= title.c_str();
//        QListWidgetItem *radbutton=new QListWidgetItem(ui->listWidget);
//        radbutton->setData(Qt::UserRole,temp->gameID);

//        ui->listWidget->setItemWidget(radbutton, new QRadioButton(tr((title1))));
//        temp=temp->nextGame;
//     }

}
void MainWindow::on_pushButton_clicked()
{
    //"Launch Window" button. joins game that is selected in the listWidget.
    //if no game is selected in the listWidget then is does nothing
    //launches game associated with the clist list item and informs the server
    if(gameidtojoin!=-1){
    QWidget *myWidget = new QWidget();
        QScreen *screen = QGuiApplication::primaryScreen();
        QRect  screenGeometry = screen->geometry();
        int height = screenGeometry.height()/2;
        int width = screenGeometry.width()/2;
        myWidget->setGeometry(width/2,height/2,width,height);

        int gametype=1;
        int mode =1;//whether spectator or player. Default to player.
        for(int i=0; i<GameManager::games.size();i++)
            if(i==gameidtojoin){
                gametype=GameManager::games[i][0][0];
                if(GameManager::games[i].size()>=2)
                    mode=0;//automatically sets to spectate mode if there are already two players
            }
        int requestID[5]={2,gameidtojoin,mode,1,gametype};
        int playerid=GameManager::clientID;
        Client::makeRequest(requestID,playerid);

        if(gametype==0){
            GoBoard c;
            cc=&c;
                Go *tile[13][13]={{NULL}};
                Go::color=1;

                Go::turn=0;
                c.display(myWidget,tile);
                myWidget->show();

                myWidget->setAttribute( Qt::WA_DeleteOnClose );
                connect(myWidget, SIGNAL(destroyed()), this, SLOT(leaveGo()));


        }
        else if(gametype==1){


            chessboard c;

            c.setup(myWidget);

            myWidget->show();
            myWidget->setAttribute( Qt::WA_DeleteOnClose );
            connect(myWidget, SIGNAL(destroyed()), this, SLOT(leaveChess()));

            Chess::playercolor=1;
            Chess::chessturn=0;
        }
        else if(gametype==2){
            checkersboard c;
            c.setup(myWidget);
            myWidget->show();
            myWidget->setAttribute( Qt::WA_DeleteOnClose );
            connect(myWidget, SIGNAL(destroyed()), this, SLOT(leaveCheckers()));

            Checkers::playercolor=1;
            Checkers::checkersturn=0;

        }
        else if(gametype==3){
            m = new monopolyboard;
            m->show();
            monopolyboard::turn=0;
        }
}


}

void MainWindow::leaveGo(){
    //informs the server that the player is leaving the Go game
    //calls endingScreen which in turn displays the victory or defeat window.
    int gameid=0;
    int playindex=0;
    bool screenType = victory;
    victory=false;
    for(int i=0; i<GameManager::games.size(); i++){
        int playsize= GameManager::games[i].size();
        for(int ii=0; ii<playsize; ii++)
            if(GameManager::games[i][ii][2]==GameManager::clientID && GameManager::games[i][ii][0]==0){
                gameid=i;
                playindex=ii;
            }
    }
    int requestID[5]={1,gameid,playindex,0,0};//msg type (delete), gameID, 0, 0,0
    int playerid=GameManager::clientID;
    Client::makeRequest(requestID,playerid);
    int vecsize=GameManager::games.size();
    for(int i =0; i<vecsize; i++){
        int playsize=GameManager::games[i].size();
        for(int ii=0; ii<playsize;ii++){
            if(GameManager::games[i][ii][2]==GameManager::clientID && GameManager::games[i][ii][1]==1)
                endingScreen(screenType);
        }
    }

    //delete cc;
}
void MainWindow::leaveChess(){
    //informs the server that the player is leaving the Chess game
    //calls endingScreen which in turn displays the victory or defeat window.
    int gameid=0;
    int playindex=0;
    bool screenType = victory;
    victory=false;
    for(int i=0; i<GameManager::games.size(); i++){
        int playsize= GameManager::games[i].size();
        for(int ii=0; ii<playsize; ii++)
            if(GameManager::games[i][ii][2]==GameManager::clientID && GameManager::games[i][ii][0]==1){
                gameid=i;
                playindex=ii;
            }
    }
    int requestID[5]={1,gameid,playindex,0,0};//msg type (delete), gameID, 0, 0,0
    int playerid=GameManager::clientID;
    Client::makeRequest(requestID,playerid);

    int vecsize=GameManager::games.size();
    for(int i =0; i<vecsize; i++){
        int playsize=GameManager::games[i].size();
        for(int ii=0; ii<playsize;ii++){
            if(GameManager::games[i][ii][2]==GameManager::clientID && GameManager::games[i][ii][1]==1)
                 endingScreen(screenType);
        }
    }


    //delete cc;
}
void MainWindow::leaveCheckers(){
    //informs the server that the player is leaving the Checkers game
    //calls endingScreen which in turn displays the victory or defeat window.
    int gameid=0;
    int playindex=0;
    bool screenType = victory;
    victory=false;
    for(int i=0; i<GameManager::games.size(); i++){
        int playsize= GameManager::games[i].size();
        for(int ii=0; ii<playsize; ii++)
            if(GameManager::games[i][ii][2]==GameManager::clientID && GameManager::games[i][ii][0]==2){
                gameid=i;
                playindex=ii;
            }
    }
    int requestID[5]={1,gameid,playindex,0,0};//msg type (delete), gameID, 0, 0,0
    int playerid=GameManager::clientID;
    Client::makeRequest(requestID,playerid);

    int vecsize=GameManager::games.size();
    for(int i =0; i<vecsize; i++){
        int playsize=GameManager::games[i].size();
        for(int ii=0; ii<playsize;ii++){
            if(GameManager::games[i][ii][2]==GameManager::clientID && GameManager::games[i][ii][1]==1)
                endingScreen(screenType);
        }
    }


    //delete cc;
}

void MainWindow::on_pushButton_3_clicked()
{

    //checks the largest gameid val
    int counter=GameManager::games.size();


    //counter++;

    //create go game and inform the server of the new go game
    int gametype=0;
    int requestID[5]={2,counter,1,0,gametype};//based on gametype
    int playerid=GameManager::clientID;
    if(offline==0)
        Client::makeRequest(requestID,playerid);
    QWidget *myWidget = new QWidget();
        QScreen *screen = QGuiApplication::primaryScreen();
        QRect  screenGeometry = screen->geometry();
        int height = screenGeometry.height()/2;
        int width = screenGeometry.width()/2;
        myWidget->setGeometry(width/2,height/2,width,height);
    GoBoard c;
    cc=&c;
        Go *tile[13][13]={{NULL}};

        c.display(myWidget,tile);
        myWidget->show();
        myWidget->setAttribute( Qt::WA_DeleteOnClose );
        connect(myWidget, SIGNAL(destroyed()), this, SLOT(leaveGo()));
        Go::offline=offline;
}

void MainWindow::on_pushButton_2_clicked()
{
    //create chess game window. Inform the server of the new chess game
    int counter=GameManager::games.size();
    int gametype=1;
    int requestID[5]={2,counter,1,0,gametype};
    int playerid=GameManager::clientID;
    if(offline==0)
        Client::makeRequest(requestID,playerid);
    QWidget *myWidget = new QWidget();
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    myWidget->setGeometry(0,0,width,height);

    chessboard c;

    c.setup(myWidget);

    myWidget->show();
    myWidget->setAttribute( Qt::WA_DeleteOnClose );
    connect(myWidget, SIGNAL(destroyed()), this, SLOT(leaveChess()));
    Chess::offline=offline;
}

void MainWindow::on_pushButton_5_clicked()
{
    //create checkers game and inform the server fo the new checkers game
    int counter=GameManager::games.size();
    int gametype=2;
    int requestID[5]={2,counter,1,0,gametype};
    int playerid=GameManager::clientID;
    Client::makeRequest(requestID,playerid);
    QWidget *myWidget = new QWidget();
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    myWidget->setGeometry(0,0,width,height);

    checkersboard c;

    c.setup(myWidget);

    myWidget->show();
    myWidget->setAttribute( Qt::WA_DeleteOnClose );
    connect(myWidget, SIGNAL(destroyed()), this, SLOT(leaveCheckers()));
    Checkers::offline=offline;
}

void MainWindow::on_pushButton_4_clicked()
{
    //request server to add monopoly game to register
    int counter=GameManager::games.size();
    int gametype=3;
    int requestID[5]={2,counter,1,0,gametype};
    int playerid=GameManager::clientID;
    Client::makeRequest(requestID,playerid);
    //create monopoly game
    m=new monopolyboard();
    m->show();
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    //this is to change the radio button -game id
    gameidtojoin=item->data(Qt::UserRole).toInt();


}

void MainWindow::on_pushButton_6_clicked()
{
    populateList2(5);
}

void MainWindow::on_listWidget_itemActivated(QListWidgetItem *item)
{
    gameidtojoin=item->data(Qt::UserRole).toInt();

}
void MainWindow::on_listWidget_itemChanged(QListWidgetItem *item)
{
    gameidtojoin=item->data(Qt::UserRole).toInt();

}
void MainWindow::endingScreen(bool victory){
    //this screen will popup when ever the game has ended and will inform the user if they won or lost
        QWidget *myWidget = new QWidget();
        QScreen *screen = QGuiApplication::primaryScreen();
        QRect  screenGeometry = screen->geometry();
        int height = screenGeometry.height();
        int width = screenGeometry.width();
        myWidget->setGeometry(width/4,height/4,480,480);
        myWidget->show();
         QMovie *gif;
        if(victory)
            gif = new QMovie(":/Icons2/victory.gif");
        else
            gif = new QMovie(":/Icons2/defeat.gif");
        QLabel *Background = new QLabel(myWidget);
        Background->setGeometry(0,0,480,480);

        QGraphicsScene scene;
        Background->setMovie(gif);
        Background->setScaledContents(true);
        QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(myWidget);
        Background->setGraphicsEffect(effect);
        gif->start();
        myWidget->setAttribute( Qt::WA_DeleteOnClose );
        Background->show();

}
void MainWindow::changeServer(){
    //method used to change the server the client is connected to
    std::string address ="";
    address = QInputDialog::getText(this,"Server Address","Input the server address here as text.").toStdString();

    int port = 1234;
    string temp = QInputDialog::getText(this,"Server Address","Input the server port here as a number.").toStdString();
    if(std::stoi(temp)<=65535 && std::stoi(temp)>=0)
        port =std::stoi(temp);
    Client::client->s->close();
    Client::client->socket->close();
    Client::client->Connect(address,port);

    int requestID[5]={5,0,0,0,0};
    int playerid=GameManager::clientID;//doesn't matter because the purpose of this request is to find the client's player id from the server
    Client::makeRequest(requestID,playerid);
    GameManager::games.clear();

}
ChatWindow* w=nullptr;
QLabel* chatlog;
void MainWindow::initiateChat(){
    //prompts user for their username and then opens chat window
    int userID =GameManager::clientID;
    bool loggedIn=false;
    for(int i=0;i<GameManager::playerList.size();i++)
        if(userID==int(GameManager::playerList[i][0]))
            loggedIn=true;
    if(loggedIn==false){//we prompt the user for their username and then inform the server what it is. The server will then tell everyone else what it is.
        std::string name ="";
        name = QInputDialog::getText(this,"New Player Tag","Input the player name you wish to go by.").toStdString();

        QByteArray output;
        output.append(char(userID));
        output.append(char(8));
        output.append(char(7));
        string debugout="";
        output.append((char(userID)));
        for(int i =0; i<name.size(); i++){

            output.append(name[i]);
        }

        Client::s->write(output);
        Client::s->flush();
        Client::s->waitForBytesWritten(1000);
    }
    //now we make the chat Window! This means we need to make it so that it runs seperately from the mainwindow ... aka a popup
    if(w==nullptr){
    QDialog *chatWindow = new QDialog();
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    chatWindow->setGeometry(this->x()-315,this->y(),315,345);
    QPushButton *button = new QPushButton("&Send", chatWindow);
    button->setText("Send Message");
    button->move(330-button->width(),345-button->height());
    button->show();
    QPushButton *refresh = new QPushButton("&Refresh", chatWindow);
    refresh->setText("Refresh List");
    refresh->move(0,0);
    refresh->show();
    chatWindow->show();

    QTextEdit *input = new QTextEdit(chatWindow);
    input->move(5,345-input->height());
    input->setGeometry(5,345-input->height(),300-button->width(),button->height());
    input->show();
    chatWindow->setAttribute( Qt::WA_DeleteOnClose );

    QObject::connect(chatWindow, SIGNAL(destroyed()), this, SLOT(deleteChat()));

    QListWidget *groupBox = new QListWidget(chatWindow);
    groupBox->move(0,20);

    QVBoxLayout *vbox = new QVBoxLayout(chatWindow);
    chatlog  = new QLabel(chatWindow);
    chatlog->setGeometry(110,10,200,300);
    chatlog->setText("Chat Log:");
    chatlog->setStyleSheet("QLabel {background-color:rgb(255, 255, 255);}");
    chatlog->setAlignment(Qt::AlignTop);
    chatlog->show();
    for(int i=0; i<10; i++){
       //QRadioButton *radio1 = new QRadioButton("&Radio button 1");
       //vbox->addWidget(radio1);
    }
       //QRadioButton *radio2 = new QRadioButton("R&adio button 2");
       //QRadioButton *radio3 = new QRadioButton("Ra&dio button 3");

       //vbox->addWidget(radio2);
       //vbox->addWidget(radio3);
       vbox->addStretch(1);
       groupBox->setLayout(vbox);

   groupBox->show();
    w=new ChatWindow();
    w->vbox=vbox;
    w->chatinput=input;
    w->chatWindow=chatWindow;
    w->refresh=refresh;
    w->button=button;
    w->groupBox=groupBox;
    w->setSlots(chatWindow);
    }
}

void MainWindow::deleteChat(){
    delete w;//deleting w whenever chat window closes since we no longer need the memory
    w=nullptr;
    delete chatlog;
    chatlog=nullptr;
}
void ChatWindow::setSlots(QWidget *baseWidget){
    QObject::connect(refresh,SIGNAL(clicked()),this,SLOT(refreshPlayerList()));
    QObject::connect(button,SIGNAL(clicked()),this,SLOT(sendChat()));

}

void ChatWindow::refreshPlayerList(){
    if(w!=nullptr){
        groupBox->clear();
        for(int i=0;i<GameManager::playerList.size();i++){
            string name = GameManager::playerList[i];
            QRadioButton *radio1 = new QRadioButton(QString::fromStdString(name));
            vbox->addWidget(radio1);
        }
        vbox->addStretch(1);
        groupBox->setLayout(vbox);
        groupBox->show();
    }
}
void ChatWindow::sendChat(){
    //sends text info inside the textinput over the socket interface
    int userID=0;
    QString text = chatinput->toPlainText();
    QByteArray output;

    output.append(char(userID));
    output.append(char(8));
    output.append(char(8));
    //output.append(char(8));
    output.append(char(userID));
    for(int i=0; i<text.size();i++)
        output.append(char(text.toStdString()[i]));
    Client::s->write(output);
    Client::s->flush();
    Client::s->waitForBytesWritten(1000);
    chatinput->clear();

}
void ChatWindow::receiveChatMessage(const string & msg){
    if(w!=nullptr){

        QString text = chatlog->text();
        string stdtext=text.toStdString();
        int ncount=0;
        for(int i=0;i<stdtext.size();i++){
            if('\n'==stdtext[i]){
                ncount++;

            }

        }
        string newtext="Chat Log: \n";
        if(ncount>18){
            int c=0;
            for(int i=0; i<stdtext.size(); i++){
                if(c>ncount-18){
                    newtext+=stdtext[i];
                }
                if(stdtext[i]=='\n')
                    c++;

            }
            newtext+='\n';
            newtext+=msg;
            chatlog->setText(QString::fromStdString(newtext));
        }
        //QString text = w->chatinput->toPlainText();
        else{
        text+='\n';
        text+=QString::fromStdString(msg);
        //chatlog->setText("Chat Log:");
        chatlog->setText(text);
        //w->chatinput->setText(text);
        }
    }
}
void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(offline==0)
        offline=1;
    else
        offline=0;
}




