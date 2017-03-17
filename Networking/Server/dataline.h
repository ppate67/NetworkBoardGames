#ifndef DATALINE_H
#define DATALINE_H
#include "string"
#include "gamemsg.h"
using namespace std;

class dataLine
{
public:
    dataLine(int key, string username, int gameID, int gameType, int moveNumber, GameMsg msg);
    int key;
    string username;
    int gameID;
    int gameType;
    int moveNumber;
    GameMsg msg;
};

#endif // DATALINE_H
