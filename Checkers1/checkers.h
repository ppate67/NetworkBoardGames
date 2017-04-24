#ifndef CHECKERS_H
#define CHECKERS_H
#include "vector"
#include <QLabel>
#include "Networking/Client/client.h"
using namespace std;

class Checkers:public QLabel {
private:

    static int selected;
    int tileColor, pieceColor, row, col, tileNum;
    bool piece;
    char pieceName;
    static bool multicap;
public:
    Checkers(QWidget* pParent=0, Qt::WindowFlags f=0) : QLabel(pParent, f) {}
    static int offline;
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
    bool checkForWin(int lastMoveColor);
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



    void passToAI();
    vector<int> evaluateMoves(const string& originalBoardState,vector<vector<int>> moves,vector<vector<int>> playermoves, vector<Checkers*> AIpieces,vector<Checkers*> playerpieces, int treelength, int ecolor, int alpha, int beta, int score);
    string describeBoardState();
    Checkers* findPiece(int row, int col);
    int findScore(int destination);
    void resetBoardState(const string& state);

};

#endif // CHECKERS_H
