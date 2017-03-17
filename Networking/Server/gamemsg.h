#ifndef GAMEMSG_H
#define GAMEMSG_H
#include <string>
using namespace std;
class GameMsg
{
public:
    GameMsg(int type=0, string data="", int ganeid=0, int length=0);
    int type;
    int length;
    string data;
    void destroy();
    int gameid;
};

#endif // GAMEMSG_H
