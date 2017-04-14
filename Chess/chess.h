#ifndef CHESS_H
#define CHESS_H
#include <QLabel>
#include "Networking/Client/client.h"
#include "QDialog"
class Chess:public QLabel
{
private:
    static int selected;
    int tileColor,pieceColor,row,col,tileNum;
    bool piece;
    char pieceName;



public:
    static int offline;
    Chess(QWidget* pParent=0, Qt::WindowFlags f=0) : QLabel(pParent, f) {
//        Chess::chesshead=NULL;
//        Chess::chessturn=1;
//        Chess::playercolor=0;
//        Chess::selected=0;

    }

    void mousePressEvent(QMouseEvent *event);
    void displayElement(char elem);
    void displayBoard();
    void setTileColor(int color){tileColor=color;}
    void setPieceColor(int color){pieceColor=color;}
    void setPiece(bool p){piece=p;}
    void setRow(int i){row=i;}
    void setColumn(int j){col=j;}
    void setTileNum(int k){tileNum=k;}
    void setpieceName(char n){pieceName=n;}
    int getTileColor(){return tileColor;}
    int getPieceColor(){return pieceColor;}
    int getRow(){return row;}
    int getColumn(){return col;}
    int getTileNum(){return tileNum;}
    bool getPiece(){return piece;}
    char getPieceName(){return pieceName;}

    void pawnPromotion(Chess* pawn);

    //networking methods. This is essentially the same stuff used by the go class
    //but a bit different since chess is a different game with different requirements
    static int chessturn;
    static int playercolor;
    Chess* nexttile;
    static Chess* chesshead;
    Chess* prevtile;
    void fillArray(Chess* tiles[8][8],Chess* pnt);
    Chess* findHead(Chess* pnt);
    void sendGameMsg();
    static void receiveUpdates(char piece1, int iteration);

public slots:
    void queenpromotion();
};
class ChessOptions:public QLabel
{
    public:
    ChessOptions(QWidget* pParent=0, Qt::WindowFlags f=0) : QLabel(pParent, f) {}
    int piecetype;
    Chess *pawn;
    QDialog * window;
    void mousePressEvent(QMouseEvent *event);


};
#endif // CHESS_H
