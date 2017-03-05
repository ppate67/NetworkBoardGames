/*
 Object for a checker game board.
 @author: Chris Frost
 */

#ifndef _CHECKERSGAME_H_
#define _CHECKERSGAME_H_

class CheckersGame : public Board{ //Parent Class Board not yet implemented
private:
    bool winner;
public:
    CheckersGame() : Board();
    bool checkMove();
    bool checkWin();
};
#endif
