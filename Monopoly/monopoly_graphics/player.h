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
    bool inJail; //whether or not the player is in jail
    int position; //Position on the board where the player is
    int ownedproperty[40];

public:
    Player(){
        for(int i=0; i<40; i++)
            ownedproperty[i]=0;
    }

    void setName(string initName){
        name = initName;
    }
    void setUserID(int initUserID){
        userid = initUserID;
    }

    void setBank(int initName){
        bank = initName;
    }
    void setJailFree(int initJailFree){
        jailFree = initJailFree;
    }
    int addJailFree(){
       return jailFree += 1;
    }
    int subJailFree(){
        return jailFree -= 1;
    }

    void setPosition(int initPosition){
        position = initPosition;
    }

    void setJail(bool initJail){
        inJail = initJail;
    }

    void setOwned(int newOwned){
        ownedproperty[newOwned] = 1;
    }

    int getOwned(int newcheck){
        return ownedproperty[newcheck];
    }

    int getPosition(){
        return position;
    }

    int getUserID(){
        return userid;
    }

    int getBank(){
        return bank;
    }

    int getJailFree(){
        return jailFree;
    }

    int getJailStatus(){
        return inJail;
    }

    friend void payRent(Player& a, Player& b, int& Rent){  //Player A pays Player B rent if on their property
        a.bank = a.bank - Rent;
        b.bank = b.bank + Rent;
    }

    void movePlayer(int distance){
        position = position + distance;
        if(position > 39){
            position -= 40;
            bank += 200;
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

    Player operator =(Player a){
        Player temp(a.name, a.userid, a.bank, a.jailFree, a.position);
        return temp;
        }

*/

};


#endif // PLAYER_H
