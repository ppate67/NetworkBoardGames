#ifndef GO_H
#define GO_H
#include "QLabel"
#include "Networking/Client/client.h"
class Go:public QLabel
{
private:
    int userColor=2;

    int row, col, tileNum;
    bool piece;
public:
    static int offline;
    Go* nexttile;
    static Go* head;
    static int opponentScore;
    static int playerScore;
    static int wterr;
    static int blterr;
    Go* prevtile;
    int type;
    static int turn;
    static int color;
    Go(QWidget* pParent=0, Qt::WindowFlags f=0) : QLabel(pParent, f){
        nexttile=NULL;
        prevtile=NULL;

    }
    ~Go(){
        head=nullptr;

        turn=1;
        color=0;
        opponentScore=0;
        playerScore=0;
        wterr=0;
        blterr=0;
        offline=0;
    }
    static void updateEntireBoard();
    void mousePressEvent(QMouseEvent *event);
    void displayElement(char elem);
    void displayBoard(int type);
    void setPiece(bool p){piece=p;}
    void setRow(int i){row=i;}
    void setPieceColor(int color){userColor=color;}
    void fillArray(Go* tiles[13][13],Go* pnt);
    Go* findHead(Go* pnt);
    void setColumn(int j){col=j;}
    void setTileNum(int k){tileNum=k;}
    int getPieceColor(){return userColor;}
    int getRow(){return row;}
    int getColumn(){return col;}
    int gettileNum(){return tileNum;}
    int getUserColor();
    int checkLiberties(Go* position, Go* prevposition, vector<Go*>* positions);
    bool isConnected(Go* curposition,Go*prevposition, Go* otherposition);
    //bool korule(GoBoard board);
    //bool suicide(GoBoard board);
    bool checkPositionValidity(int corx, int cory, int color);
    bool placeStone(int corx, int cory);
    void captureStones();
    void addStonePoints(int numcapstones, int playercolor);
    void sendGameMsg();
    static void receiveUpdates(int color, int iteration);
    int calculateTerritory(Go* position, Go* prevposition, vector<Go*>* positions, int tercolor);
    void passToAI();
    int checkValAI(Go* consideration);
};


#endif // GO_H
