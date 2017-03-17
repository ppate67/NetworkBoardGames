#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "vector"
class GameManager
{
public:
    GameManager();

    int playerid;
    int gameType;
    int gameID;
    bool player;
    GameManager *nextGame;
    static GameManager *head;
    static bool hasPlayerID;
    static std::vector<std::vector<std::vector<int>>> games;
    static int clientID;
    GameManager *nextPlayer;
//this class is an interconnected data structure sort of like a linked
    //list but with branches off to the num of players/spectators
    //this is done because a 2dimensional vector would be the only other
    //option and it seems to be seems messier to maintain the overall game vector that way
    void removePlayer(GameManager *player, GameManager *game);
    void addPlayer(GameManager *game,GameManager* &player);//adds to a game based on id
     GameManager* findGame1(int playerid);
    GameManager* findGame2(int gType);
    GameManager* findGame3(int gID);

};

#endif // GAMEMANAGER_H
