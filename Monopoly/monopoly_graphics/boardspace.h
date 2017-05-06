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
    int Ownership;
    int price;
    int freeParking;
    bool occupied;
    int owned;
    bool mortgaged;
    int houses;
    int rent;
    int tax;
    int xCoordinate;
    int yCoordinate;
public:
    boardSpace(){} // everything default to zero, set parameters outside of class with method calls

    int getRent(){
        return rent;
    }
    string getSpaceType(){
        return spaceType;
    }
    int getOwnership(){
        return Ownership;
    }

    int getPrice(){
        return price;
    }

    friend void setOwner(boardSpace& a, int id){
        a.owned = id;
    }

    friend void buildHouse(boardSpace& a){
        a.houses = a.houses +1;
        a.rent = a.rent + a.houses*100 ;
    }

    friend void mortgageProperty(boardSpace& a){
        a.mortgaged = true;
    }

    friend void unmortgageProperty(boardSpace& a){
        a.mortgaged = false;
    }

    //use void functions such as these to allow us to create an array of board positions easier
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
        Ownership = initOwnership;
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

    void setXcoordinate(int initX){
        xCoordinate = initX;
    }

    void setYcoordinate(int initY){
        yCoordinate = initY;
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



    string getBoardname(boardSpace a){
        return a.name;
    }

    string getName(){
        return name;
    }

};


#endif // BOARDSPACE_H
