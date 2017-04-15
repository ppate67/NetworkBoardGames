#include "pieces.h"

int Piece::bkr = 0;
int Piece::bkc = 4;
int Piece::wkr = 7;
int Piece::wkc = 4;

bool Piece::checkPawn(int startRow, int startCol, int endRow, int endCol, bool occupied){
    switch(color){
        case 0:{ //black pieces increasing numbers in rows
            if (occupied == false){ // can't move forward into opposing piece
                if (endRow == startRow + 1 && endCol == startCol)
                    return true;
                if (startRow == 1){ // can move forward two spaces off start
                    if (endRow == startRow + 2 && endCol == startCol)
                        return true;
                }
            }
            else { // can only capture diagonally
                if (endRow == startRow + 1){
                    if (endCol == startCol - 1 || endCol == startCol + 1)
                        return true;
                }
            }
            break;
        }
        case 1:{ //white pieces decreasing numbers in rows
            if (occupied == false){
                if (endRow == startRow - 1 && endCol == startCol)
                    return true;
                if (startRow == 6){
                    if (endRow == startRow - 2 && endCol == startCol)
                        return true;
                }
            }
            else {
                if (endRow == startRow - 1){
                    if (endCol == startCol - 1 || endCol == startCol + 1)
                        return true;
                }
            }
            break;
        }
    }
    return false;
}

bool Piece::checkRook(int startRow, int startCol, int endRow, int endCol){ // can move in straight lines without jumping over pieces
    if (chessboard::checkPath(startRow, startCol, endRow, endCol, 'l') == true){
        return true;
    }
    else {
        return false;
    }
}

bool Piece::checkKnight(int startRow, int startCol, int endRow, int endCol){ // allowed to jump over pieces
    if (endRow == startRow + 2){ // move two up and one to left or right
        if (endCol == startCol - 1 || endCol == startCol + 1)
            return true;
    }
    else if (endRow == startRow - 2){ // move two back and one to left or right
        if (endCol == startCol - 1 || endCol == startCol + 1)
            return true;
    }
    else if (endCol == startCol + 2){ // move two right and one up or back
        if (endRow == startRow - 1 || endRow == startRow + 1)
            return true;
    }
    else if (endCol == startCol - 2){ // move two left and one up or back
        if (endRow == startRow - 1 || endRow == startRow + 1)
            return true;
    }
    return false;
}

bool Piece::checkKing(int startRow, int startCol, int endRow, int endCol){
    if (endRow == startRow){
        if ((endCol == startCol - 1) || (endCol == startCol + 1)){
            return true; // checks move 1 to left or right
        }
    }
    else if (endCol == startCol){
        if ((endRow == startRow - 1) || (endRow == startRow + 1)){
            return true; // checks move 1 up or back
        }
    }
    else if (endRow == startRow + 1){
        if ((endCol == startCol - 1) || (endCol == startCol + 1)){
            return true; // check top right and left corners
        }
    }
    else if (endRow == startRow - 1){
        if ((endCol == startCol - 1) || (endCol == startCol + 1)){
            return true; // check bottom right and left corners
        }
    }
    return false;
}

bool Piece::checkQueen(int startRow, int startCol, int endRow, int endCol){ // can move in straight or diagonal lines without jumping over pieces
    if (chessboard::checkPath(startRow, startCol, endRow, endCol, 'l') == true){
        return true;
    }
    if (chessboard::checkPath(startRow, startCol, endRow, endCol, 'd') == true){
        return true;
    }
    return false;
}

bool Piece::checkBishop(int startRow, int startCol, int endRow, int endCol){ // can move in diagonal lines without jumping over pieces
    if (chessboard::checkPath(startRow, startCol, endRow, endCol, 'd') == true){
        return true;
    }
    else {
        return false;
    }
}

bool Piece::checkValid(int endRow, int endCol, int endPieceColor, bool occupied){
    if (occupied == true){
        if(color == endPieceColor){ // can not take own color piece
            return false;
        }
    }
    bool allow = false;
    switch(name){
        case 'P': allow = checkPawn(row, col, endRow, endCol, occupied);
            break;
        case 'R': allow = checkRook(row, col, endRow, endCol);
            break;
        case 'H': allow = checkKnight(row, col, endRow, endCol);
            break;
        case 'K': allow = checkKing(row, col, endRow, endCol);
            break;
        case 'Q': allow = checkQueen(row, col, endRow, endCol);
            break;
        case 'B': allow = checkBishop(row, col, endRow, endCol);
            break;
   }
   return allow;
}
