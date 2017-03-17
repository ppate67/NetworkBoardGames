#ifndef GAMEMSG_H
#define GAMEMSG_H
#include "string"
using namespace std;
class GameMsg
{
public:
    GameMsg(int type, string data, int userid, int length);
    int type;
    int length;
    string data;
    void destroy();
    int userid;
};

#endif // GAMEMSG_H
