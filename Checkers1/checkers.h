#ifndef CHECKERS_H
#define CHECKERS_H

#include <QLabel>
#include "Networking/Client/client.h"


class Checkers:public QLabel {
private:
    static int selected;
    int tileColor, pieceColor, row, col, tileNum;
    bool piece;
    char pieceName;
    static bool multicap;
public:
    Checkers(QWidget* pParent=0, Qt::WindowFlags f=0) : QLabel(pParent, f) {}

    void mousePressEvent(QMouseEvent *event);
    void displayElement(char elem);
    void displayBoard();

    int getTileColor() {return tileColor;}
    int getPieceColor() {return pieceColor;}
    int getRow() {return row;}
    int getColumn() {return col;}
    int getTileNum() {return tileNum;}
    bool getPiece() {return piece;}
    int getPieceName() {return pieceName;}
    void capturePiece(Checkers* capturee, Checkers* captor);
    void checkCapture();
    void setTileColor(int color){tileColor=color;}
    void setPieceColor(int color){pieceColor=color;}
    void setPiece(bool p){piece=p;}
    void setRow(int i){row=i;}
    void setColumn(int j){col=j;}
    void setTileNum(int k){tileNum=k;}
    void setpieceName(char n){pieceName=n;}
    bool multiCapture();
    void captureAuxiloryFunc(int usercolor, int enemycolor);
    //networking functionalities
    static int checkersturn;
    static int playercolor;
    Checkers* nexttile;
    static Checkers* checkershead;
    Checkers* prevtile;
    void fillArray(Checkers* tiles[8][8],Checkers* pnt);
    Checkers* findHead(Checkers* pnt);
    void sendGameMsg();
    static void receiveUpdates(char piece1, int iteration);

};

#endif // CHECKERS_H
