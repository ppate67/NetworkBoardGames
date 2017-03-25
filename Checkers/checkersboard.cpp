#ifndef board.h
#define board.h

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