#include "chessboard.h"
#include "chess.h"
#include <QLabel>
#include <QtGui>
chessboard::chessboard()
{

}

void chessboard::display(QWidget *baseWidget,Chess *tile[8][8])
{
    QLabel *outLabel = new QLabel(baseWidget);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
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
