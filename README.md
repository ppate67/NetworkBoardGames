# EE553_Networked_Board_Games
This project currently incorporates online and offline play for Checkers, Chess, and Go. 

The program is split into two sections: the server and the client. 

Client:
Consider the diagram below

http://imgur.com/a/xbs6N

When the program launches, main.cpp is the first to execute. From there, it launches and initializes the TCP client connection to the server.
The mainwindow is then launched. On mainwindow launch, the first thing done is to find the client's id "clientID" which is stored in the GameManager class. 
This is done by sending a request through the client with request data called "int requestID[5]={5,0,0,0,0};". This is responded to by the server with the 
client's ID number. The client then sends "int request1[5]={3,1,0,0,0};" which requests a list of all the details for all the games being played on the server. 
This received list then used to update the static vector "games" which is in the GameManager class and keeps an almanac of all the information being stored on the server.

At this point, the player should see the mainwindow displayed on their screen. See below:
http://imgur.com/a/7KVyX

If the user wishes to change the server they are connected to, they can click "Networked Board Games --> Change Server". 
They will then be prompted through dialog windows to enter first the server address and then the port number. The default server location is localhost (127.0.0.1). 
The current socket connection is then closed and then the client is then connected to the new one.

If the user wishes to play offline (with an AI) by clicking a checkBox on the mainwindow. When they do the static variable "offline" in mainwindow.h is changed to the value of 1. 

If the client wishes to update the game list on the mainwindow they simply need to click refresh. To join a game in this list, one needs to press "Launch Game".
When the game is joined, the server launches a message to the server requesting to join the game. The server will then respond with an updated message to all players on the server containing info on all the games on the system.
A client that joins a game that already exists is always player 2 and, as such, makes their turn second. Naturally, the "Launch Game" button also opens a window for the game to be played in.

The following are descriptions for each game that can be played:

GO:
http://imgur.com/a/AFl4w
Chess:
http://imgur.com/a/p6MQd
Checkers:
http://imgur.com/a/aUzrA

The following are descriptions for each AI for each game:
Go AI:

Chess AI:

Checkers AI:


Server Description:

