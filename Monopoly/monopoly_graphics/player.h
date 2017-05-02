#ifndef PLAYER_H
#define PLAYER_H
#include "boardspace.h"
#include <string>
#include <iostream>
using namespace std;


class Player{
private:
    string name; //The name of the property
    int userid; //The ID of the User
    int bank; //Amount of Money Owned
    int jailFree; //How Many Get Out of Free Cards DO you have
    int position; //Position on the board where the player is

public:
    Player(string name, int userid, int bank, int jailFree, int position) : name(name), userid(userid), bank(bank), jailFree(jailFree), position(position){}

    friend int getPosition(Player a){
        return a.position;
    }

    friend int getUserID(Player a){
        return a.userid;
    }

    friend int getBank(Player a){
        return a.bank;
    }

    friend int getJailFree(Player a){
        return a.jailFree;
    }

    friend void payRent(Player& a, Player& b, int& Rent){  //Player A pays Player B rent if on their property
        a.bank = a.bank - Rent;
        b.bank = b.bank + Rent;
    }

    friend void movePlayer(Player& a, int distance){
        a.position = a.position + distance;
        if(a.position > 39){
            a.position = a.position - 40;
        }

    }

    friend void BuyProperty(Player& a, int amount){
        a.bank = a.bank -amount;
    }

    //Amount = (Price of Property / 2)
    friend void playerMortgageProperty(Player& a, int amount){
        a.bank = a.bank + amount;
    }

    //Amount = (Price of Property / 2)
    friend void playerPayMortgageProperty(Player& a, int amount){
        a.bank = a.bank - amount;
    }

    /*
    Player& operator =(Player a){
        a.name = name;
        a.userid = userid;
        a.bank = bank;
        a.jailFree = jailFree;
        a.position = position;
    }
    */


};


#endif // PLAYER_H
