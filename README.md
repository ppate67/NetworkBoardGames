# EE553_Networked_Board_Games
This project currently incorporates online and offline play for Checkers, Chess, and Go. 

The program is split into two sections: the server and the client. 

# Client:
Consider the diagram below

![Imgur](http://i.imgur.com/7oBk5y9.png)

When the program launches, main.cpp is the first to execute. From there, it launches and initializes the TCP client connection to the server.
The mainwindow is then launched. On mainwindow launch, the first thing done is to find the client's id "clientID" which is stored in the GameManager class. 
This is done by sending a request through the client with request data called "int requestID[5]={5,0,0,0,0};". This is responded to by the server with the 
client's ID number. The client then sends "int request1[5]={3,1,0,0,0};" which requests a list of all the details for all the games being played on the server. 
This received list then used to update the static vector "games" which is in the GameManager class and keeps an almanac of all the information being stored on the server.

At this point, the player should see the mainwindow displayed on their screen. See below:
![Imgur](http://i.imgur.com/zgZODmI.png)

If the user wishes to change the server they are connected to, they can click "Networked Board Games --> Change Server". 
They will then be prompted through dialog windows to enter first the server address and then the port number. The default server location is localhost (127.0.0.1). 
The current socket connection is then closed and then the client is then connected to the new one.

If the user wishes to play offline (with an AI) by clicking a checkBox on the mainwindow. When they do the static variable "offline" in mainwindow.h is changed to the value of 1. 

If the client wishes to update the game list on the mainwindow they simply need to click refresh. To join a game in this list, one needs to press "Launch Game".
When the game is joined, the server launches a message to the server requesting to join the game. The server will then respond with an updated message to all players on the server containing info on all the games on the system.
A client that joins a game that already exists is always player 2 and, as such, makes their turn second. Naturally, the "Launch Game" button also opens a window for the game to be played in.

## The following are descriptions for each game that can be played:

### Go:
![Imgur](http://i.imgur.com/XEgMN7M.png)
When a Go game is launched, the first an instance of goboard is created. Along with the goboard object, an 13 by 13 array of Go objects.
Go objects, which inherent from QLabel, are associated with a single tile of the board. This means that the graphics for a single tile can be altered within the Go object associated with that tile. The goboard object mostly handles the graphics of the entire board.  
In the game, a player can only make a move if the static Go int "turn" is set to 1 and if the move is valid. The game determines if the move is valid by calling Go::checkPositionValidity (which in turn checks if there is already a piece in the position).

Once the new piece is placed on the board, Go::updateEntireBoard() is called in which the liberties of each piece on the board are taken into consideration (this is acheived through the Go::checkLiberties method). If checkLiberties returns a value equal to or less than 0 then the piece being checked will be removed from the board. Go::updateEntireBoard() also updates the score of the game (which includes adding a point to a score if an opponent piece is removed). The score is also updated by factoring in the value of the territories the players hold (this is done with the Go::calculateTerritory method). 

Once the entire board is updated, the game is either passed off to the opponent (be it the AI or an opponent connected to the server).
If it is an online game, Go::sendGameMsg is used to send a game message over the server. This message is composed of a 171 byte long byte array categorizing which game the message corresponds to and the 169 tiles in the game.

When a player receives one of these game messages from the server, it uses Go::receiveUpdates to update each tile on the board with the opponent's move (and its consequences) and Go::updateEntireBoard to update the score of each player.

### Chess:
![Imgur](http://i.imgur.com/IbNoJMY.png)
When a Chess game is launched, the first an instance of chessboard is created. Along with the chessboard object, an 8 by 8 array of Chess objects. Chess objects, which inherent from QLabel, are associated with a single tile of the board. This means that the graphics for a single tile can be altered within the Chess object associated with that tile. The chessboard object mostly handles the graphics of the entire board. In the game, a player can only make a move if the static Chess int "chessturn" is set to 1 and if the move is valid. The game determines if the move is valid by utilizing the Piece class and the Piece::checkValid method.

### Checkers:
![Imgur](http://i.imgur.com/An8N6EL.png)
When a Checkers game is launched, the first an instance of checkersboard is created. Along with the checkersboard object, an 8 by 8 array of Checkers objects. Checkers objects, which inherent from QLabel, are associated with a single tile of the board. This means that the graphics for a single tile can be altered within the Checkers object associated with that tile. The checkersboard object mostly handles the graphics of the entire board. In the game, a player can only make a move if the static Checkers int "checkersturn" is set to 1 and if the move is valid.  The game determines if the move is valid by utilizing the Piece class and the Piece::checkValid method.

##T he following are descriptions for each AI for each game:
### Go AI:

### Chess AI:

### Checkers AI:


# Server Description:

