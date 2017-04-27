#ifndef cards_H_
#define cards_H_

#include<string>
#include<iostream>
using namespace std;

class Card{
private:
	string text; // the instructions on the card
	int amount; // amount of money to add or subtract from the player according to the card

public:
    Card(){}

    //use void functions such as these to allow us to create an array of chance and community chest cards easier
    //we will set us this array in main.cpp as part of initialization
    //we can then can pick randomly from the array to pick which card they get

    void setText(string initText){
        text = initText;
    }
    void setAmount(int initAmount){
        amount = initAmount;
    }


    //The card read would be Chance[randomCard()] or CommunityChance[randomCard] --- A random card would be read out of that set based on the position the player is in
    friend void readCard(Card a, string& words, int& payment){
        words = a.text;
        payment = a.amount;
    }


};


	


#endif
