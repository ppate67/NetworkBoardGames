#include "Chess/chessboard.h"
#include "Chess/chess.h"
#include <QLabel>
#include <QtGui>
#include <QPushButton>
#include "QMessageBox"

Chess* chessboard::tile[8][8] = {NULL};

void chessboard::setup(QWidget *baseWidget)
{
    QLabel *outLabel = new QLabel(baseWidget);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    //display player tags
    QLabel *player1=new QLabel(baseWidget);
    QLabel *player2=new QLabel(baseWidget);
    player1->setGeometry(width/2+300,height/2-260,400,100);
    player2->setGeometry(width/2+300,height/2+100,400,100);
    player1->setPixmap(QPixmap(":/Icons/Player1Logo.png"));
    player2->setPixmap(QPixmap(":/Icons/Player2Logo.png"));
    //quit button
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
            tile[i][j] = new Chess(baseWidget);
            tile[i][j]->setTileColor((i+j)%2);
            tile[i][j]->setPiece(false);
            tile[i][j]->setRow(i);
            tile[i][j]->setColumn(j);
            tile[i][j]->setTileNum(k++);
            tile[i][j]->displayBoard();
            tile[i][j]->setGeometry(x,y,64,64);
            tile[i][j]->displayElement(' ');//sets all pieces to empty but later on we place the pieces
            x+=60;
        }
        y+=60;
    }

    //white pawns
    for(j=0;j<8;j++)
    {
        tile[1][j]->setPiece(true);
        tile[1][j]->setPieceColor(0);
        tile[1][j]->displayElement('P');
    }

    //black pawns
    for(j=0;j<8;j++)
    {
        tile[6][j]->setPiece(true);
        tile[6][j]->setPieceColor(1);
        tile[6][j]->displayElement('P');
    }

    //white and black remaining elements
    for(j=0;j<8;j++)
    {
        tile[0][j]->setPiece(true);
        tile[0][j]->setPieceColor(0);
        tile[7][j]->setPiece(true);
        tile[7][j]->setPieceColor(1);
    }

    //black pieces
        tile[0][0]->displayElement('R');    //Rook
        tile[0][1]->displayElement('H');    //Knight
        tile[0][2]->displayElement('B');    //Bishop
        tile[0][3]->displayElement('Q');    //Queen
        tile[0][4]->displayElement('K');    //King
        tile[0][5]->displayElement('B');    //Bishop
        tile[0][6]->displayElement('H');    //Knight
        tile[0][7]->displayElement('R');    //Rook
    //white pieces
        tile[7][0]->displayElement('R');
        tile[7][1]->displayElement('H');
        tile[7][2]->displayElement('B');
        tile[7][3]->displayElement('Q');
        tile[7][4]->displayElement('K');
        tile[7][5]->displayElement('B');
        tile[7][6]->displayElement('H');
        tile[7][7]->displayElement('R');

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
        Chess::chesshead=tile[0][0];

}

bool chessboard::checkPath(int startRow, int startCol, int endRow, int endCol, char direction){
    switch(direction){
        case 'l':{ // straight line path
            if (startRow == endRow){
                if (startCol < endCol){ // moving right
                    for (int i = startCol + 1; i < endCol; i++){
                        if (tile[startRow][i]->getPiece() == true)
                            return false;
                    }
                }
                else { // moving left
                    for (int i = endCol + 1; i < startCol; i++){
                        if (tile[startRow][i]->getPiece() == true)
                            return false;
                    }
                }
            }
            else if (startCol == endCol){
                if (startRow < endRow){ // moving forward
                    for (int i = startRow + 1; i < endRow; i++){
                        if (tile[i][startCol]->getPiece() == true)
                            return false;
                    }
                }
                else { // moving backward
                    for (int i = endRow + 1; i < startRow; i++){
                        if (tile[i][startCol]->getPiece() == true)
                            return false;
                    }
                }
            }
            else {
                return false; // not moving in a straight line
            }
            return true; // the path is clear
        }
        case 'd':{ // diagonal path
            if (startRow == endRow || startCol == endCol){
                return false; // not a diagonal move
            }
            else if (abs(startRow - endRow) != abs(startCol - endCol)){
                return false; // is not an allowed diagonal move
            }
            if (startRow < endRow){ // moving down the board
                if (startCol < endCol){ // moving to the right
                    for (int i = 1; i < (endCol - startCol); i++){
                        if (tile[startRow+i][startCol+i]->getPiece() == true)
                            return false;
                    }
                }
                else { // moving to the left
                    for (int i = 1; i < (startCol - endCol); i++){
                        if (tile[startRow+i][startCol-i]->getPiece() == true)
                            return false;
                    }
                }
            }
            else if (endRow < startRow){ // moving up the board
                if (startCol < endCol){ // moving to the right
                    for (int i = 1; i < (endCol - startCol); i++){
                        if (tile[startRow-i][startCol+i]->getPiece() == true)
                            return false;
                    }
                }
                else { // moving to the left
                    for (int i = 1; i < (startCol - endCol); i++){
                        if (tile[startRow-i][startCol-i]->getPiece() == true)
                            return false;
                    }
                }
            }
            return true; // the path is clear
        }
    }
}

