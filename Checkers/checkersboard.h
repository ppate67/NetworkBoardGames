#ifndef _CHECKERSBOARD_H_
#define _CHECKERSBOARD_H_
//This is the basic outline of a checkers board.
//IS THIS FILE STILL NECESSARY?

Class board{
Private:
	Piece board[8][8];
Public:
	board();
	~board();
	void displayBoard();
	bool checkMove();
	bool checkWin();
	
};
#endif
