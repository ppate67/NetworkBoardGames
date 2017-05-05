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
Piece::checkValid utilizes a number of methods within the Piece class to determine whether a piece is allowed to move to a given destination. If the piece is a pawn and the destination is the last row of the board, then Chess::pawnPromotion is called. 

Chess::pawnPromotion is a method that uses the ChessOptions class which inherents from QObject and allows the user to decide which piece they want to promote their pawn to (rook, knight, bishop, or queen). The functionalities in ChessOptions needed to be in a seperate class from Chess so that a suitable UI that utilizes the QT signal/slot mechanism could be made for pawn promotion selection.
Once a piece is placed on the board, the method Chess::sendGameMsg() (or passToAI() if in offline mode) is called to send the game data to the opponent over the server. The message is 66 bytes long (64 for the game state information and 2 for the header). 
As with Go, once a player receives the message in client::readyRead(), the data is passed off to Chess::receiveUpdates and the board state for the receiving party is updated. 

It is important to note that Chess uses a doubly linked list data structure that connects all the pieces on the board together. This is a useful feature because it allows one to access any tile on the board from any Chess object.

### Checkers:
![Imgur](http://i.imgur.com/An8N6EL.png)
When a Checkers game is launched, the first an instance of checkersboard is created. Along with the checkersboard object, an 8 by 8 array of Checkers objects. Checkers objects, which inherent from QLabel, are associated with a single tile of the board. This means that the graphics for a single tile can be altered within the Checkers object associated with that tile. The checkersboard object mostly handles the graphics of the entire board. In the game, a player can only make a move if the static Checkers int "checkersturn" is set to 1 and if the move is valid.  The game determines if the move is valid by utilizing the Piece class and the Piece::checkValid method.

## The following are descriptions for each AI for each game:
### Go AI:

### Chess AI:

### Checkers AI:
## Description of the Chat Room Component

# Server Description:
The server, and the client for that matter, has a data structure "games" which is a vector of vector of ints. Each vector in the top most vector represents a game while each item in the innermost vector is representative of a single player; it is structured as follows:
* games[gameid][0] = gametype;
* games[gameid][1] = player type; - Player type specifies whether it is a spectator or a player.
* games[gameid][2] = playerid;
There are a number of codes and headers that clients send to the server in order to acheive certain goals such as to get lists of games being played on the server. The messages are as follows:
Message Structure:
The message structure is split up into individual byte segments as follows
* {sending id/gameid}{message type}{code/message}
Types:
* 8 - Type reserved for non-game data. This can refer to all of the informational requests/chat messages.
* 0 - Go game data messages - Describes the board state of a particular Go game running on the server.
* 1 - Chess game data messages - Describes the board state of a particular Chess game running on the server.
* 2 - Checkers game data messages - Describes the board state of a particular Checkers game running on the server.
Codes (All have type = 8):
* 5 0 0 0 0 - Requests server to send the client's userid to the client.
* 3 1 0 0 0 - Makes request for the the server to send all the games on the server.
* 1 gameid playerindex 0 0 - Requests server to delete a player from the "game" vector.
* 2 gameid 1 0 gametype - Requests the server to add a game to the server by gameid. Byte 3 sets the server to add by gametype
* 2 gameidtojoin mode 1 gametype - Requests server to add player to specified game based on the gameid. Mode designates the playertype.
* 7 "new username" - Requests server to add username to the "playerList" vector. 
* 6 1 1 1 1 - Requests server to broadcast all player usernames to every client on the server.
* 8 "chat message" - Server requested to forward chat messages to people participating in the chat room.

The server is broken up into two main functional classes. "MyServer" and "player". MyServer listens for port 1234 and sets up (and maintains) a socket connection to any clients that connect to the server. player which inherits from QObject is the embodiment the TCP socket connection. One player object is associated with each socket connection. The player listens along its associated socket and makes responses to any messages it receives along the socket. Below is a graphic describing the structure of the server.

![Imgur](http://i.imgur.com/MotFu7d.png)

