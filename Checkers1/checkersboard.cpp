#include "checkersboard.h"
#include <QLabel>
#include <QtGui>
#include <QPushButton>

Checkers* checkersboard::tile[8][8] = {NULL};

void checkersboard::setup(QWidget *baseWidget)
{
    QLabel *outLabel = new QLabel(baseWidget);  // This block of code the window to be the size of the screen
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    QPushButton *button = new QPushButton("&Quit", baseWidget);
    button->setText("Quit");
    button->move(width/2-400,height/2);
    button->show();
    QObject::connect(button,SIGNAL(clicked()),baseWidget,SLOT(close()));
    outLabel->setGeometry((width/2)-(60*4)-20,(height/2)-(60*4)-20,60*8+40,60*8+40);

    outLabel->setStyleSheet("QLabel { background-color :rgb(178, 123, 60); color : black; }");

    int i,j,x,y,k=0;

    //Create board and allocate memory
    y=(height/2)-(60*4);
    for(i=0;i<8;i++)
    {
        x=(width/2)-(60*4);
        for(j=0;j<8;j++)
        {
            tile[i][j] = new Checkers(baseWidget);
            tile[i][j]->setTileColor((i+j)%2);
            tile[i][j]->setPiece(false);
            tile[i][j]->setRow(i);
            tile[i][j]->setColumn(j);
            tile[i][j]->setTileNum(k++);
            tile[i][j]->displayBoard();
            tile[i][j]->setGeometry(x,y,60,60);
            tile[i][j]->displayElement(' ');//sets all pieces to empty but later on we place the pieces
            x+=60;
        }
        y+=60;
    }

    //Black Pieces
    for(j=0;j<8;j+=2){
        tile[0][j]->setPiece(true);
        tile[0][j]->setPieceColor(0);
        tile[0][j]->displayElement('P');
        tile[2][j]->setPiece(true);
        tile[2][j]->setPieceColor(0);
        tile[2][j]->displayElement('P');
    }
    for(j=1;j<8;j+=2){
        tile[1][j]->setPiece(true);
        tile[1][j]->setPieceColor(0);
        tile[1][j]->displayElement('P');
    }

    //Red Pieces
    for(j=1;j<8;j+=2){
        tile[5][j]->setPiece(true);
        tile[5][j]->setPieceColor(1);
        tile[5][j]->displayElement('P');
        tile[7][j]->setPiece(true);
        tile[7][j]->setPieceColor(1);
        tile[7][j]->displayElement('P');
    }
    for(j=0;j<8;j+=2){
        tile[6][j]->setPiece(true);
        tile[6][j]->setPieceColor(1);
        tile[6][j]->displayElement('P');
    }
    //this will set up the pointers within each Chess object
    //having pointers in each object makes it easier to navigate between objects
    tile[0][0]->prevtile=nullptr;
    for(int ii=0;ii<8;ii++){
    for(int i=0;i<7;i++){
        tile[i][ii]->nexttile=tile[i+1][ii];
        tile[i+1][ii]->prevtile=tile[i][ii];
    }
    if(ii!=7){
        tile[7][ii]->nexttile=tile[0][ii+1];
        tile[0][ii+1]->prevtile=tile[7][ii];
    }
    else{
        tile[7][7]->nexttile=nullptr;

    }
    }
    Checkers::checkershead=tile[0][0];
}

bool checkersboard::isOccupied(int row, int col){
    if(tile[row][col]->getPiece())
        return true;
    return false;
}

