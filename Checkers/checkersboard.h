#ifndef board.h
#define board.h
//This is the basic outline of a chess or a checker board

Class board{
Private:
	Piece board[8][8];
Public:
	board();
	~board();
	Void displayBoard();
	Bool checkMove();
	Bool checkWin();
	
};
#endif