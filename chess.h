#ifndef CHESS_H
#define CHESS_H
#include <QLabel>
class Chess:public QLabel
{
private:
    static int selected;
    int tileColor,pieceColor,row,col,tileNum;
    bool piece;
    char pieceName;
public:
    Chess(QWidget* pParent=0, Qt::WindowFlags f=0) : QLabel(pParent, f) {}
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
    int gettileNum(){return tileNum;}
    bool getPiece(){return piece;}
    int getPieceName(){return pieceName;}
};

#endif // CHESS_H
