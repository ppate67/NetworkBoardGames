#include "chessboard.h"
#include "chess.h"
#include <QLabel>
#include <QtGui>
#include <QPushButton>
Chess* chessboard::tile[8][8] = {NULL};

void chessboard::setup(QWidget *baseWidget)
{
    QLabel *outLabel = new QLabel(baseWidget);
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
            tile[i][j] = new Chess(baseWidget);
            tile[i][j]->setTileColor((i+j)%2);
            tile[i][j]->setPiece(false);
            tile[i][j]->setRow(i);
            tile[i][j]->setColumn(j);
            tile[i][j]->setTileNum(k++);
            tile[i][j]->displayBoard();
            tile[i][j]->setGeometry(x,y,64,64);
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
