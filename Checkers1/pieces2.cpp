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

bool CheckerPiece::checkCapture(int endRow, int endCol, bool midOccupied, bool endOccupied, int midColor){
    if(endOccupied || midColor == color)
        return false;
    if(name == 'P'){ //Piece is making a jump
        if((endCol == col - 2 || endCol == col + 2) && midOccupied){
            if(color == 0){ //Black Piece
                if(endRow == row + 2)
                    return true;
            }
            else{ //Red piece
                if(endRow == row - 2)
                    return true;
            }
        }
    }
    else{ //King is making a jump
        if((endCol == col - 2 || endCol == col + 2) && midOccupied){
            if(endRow == row + 2 || endRow == row - 2)
                return true;
        }
    }
    return false;
}

//Check if there are any available moves for this piece. If none, return false.
bool CheckerPiece::checkMoves(Checkers* tile[8][8]){
    bool space1 = false, space2 = false, space3 = false, space4 = false;
    switch(name){
        case 'P':
                if (color == 0){

                    if(col<7)
                        space1 = checkValid2(row+1, col+1, tile[row+1][col+1]->getPieceColor(), tile[row+1][col+1]->getPiece());
                    if(col>0)
                        space2 = checkValid2(row+1, col+1, tile[row+1][col-1]->getPieceColor(), tile[row+1][col-1]->getPiece());

                    if(space1 || space2)
                        return true;

                    if(!space1){
                        //If space1 is invalid, check if there is a valid jump.
                        if(row < 6 && col < 6 && tile[row+1][col+1]->getPiece()){
                            space1 = checkCapture(row+2, col+2, true, tile[row+2][col+2]->getPiece(), tile[row+1][col+1]->getPieceColor());
                        }
                    }
                    if(!space2){
                        //If space2 is invalid, check if there is a valid jump.
                        if(row < 6 && col > 1 && tile[row+1][col-1]->getPiece()){
                            space1 = checkCapture(row+2, col-2, true, tile[row+2][col-2]->getPiece(), tile[row+1][col-1]->getPieceColor());
                        }
                    }
                }
                else{

                    if(col < 7)
                        space1 = checkValid2(row-1, col+1, tile[row-1][col+1]->getPieceColor(), tile[row-1][col+1]->getPiece());
                    if(col > 0)
                        space2 = checkValid2(row-1, col-1, tile[row-1][col-1]->getPieceColor(), tile[row-1][col-1]->getPiece());

                    if(space1 || space2)
                        return true;

                    if(!space1){
                        //If space1 is invalid, check if there is a valid jump.
                        if(row > 1 && col < 6 && tile[row-1][col+1]->getPiece()){
                            space1 = checkCapture(row-2, col+2, true, tile[row-2][col+2]->getPiece(), tile[row-1][col+1]->getPieceColor());
                        }
                    }
                    if(!space2){
                        //If space2 is invalid, check if there is a valid jump.
                        if(row > 1 && col > 1 && tile[row-1][col-1]->getPiece()){
                            space1 = checkCapture(row-2, col-2, true, tile[row-2][col-2]->getPiece(), tile[row-1][col-1]->getPieceColor());
                        }
                    }
                }
            break;
        case 'K':

            if(row > 0 && col < 7)
                space1 = checkValid2(row-1, col+1, tile[row-1][col+1]->getPieceColor(), tile[row-1][col+1]->getPiece());
            if(row < 7 && col < 7)
                space2 = checkValid2(row+1, col+1, tile[row+1][col+1]->getPieceColor(), tile[row+1][col+1]->getPiece());
            if(row > 0 && col > 0)
                space3 = checkValid2(row-1, col-1, tile[row-1][col-1]->getPieceColor(), tile[row-1][col-1]->getPiece());
            if(row < 7 && col > 0)
                space4 = checkValid2(row+1, col-1, tile[row+1][col-1]->getPieceColor(), tile[row+1][col-1]->getPiece());

            if(space1 || space2 || space3 || space4)
                return true;

            if(!space1){
                //If space1 is invalid, check if there is a valid jump.
                if(row > 1 && col < 6 && tile[row-1][col+1]->getPiece()){
                    space1 = checkCapture(row-2, col+2, true, tile[row-2][col+2]->getPiece(), tile[row-1][col+1]->getPieceColor());
                }
            }
            if(!space2){
                //If space2 is invalid, check if there is a valid jump.
                if(row < 6 && col < 6 && tile[row+1][col+1]->getPiece()){
                    space2 = checkCapture(row+2, col+2, true, tile[row+2][col+2]->getPiece(), tile[row+1][col+1]->getPieceColor());
                }
            }
            if(!space3){
                //If space2 is invalid, check if there is a valid jump.
                if(row > 1 && col > 1 && tile[row-1][col-1]->getPiece()){
                    space3 = checkCapture(row-2, col-2, true, tile[row-2][col-2]->getPiece(), tile[row-1][col-1]->getPieceColor());
                }
            }
            if(!space4){
                //If space2 is invalid, check if there is a valid jump.
                if(row < 6 && col > 1 && tile[row+1][col-1]->getPiece()){
                    space4 = checkCapture(row+2, col-2, true, tile[row+2][col-2]->getPiece(), tile[row+1][col-1]->getPieceColor());
                }
            }
            break;
    }
    return(space1 || space2 || space3 || space4);
}
