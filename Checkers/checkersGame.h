/*
 Object for a checker game board.
 @author: Chris Frost
 */

#ifndef _CHECKERSGAME_H_
#define _CHECKERSGAME_H_

#include "checkersboard.h"
#include "checkerDisk.h"
#include <cmath>

class CheckersGame{
private:
    checkersboard* board;
    bool winner;
public:
    CheckersGame() : winner(false) {
        board = checkersboard(); //Initialize a checkers board (4x4 array) to default piece locations
    }
    
    bool checkMove(checkerDisk c, int destX, int destY){
        //Checks if the intended move is a valid move.
        //Must be called before each move.
        if(destX < 0 || destX > 7 || destY < 0 || destY > 7)
            return false;
        if(c.c == 'b' || c.c == 'r'){
            //Not a king
            if(c.c == 'b'){
                if(abs(destY-c.currY) == 1 && abs(destX-c.currX) == 1){
                    //check if the user is making a valid move (in the correct direction)
                    if (destY < c.currY)
                        return true;
                }
                else if (abs(destY-c.currY) == 2 && abs(destX-c.currX) == 2){
                    //Check if the user is making a valid jump over an opponent piece
                    int lowX = min(c.currX, destX);
                    int lowY = min(c.currY, destY);
                    if((board[lowY+1][lowX+1]->c == 'r') && destY < c.currY)
                        return true;
                }
                return false;
            }
            else{
                if(abs(destY-c.currY) == 1 && abs(destX-c.currX) == 1){
                    //check if the user is making a valid move (in the correct direction)
                    if (destY > c.currY)
                        return true;
                }
                else if (abs(destY-c.currY) == 2 && abs(destX-c.currX) == 2){
                    //Check if the user is making a valid jump over an opponent piece
                    int lowX = min(c.currX, destX);
                    int lowY = min(c.currY, destY);
                    if(board[lowY+1][lowX+1]->c == 'b' && destY > c.currY)
                        return true;
                }
            }
        }
        else{
            //King
            if (c.c == 'B'){
                if (board[destY][destX] != nullptr)
                    return false;
                if (abs(destY-c.currY) > 2 && abs(destX-c.currX) > 2)
                    return false;
                else if (abs(destY-c.currY) == 2 && abs(destX-c.currX) == 2){
                    int lowX = min(c.currX, destX);
                    int lowY = min(c.currY, destY);
                    if(board[lowY+1][lowX+1]->c == 'r' || board[lowY+1][lowX+1]->c == 'R')
                        return true;
                }
                return true;
            }
            else{
                if (board[destY][destX] != nullptr)
                    return false;
                if (abs(destY-c.currY) > 2 && abs(destX-c.currX) > 2)
                    return false;
                else if (abs(destY-c.currY) == 2 && abs(destX-c.currX) == 2){
                    int lowX = min(c.currX, destX);
                    int lowY = min(c.currY, destY);
                    if(board[lowY+1][lowX+1]->c == 'r' || board[lowY+1][lowX+1]->c == 'R')
                        return true;
                }
                return true;
            }
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
