#include <iostream>
#include <string>

#include <pieces.h>

using namespace std;

class Player{
private:
	string name;
    int userid;
    int userColor;
public:
	Player(string name, int userid, int userColor): name(name), userid(userid), userColor(userColor){}
};

class chessGame(): public board{
private:
    bool winner;
public:
    void checkForWin();
};

int main(){
    // access server
    // get player information
    Player p1("John", 100, 0); // 0 is white color
    Player p2("Jane", 200, 1); // 1 is black color

    //get message from player, send to server, repeat
}
