#include "goboard.h"
#include "QPushButton.h"
#include <QtGui>
#include "QMessageBox"
GoBoard::GoBoard()
{
      Go::opponentScore=0;
      Go::playerScore=0;
}
QLabel *score;
void GoBoard::display(QWidget *baseWidget,Go *tile[13][13])
{
    QLabel *outLabel = new QLabel(baseWidget);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    score  = new QLabel(baseWidget);
    score->move(width/2-60*15,height/2-40*13);
    QString scoreText = "Score (You): "; scoreText+=QString::number(Go::playerScore) + "\nScore (Opponent): " + QString::number(Go::opponentScore);
    score->setText(scoreText);
    score->show();
    QPushButton *button = new QPushButton("&Forfeit", baseWidget);
    button->setText("Forfeit");
    button->move(width/2-60*15,height/2-40*10);
    button->show();
    //QObject::connect(button,SIGNAL(clicked()),baseWidget,SLOT(forfeitclose()));
    outLabel->setGeometry((width/2)-(60*12)-20,(height/2)-(40*13)-20,40*13+40,40*13+40);

    outLabel->setStyleSheet("QLabel { background-color :rgb(178, 123, 60); color : black; }");

    int i,j,x,y,k=0;

    //Create board and allocate memory
    y=(height/2)-(40*13);
    for(i=0;i<13;i++)
    {
        x=(width/2)-(60*12);
        for(j=0;j<13;j++)
        {
            int type=0;
            tile[i][j] = new Go(baseWidget);
            tile[i][j]->setPiece(false);
            tile[i][j]->setRow(i);
            tile[i][j]->setColumn(j);
            tile[i][j]->setTileNum(k++);
            if((i==3 && j==3)||(i==3 && j==9)||(i==6 && j==6)||(i==9 && j==3)||(i==9 && j==9))
                type=0;//dot type
            else if(i>0 && i<12 && j >0 &&j<12)//middle type
                type=(1);
            else if(i>0 && i<12 && j==12)
                type=(5);//rightside type
            else if(i>0 && i<12 && j==0)//top type3
                type=(4);
            else if(i==0 && j<12 && j>0)
                type=(3);//left side type4
            else if(i==12 && j<12 && j>0)
                type=(2);//bottom type
            else if(i==0 && j==12)
                type=(7);//bottom left6
            else if(i==0 && j==0)
                type=(9);//top left7
            else if(i==12 && j==12)
                type=(8);//bottom right
            else if(i==12 && j==0)
                type=(6);//top right9
            tile[i][j]->displayBoard(type);
            tile[i][j]->setGeometry(x,y,40,40);
            tile[i][j]->type=type;
            x+=40;

        }
        y+=40;
    }
                tile[1][1]->setPiece(true);
                tile[1][1]->setPieceColor(0);
                tile[1][1]->displayElement(' ');
                tile[0][0]->prevtile=nullptr;
                for(int ii=0;ii<13;ii++){
                for(int i=0;i<12;i++){
                    tile[i][ii]->nexttile=tile[i+1][ii];
                    tile[i+1][ii]->prevtile=tile[i][ii];
                }
                if(ii!=12){
                    tile[12][ii]->nexttile=tile[0][ii+1];
                    tile[0][ii+1]->prevtile=tile[12][ii];
                }
                else{
                    tile[12][12]->nexttile=nullptr;

                }
                }
                Go::head=tile[0][0];
}
void GoBoard::forfeitclose(){
    //remove player from game on server
    this->removeplayer();

    QCoreApplication::quit();
}
void GoBoard::removeplayer(){
    int gameid=0;
    int playindex=0;
    for(int i=0; i<GameManager::games.size(); i++){
        int playsize= GameManager::games[i].size();
        for(int ii=0; ii<playsize; ii++)
            if(GameManager::games[i][ii][2]==GameManager::clientID && GameManager::games[i][ii][1]==1){
                gameid=i;
                playindex=ii;
            }
    }
    int requestID[5]={1,gameid,playindex,0,0};//msg type (delete), gameID, 0, 0,0
    int playerid=GameManager::clientID;
    Client::makeRequest(requestID,playerid);
}
void GoBoard::updateScores(){
    int pterr=0; int antiterr=0;
    if(Go::color==0){//white
        pterr=Go::wterr;
        antiterr=Go::blterr;
    }
    else{
        pterr=Go::blterr;
        antiterr=Go::wterr;
    }
    QString scoreText = "Score (You): "; scoreText+=QString::number(Go::playerScore+pterr) + "\nScore (Opponent): " + QString::number(Go::opponentScore+antiterr);
    score->setText(scoreText);
    score->show();

}
