#ifndef GOBOARD_H
#define GOBOARD_H
#include "QWidget"
#include "go.h"

class GoBoard
{

public:
    GoBoard();

    void display(QWidget *baseWidget,Go *tile[13][13]);
    void forfeitclose();
    void removeplayer();
    static void updateScores();


};

#endif // GOBOARD_H
