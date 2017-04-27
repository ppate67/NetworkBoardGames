#ifndef BOARDSPACE_H
#define BOARDSPACE_H
#include"player.h"
#include<string>
using namespace std;

class boardSpace{
private:
    string name;
    string actionText;
    string spaceType;
    int price;
    int freeParking;
    bool occupied;
    int owned;
    bool mortgaged;
    int houses;
    int rent;
    int tax;
public:
    boardSpace(){} // everything default to zero

    friend class Player;

    friend void buildHouse(boardSpace& a){
        a.houses = a.houses +1;
        a.rent = a.rent + a.houses*100 ;
    }

    friend int getRent(boardSpace& a){
        return a.rent;
    }

    friend int getPrice(boardSpace a){
        return a.price;
    }

    friend int setOwner(boardSpace& a, int id){
        a.owned = id;
    }

    //use void functions such as these to allow us to create an array of board positions easier
    //we will set us this array in main.cpp as part of initialization
    void setName(string initName){
        name = initName;
    }
    void setType(string initType){
        spaceType = initType;
    }
    void setPropertyCost(int initPrice){
        price = initPrice;
    }

    void setFreeParking(int initMoney){
        freeParking = initMoney;
    }

    void setOccupied(bool initOccupied){
        occupied = initOccupied;
    }

    void setOwnership(int initOwnership){
        owned = initOwnership;
    }

    void setMortgaged(bool initMortgage){
        mortgaged = initMortgage;
    }

    void setRent(int initRent){
        rent = initRent;
    }
    void setTax(int initTax){
        tax = initTax;
    }

    void setActionText(string initText){
        actionText = initText;
    }

    void setHouses(int initHouses){
        houses = initHouses;
    }

    bool upgrade(){
        if(houses < 5){
            rent = rent * 2;
            houses++;
            return true;
        } else {
            return false;
        }
    }

};


#endif // BOARDSPACE_H
