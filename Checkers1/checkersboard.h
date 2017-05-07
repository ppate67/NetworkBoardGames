#ifndef CHECKERSBOARD_H
#define CHECKERSBOARD_H

#include <QWidget>
#include "checkers.h"
#include <stdlib.h> // used in checkPath function

class checkersboard:public Checkers
{
    friend class Checkers;
private:
    static Checkers *tile[8][8];
public:
    checkersboard(){}
    void setup(QWidget *baseWidget);
    //static bool checkPath(int startRow, int startCol, int endRow, int endCol, char direction); //Don't think I need this for checkers b/c i never use it
    bool isOccupied(int row, int col);
};

#endif // CHECKERSBOARD_H
