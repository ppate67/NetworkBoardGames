#include "Go/mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QApplication>
#include "iostream"
#include "QRadioButton"
#include "QHBoxLayout"
#include "QMessageBox"
int gameidtojoin=-1;

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

}

MainWindow::~MainWindow()
{
    delete ui;
}
Go *tile[13][13]={{NULL}};
GoBoard *cc;
void MainWindow::populateList2(int size){
    ui->listWidget->clear();
    int vecsize=GameManager::games.size();
    for(int i=0; i<vecsize;i++){
        string rowtitle="Player: ";
        string rowtitlepart2=" Spectators: ";
        string game="";
        if(GameManager::games[i][0][0]==1)//go
            game="Go: ";
        else if(GameManager::games[i][0][0]==2)//chess
            game="Chess: ";
        else if(GameManager::games[i][0][0]==3)//checkers
            game="Checkers: ";
        else//monopoly
            game="Monopoly: ";
        int playsize = GameManager::games[i].size();
        for(int ii=0;ii<playsize; ii++){
            if(GameManager::games[i][ii][1]==1)
                rowtitle += " "+GameManager::games[i][ii][2];
            else
                rowtitlepart2+=" "+GameManager::games[i][ii][2];
        }
        string title = game + rowtitle + rowtitlepart2;
        const char* title1= title.c_str();
        QListWidgetItem *radbutton=new QListWidgetItem(ui->listWidget);
        radbutton->setData(Qt::UserRole,i);

        ui->listWidget->setItemWidget(radbutton, new QRadioButton(tr((title1))));

    }
}
void MainWindow::populateList(int size){
    GameManager* temp = GameManager::head;

    ui->listWidget->clear();
    while(temp!=nullptr){
        GameManager* ptemp=temp;
        string rowtitle="Player: ";
        string rowtitlepart2=" Spectators: ";
        string game="";
        if(ptemp->gameType==0)//go
            game="Go: ";
        else if(ptemp->gameType==1)//chess
            game="Chess: ";
        else if(ptemp->gameType==2)//checkers
            game="Checkers: ";
        else//monopoly
            game="Monopoly: ";

        while(ptemp!=nullptr){
            if(ptemp->player==true)
                rowtitle += " "+ptemp->playerid;
            else
                rowtitlepart2+=" "+ptemp->playerid;
            ptemp=ptemp->nextPlayer;
        }
        string title = game + rowtitle + rowtitlepart2;
        const char* title1= title.c_str();
        QListWidgetItem *radbutton=new QListWidgetItem(ui->listWidget);
        radbutton->setData(Qt::UserRole,temp->gameID);

        ui->listWidget->setItemWidget(radbutton, new QRadioButton(tr((title1))));
        temp=temp->nextGame;
     }

}
void MainWindow::on_pushButton_clicked()
{

    if(gameidtojoin!=-1){
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
        connect(myWidget, SIGNAL(destroyed()), this, SLOT(deleteBoard()));
        int gametype=0;
        for(int i=0; i<GameManager::games.size();i++)
            if(i==gameidtojoin)
                gametype=GameManager::games[i][0][0];
        int requestID[5]={2,gameidtojoin,1,1,gametype};
        int playerid=GameManager::clientID;
        Client::makeRequest(requestID,playerid);
        Go::color=1;
        Chess::playercolor=1;
        Chess::chessturn=0;
        Go::turn=0;
}


}
void MainWindow::deleteBoard(){
    for(int i=0; i<13; i++){
        for(int j=0;j<13;j++){
            //delete tile[i][j];
            Go::turn=1;
        }

    }
    //delete cc;
}

void MainWindow::on_pushButton_3_clicked()
{

    //checks the largest gameid val
    int counter=GameManager::games.size();


    //counter++;

    //create go game
    int gametype=0;
    int requestID[5]={2,counter,1,1,gametype};
    int playerid=GameManager::clientID;
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
        connect(myWidget, SIGNAL(destroyed()), this, SLOT(deleteBoard()));
}

void MainWindow::on_pushButton_2_clicked()
{
    //create chess game
    int counter=GameManager::games.size();
    int gametype=1;
    int requestID[5]={2,counter,1,1,gametype};
    int playerid=GameManager::clientID;
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

}

void MainWindow::on_pushButton_5_clicked()
{
    //create checkers game
}

void MainWindow::on_pushButton_4_clicked()
{
    //create monopoly game
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
