#include <iostream>
#include <string>
using namespace std;

class Player{
private:
	string name; //The name of the property
	int userid; //The ID of the User
	int bank; //Amount of Money Owned
	int jailFree; //How Many Get Out of Free Cards DO you have
	int position; //Position on the board where the player is

public:
	Player(string name, int userid, int bank, int jailFree, int position)

};

class gameBoard{
private:
	int price; //Price for that property
	int tax; //Amount it costs if landed on
	int mortgage; //Amount of money you get if mortgaged
	string owner; //Owner of property, originally set to null
	int position; //Position on the board
	int houses; //Amount of house (5 houses = 1 hotel)
	int category; //What color cattegory it is instructions
	bool Mortgage; //Is it mortgaged? 
public: 
	gameBoard(int price, int tax, int mortgage, string owner, int position, int houses, int hotels, int category, bool Mortgage)


};

Class Card{
private:
	int type; // chance or community chest
	string text; // the instructions on the card
	int amount; // amount of money to add or subtract from the player according to the card
public:
	Card(int type, string text, int amount)

};

void propertyPay {
		//Player lands on property owned by another player 
		//Player pays property owner
}
void drawCard {
		//draw either a chance or community chest card
		//add amount of card (negative or positive) to player
		//add 1 to  “get out of jail free card” variable if it is that card (jailFree attribute)
}
int dieroll(int& roll1, int& roll2) {
	srand(time(NULL));
	roll1 = rand()%6+1;
	roll2 = rand()%6+1;
}

void propertyBuy {
		//ask if player would like to purchase, if yes continue if no call property auction
		//change status of property to owned
		//subtract money from player bank
}

void propertyAuction {
		//allow mortgages or trades??
		//input an amount from each player
		//highest amount gets the property
		//subtract wagered money from winner's account
		//Low Priority
}

void propertyTrade {
		//ask if player would like to trade, if yes continue
		//select a player, bring up a list of their properties and their bank
		//select property numbers and enter an amount of money from 0-some upper        bound
		//select own property numbers and enter an amount of money similar to above
		//trade offer send, if accepts -> swap traded property accordingly
		//if offer rejected -> allow X counter offers?? Otherwise exit trades
		//offer to trade with other players??
		//Low Priority
}

void propertyManage {
		//if a monopoly is held
		//ask if they would like to purchase houses and how many
		//if maximum houses ask if they would like to purchase hotels
		//subtract any houses or hotels from the game total
		//subtract money from the bank of the purchasing player
}

void propertyMortgage {
		//Need Money? Mortgage for a certain price
		//Change flag for property to mortgaged (bool Mortgage = true)
		//Set amount to unmortgage
}
