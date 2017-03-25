/*
 Object for a checker game piece. (red, black, red king, black king)
 @author: Chris Frost
*/

#ifndef _CHECKERDISK_H_
#define _CHECKERDISK_H_

#include "checkersBoard.h"

class CheckerDisk{
private:
    int currX;
    int currY;
    char c; //r, b, R, B
public:
    CheckerDisk(int x, int y, char c) : currX(x), currY(y), c(c) {}
    void makeMove(int destX, int destY){
        //This function will only be called AFTER the checkersBoard class checks if it is a valid move.
        currX = destX;
        currY = destY;
    }
    void makeKing(){
        if (c == 'r')
            c = 'R';
        else
            c = 'B';
    }
};
#endif