void chessboard::quitclicked()
{

    QCoreApplication::quit();
}

void chessboard::drawpath(Chess *t)
{
    int rw=t->getRow(),co=t->getColumn();
    if(t->getPiece())//if there is any piece
    {
        if(t->getPieceName()=='P'&&t->getPieceColor())//if it's white pawn
        {
            if(rw!=0)
            {
                if(rw==6)//if it's at initial position
                {
                    if(tile[rw-1][co]->getPiece()==false)
                    {
                        tile[rw-1][co]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                            if(tile[rw-2][co]->getPiece()==false)
                                tile[rw-2][co]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                    }
                }
                else
                {
                    if(tile[rw-1][co]->getPiece()==false)
                        tile[rw-1][co]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                }
                if(rw-1>=0&&co-1>=0)
                {
                    if(tile[rw-1][co-1]->getPiece()&&tile[rw-1][co-1]->getPieceColor()==0)
                        tile[rw-1][co-1]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                }
                if(rw-1>=0&&co+1<=7)
                {
                    if(tile[rw-1][co+1]->getPiece()&&tile[rw-1][co+1]->getPieceColor()==0)
                        tile[rw-1][co+1]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                }
            }
        }
        else if(t->getPieceName()=='P'&&t->getPieceColor()==false)//if it's black pawn
        {
            if(rw!=7)
            {
                if(rw==1)//if it's at initial position
                {
                    if(tile[rw+1][co]->getPiece()==false)
                    {
                        tile[rw+1][co]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                        if(tile[rw+2][co]->getPiece()==false)
                            tile[rw+2][co]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                    }
                }
                else
                {
                    if(tile[rw+1][co]->getPiece()==false)
                        tile[rw+1][co]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                }
                if(rw+1<=7&&co+1<=7)
                {
                    if(tile[rw+1][co+1]->getPiece()&&tile[rw+1][co+1]->getPieceColor()==1)
                        tile[rw+1][co+1]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                }
                if(rw+1<=7&&co-1>=0)
                {
                    if(tile[rw+1][co-1]->getPiece()&&tile[rw+1][co-1]->getPieceColor()==1)
                        tile[rw+1][co-1]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                }
            }
        }
        else if(t->getPieceName()=='R')
        {
            //left
            for(int i=co-1;i>=0;i--)
            {
                if(tile[rw][i]->getPiece()==false)
                    tile[rw][i]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                else
                {
                    if(tile[rw][i]->getPieceColor()!=t->getPieceColor())
                        tile[rw][i]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                    break;
                }
            }
            //right
            for(int i=co+1;i<=7;i++)
            {
                if(tile[rw][i]->getPiece()==false)
                    tile[rw][i]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                else
                {
                    if(tile[rw][i]->getPieceColor()!=t->getPieceColor())
                        tile[rw][i]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                    break;
                }
            }
            //forward
            for(int i=rw+1;i<=7;i++)
            {
                if(tile[i][co]->getPiece()==false)
                    tile[i][co]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                else
                {
                    if(tile[i][co]->getPieceColor()!=t->getPieceColor())
                        tile[i][co]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                    break;
                }
            }
            //backward
            for(int i=rw-1;i>=0;i--)
            {
                if(tile[i][co]->getPiece()==false)
                    tile[i][co]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                else
                {
                    if(tile[i][co]->getPieceColor()!=t->getPieceColor())
                        tile[i][co]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                    break;
                }
            }
        }
        else if(t->getPieceName()=='H')
        {
            //all positions where a knight can move. Check if out of bounds and if move is valid
            if(co-1>=0&&rw-2>=0)
            {
                if(tile[rw-2][co-1]->getPiece()==false||tile[rw-2][co-1]->getPieceColor()!=t->getPieceColor())
                    tile[rw-2][co-1]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
            }
            if(co+1<=7&&rw-2>=0)
            {
                if(tile[rw-2][co+1]->getPiece()==false||tile[rw-2][co+1]->getPieceColor()!=t->getPieceColor())
                    tile[rw-2][co+1]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
            }
            if(co-1>=0&&rw+2<=7)
            {
                if(tile[rw+2][co-1]->getPiece()==false||tile[rw+2][co-1]->getPieceColor()!=t->getPieceColor())
                    tile[rw+2][co-1]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
            }
            if(co+1<=7&&rw+2<=7)
            {
                if(tile[rw+2][co+1]->getPiece()==false||tile[rw+2][co+1]->getPieceColor()!=t->getPieceColor())
                    tile[rw+2][co+1]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
            }
            if(co-2>=0&&rw-1>=0)
            {
                if(tile[rw-1][co-2]->getPiece()==false||tile[rw-1][co-2]->getPieceColor()!=t->getPieceColor())
                    tile[rw-1][co-2]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
            }
            if(co+2<=7&&rw-1>=0)
            {
                if(tile[rw-1][co+2]->getPiece()==false||tile[rw-1][co+2]->getPieceColor()!=t->getPieceColor())
                    tile[rw-1][co+2]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
            }
            if(co-2>=0&&rw+1<=7)
            {
                if(tile[rw+1][co-2]->getPiece()==false||tile[rw+1][co-2]->getPieceColor()!=t->getPieceColor())
                    tile[rw+1][co-2]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
            }
            if(co+2<=7&&rw+1<=7)
            {
                if(tile[rw+1][co+2]->getPiece()==false||tile[rw+1][co+2]->getPieceColor()!=t->getPieceColor())
                    tile[rw+1][co+2]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
            }
        }
        else if(t->getPieceName()=='B')
        {
            //left-top
            for(int i=rw-1,j=co-1;i>=0&&j>=0;i--,j--)
            {
                if(tile[i][j]->getPiece()==false)
                    tile[i][j]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                else
                {
                    if(tile[i][j]->getPieceColor()!=t->getPieceColor())
                        tile[i][j]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                    break;
                }
            }
            //left-bottom
            for(int i=rw+1,j=co-1;i<=7&&j>=0;i++,j--)
            {
                if(tile[i][j]->getPiece()==false)
                    tile[i][j]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                else
                {
                    if(tile[i][j]->getPieceColor()!=t->getPieceColor())
                        tile[i][j]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                    break;
                }
            }
            //right-top
            for(int i=rw-1,j=co+1;i>=0&&j<=7;i--,j++)
            {
                if(tile[i][j]->getPiece()==false)
                    tile[i][j]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                else
                {
                    if(tile[i][j]->getPieceColor()!=t->getPieceColor())
                        tile[i][j]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                    break;
                }
            }
            //right-bottom
            for(int i=rw+1,j=co+1;i<=7&&j<=7;i++,j++)
            {
                if(tile[i][j]->getPiece()==false)
                    tile[i][j]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                else
                {
                    if(tile[i][j]->getPieceColor()!=t->getPieceColor())
                        tile[i][j]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                    break;
                }
            }
        }
        else if(t->getPieceName()=='K')
        {
            //left
            if(co-1>=0)
            {
                if(tile[rw][co-1]->getPiece()==false)
                    tile[rw][co-1]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                else
                {
                    if(tile[rw][co-1]->getPieceColor()!=t->getPieceColor())
                        tile[rw][co-1]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                }
            }
            //right
            if(co+1<=7)
            {
                if(tile[rw][co+1]->getPiece()==false)
                    tile[rw][co+1]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                else
                {
                    if(tile[rw][co+1]->getPieceColor()!=t->getPieceColor())
                        tile[rw][co+1]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                }
            }
            //forward
            if(rw-1>=0)
            {
                if(tile[rw-1][co]->getPiece()==false)
                    tile[rw-1][co]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                else
                {
                    if(tile[rw-1][co]->getPieceColor()!=t->getPieceColor())
                        tile[rw-1][co]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                }
            }
            //backward
            if(rw+1<=7)
            {
                if(tile[rw+1][co]->getPiece()==false)
                    tile[rw+1][co]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                else
                {
                    if(tile[rw+1][co]->getPieceColor()!=t->getPieceColor())
                        tile[rw+1][co]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                }
            }
            //left-top
            if(rw-1>=0&&co-1>=0)
            {
                if(tile[rw-1][co-1]->getPiece()==false)
                    tile[rw-1][co-1]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                else
                {
                    if(tile[rw-1][co-1]->getPieceColor()!=t->getPieceColor())
                        tile[rw-1][co-1]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                }
            }
            //right-top
            if(rw-1>=0&&co+1<=7)
            {
                if(tile[rw-1][co+1]->getPiece()==false)
                    tile[rw-1][co+1]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                else
                {
                    if(tile[rw-1][co+1]->getPieceColor()!=t->getPieceColor())
                        tile[rw-1][co+1]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                }
            }
            //left-bottom
            if(rw+1<=7&&co-1>=0)
            {
                if(tile[rw+1][co-1]->getPiece()==false)
                    tile[rw+1][co-1]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                else
                {
                    if(tile[rw+1][co-1]->getPieceColor()!=t->getPieceColor())
                        tile[rw+1][co-1]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                }
            }
            //right-bottom
            if(rw+1<=7&&co+1<=7)
            {
                if(tile[rw+1][co+1]->getPiece()==false)
                    tile[rw+1][co+1]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                else
                {
                    if(tile[rw+1][co+1]->getPieceColor()!=t->getPieceColor())
                        tile[rw+1][co+1]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                }
            }
        }
        else if(t->getPieceName()=='Q')
        {
            //left
            for(int i=co-1;i>=0;i--)
            {
                if(tile[rw][i]->getPiece()==false)
                    tile[rw][i]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                else
                {
                    if(tile[rw][i]->getPieceColor()!=t->getPieceColor())
                        tile[rw][i]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                    break;
                }
            }
            //right
            for(int i=co+1;i<=7;i++)
            {
                if(tile[rw][i]->getPiece()==false)
                    tile[rw][i]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                else
                {
                    if(tile[rw][i]->getPieceColor()!=t->getPieceColor())
                        tile[rw][i]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                    break;
                }
            }
            //forward
            for(int i=rw+1;i<=7;i++)
            {
                if(tile[i][co]->getPiece()==false)
                    tile[i][co]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                else
                {
                    if(tile[i][co]->getPieceColor()!=t->getPieceColor())
                        tile[i][co]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                    break;
                }
            }
            //backward
            for(int i=rw-1;i>=0;i--)
            {
                if(tile[i][co]->getPiece()==false)
                    tile[i][co]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                else
                {
                    if(tile[i][co]->getPieceColor()!=t->getPieceColor())
                        tile[i][co]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                    break;
                }
            }
            //left-top
            for(int i=rw-1,j=co-1;i>=0&&j>=0;i--,j--)
            {
                if(tile[i][j]->getPiece()==false)
                    tile[i][j]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                else
                {
                    if(tile[i][j]->getPieceColor()!=t->getPieceColor())
                        tile[i][j]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                    break;
                }
            }
            //left-bottom
            for(int i=rw+1,j=co-1;i<=7&&j>=0;i++,j--)
            {
                if(tile[i][j]->getPiece()==false)
                    tile[i][j]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                else
                {
                    if(tile[i][j]->getPieceColor()!=t->getPieceColor())
                        tile[i][j]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                    break;
                }
            }
            //right-top
            for(int i=rw-1,j=co+1;i>=0&&j<=7;i--,j++)
            {
                if(tile[i][j]->getPiece()==false)
                    tile[i][j]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                else
                {
                    if(tile[i][j]->getPieceColor()!=t->getPieceColor())
                        tile[i][j]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                    break;
                }
            }
            //right-bottom
            for(int i=rw+1,j=co+1;i<=7&&j<=7;i++,j++)
            {
                if(tile[i][j]->getPiece()==false)
                    tile[i][j]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                else
                {
                    if(tile[i][j]->getPieceColor()!=t->getPieceColor())
                        tile[i][j]->setStyleSheet("QLabel {background-color:orange;border:1px solid;}");
                    break;
                }
            }
        }
    }
}

void chessboard::erasepath()
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(tile[i][j]->getTileColor()==1)
            {
                tile[i][j]->setStyleSheet("QLabel {background-color:rgb(255, 193, 122);}:hover{background-color: rgb(62, 139, 178);}");
            }
            else
            {
                tile[i][j]->setStyleSheet("QLabel {background-color:rgb(147, 91, 26);}:hover{background-color: rgb(62, 139, 178);}");
            }
        }
    }
}

bool chessboard::checkMate(){
    return false;
    // will implement this later
}
