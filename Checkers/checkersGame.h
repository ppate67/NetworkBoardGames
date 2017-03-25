/*
 Object for a checker game board.
 @author: Chris Frost
 */

#ifndef _CHECKERSGAME_H_
#define _CHECKERSGAME_H_

#include "checkersboard.h"
#include "checkerDisk.h"

class CheckersGame{
private:
    checkersboard* board;
    bool winner;
public:
    CheckersGame() : winner(false) {}
    
    bool checkMove(checkerDisk c, int destX, int destY){
        //Checks if the intended move is a valid move.
        //Must be called before each move.
        if(destX < 0 || destX > 7 || destY < 0 || destY > 7)
            return false;
        if(c.c == 'b' || c.c == 'r'){
            //Not a king
            if(c.c == 'b'){
                
            }
            else{
                
            }
        }
        else{
            //King
            if (board[currY][currX] != nullptr)
                return false;
            else if (destX)
                return false;
        }
        
    }
    bool checkKing(checkerDisk c){
        //Checks if the last move resulted in a checkerDisk being promoted to a king.
        //Must be called after each move.
        if((c.c == 'b' && currY == 0) || (c.c == 'r' && currY == 7)) //ASSUME: black pieces start at bottom of board.
            return true;
        return false;
    }
    bool checkWin(int lastPlayerMove){
        //Checks if the last player to move (lastPlayerMove) caused a win.
        if(lastPlayerMove == 0){    //Player 1 (black) made last move
            for(auto c : *board){
                if (c->c == 'b' || c->c == 'B')
                    return false;
            }
            return true;
        }
        else{                       //Player 2 (red)
            for(auto c : *board){
                if (c->c == 'r' || c->c == 'R')
                    return false;
            }
            return true;
        }
    }
};

#endif
