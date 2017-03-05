/*
 Object for a checker game piece. (red, black, red king, black king)
 @author: Chris Frost
*/

#ifndef _CHECKERDISK_H_
#define _CHECKERDISK_H_
class CheckerDisk{
private:
    int currX;
    int currY;
    char ; //r, b, R, B
public:
    CheckerDisk() : {};
    void makeMove(int destX, int destY);
};
#endif
