#ifndef CHECKERS_H
#define CHECKERS_H

#include <QLabel>

class Checkers:public QLabel {
private:
    static int selected;
    int tileColor, pieceColor, row, col, tileNum;
    bool piece;
    char pieceName;
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

    void setTileColor(int color){tileColor=color;}
    void setPieceColor(int color){pieceColor=color;}
    void setPiece(bool p){piece=p;}
    void setRow(int i){row=i;}
    void setColumn(int j){col=j;}
    void setTileNum(int k){tileNum=k;}
    void setpieceName(char n){pieceName=n;}
};

#endif // CHECKERS_H
