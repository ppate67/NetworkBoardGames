#include "pieces.h"

bool Piece::checkPawn(int endRow, int endCol, bool occupied){
    switch(color){
        case 0:{ //white pieces increasing numbers in rows
            if (occupied == false){ // can't move forward into opposing piece
                if (endRow == row + 1 && endCol == col)
                    return true;
                if (row == 1){ // can move forward two spaces off start
                    if (endRow == row + 2 && endCol == col)
                        return true;
                }
            }
            else { // can only capture diagonally
                if (endRow == row + 1 && endCol == col - 1)
                    return true;
                if (endRow == row + 1 && endCol == col + 1)
                    return true;
            }
            break;
        }
        case 1:{ //black pieces decreasing numbers in rows
            if (occupied == false){
                if (endRow == row - 1 && endCol == col)
                    return true;
                if (row == 6){
                    if (endRow == row - 2 && endCol == col)
                        return true;
                }
            }
            else {
                if (endRow == row - 1 && endCol == col - 1)
                    return true;
                if (endRow == row - 1 && endCol == col + 1)
                    return true;
            }
            break;
        }
    }
    return false;
}

bool Piece::checkRook(int endRow, int endCol){
    return false;
}

bool Piece::checkKnight(int endRow, int endCol){
    return false;
}

bool Piece::checkKing(int endRow, int endCol){
    if (endRow == row){
        if (endCol == col - 1 || endCol == col + 1)
            return true; // checks move 1 to left or right
    }
    if (endCol == col){
        if (endRow == row - 1 || endRow == row + 1)
            return true; // checks move 1 up or back
    }
    if ((endRow == row + 1 && endCol == col - 1) || (endRow == row - 1 && endCol == col + 1)){
        return true; // checks top left corner and bottom right corner
    }
    if ((endRow == row - 1 && endCol == col + 1) || (endRow == row + 1 && endCol == col - 1)){
        return true; // checks top right corner and bottom left corner
    }
    return false;
}

bool Piece::checkQueen(int endRow, int endCol){
    return true;
}

bool Piece::checkBishop(int endRow, int endCol){
    return false;
}

bool Piece::checkValid(int endRow, int endCol, int endPieceColor, bool occupied){
    if(color == endPieceColor){ // can not take own color piece
        return false;
    }
    bool allow = false;
    switch(name){
        case 'P': allow = checkPawn(endRow, endCol, occupied);
            break;
        case 'R': allow = checkRook(endRow, endCol);
            break;
        case 'H': allow = checkKnight(endRow, endCol);
            break;
        case 'K': allow = checkKing(endRow, endCol);
            break;
        case 'Q': allow = checkQueen(endRow, endCol);
            break;
        case 'B': allow = checkBishop(endRow, endCol);
            break;
   }
   return allow;
}
