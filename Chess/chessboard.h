#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <QWidget>
#include <Chess/chess.h>
#include <stdlib.h> // used in checkPath function

class chessboard:public Chess
{
private:
    static Chess *tile[8][8];
public:
    chessboard(){}
    void setup(QWidget *baseWidget);
    static bool checkPath(int startRow, int startCol, int endRow, int endCol, char direction);
    void quitclicked();
    static void drawpath(Chess *t);
    static void erasepath();
};

#endif // CHESSBOARD_H
