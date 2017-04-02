#include "Checkers1/pieces2.h"

bool CheckerPiece::checkValid2(int endRow, int endCol, int endPieceColor, bool occupied){
    if (occupied == true){

            return false; //cannot move to any occupied position in checkers.

    }
    bool allow = false;
    switch(name){
        case 'P': allow = checkPiece2(row, col, endRow, endCol); // This is a normal checkers piece
            break;
        case 'K': allow = checkKinged2(row, col, endRow, endCol); // This is for a kinged checkers piece
            break;
   }

   return allow;
}

bool CheckerPiece::checkPiece2(int startRow, int startCol, int endRow, int endCol){
    switch(color){
        case 0:{ //black pieces increasing numbers in rows
            if (endRow == startRow + 1){
                if (endCol == startCol - 1 || endCol == startCol + 1)
                    return true;
            }
            break;
        }

        case 1:{ //white pieces decreasing numbers in rows
            if (endRow == startRow - 1){
                if (endCol == startCol - 1 || endCol == startCol + 1)
                    return true;
            }
            break;

        }
    }
    return false;
}

bool CheckerPiece::checkKinged2(int startRow, int startCol, int endRow, int endCol){
    if (endRow == startRow - 1 || endRow == startRow + 1 ){ // A kinged piece can move diagnoly in any direction
        if (endCol == startCol - 1 || endCol == startCol + 1)
            return true;
    }
    return false;
}


