#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <QWidget>
#include<chess.h>

class chessboard
{
public:
    chessboard();
    void display(QWidget *baseWidget,Chess *tile[8][8]);
};

#endif // CHESSBOARD_H
