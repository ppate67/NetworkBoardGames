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


class gameProperty{
private:
	int price; //Price for that property
	int rent; //Amount it costs if landed on
	int mortgage; //Amount of money you get if mortgaged
	int owner; //Owner of property, originally set to null
	int position; //Position on the board
	int houses; //Amount of house (5 houses = 1 hotel)
  int build;
	int category; //What color cattegory it is instructions
	bool Mortgage; //Is it mortgaged?
public:
	gameProperty(int price, int rent, int mortgage, int owner, int position, int houses, int build, int category, bool Mortgage)
};

class gameRailRoad{
Private:
	int price; //Price for that property
	int rent; //Amount it costs if landed on
	int mortgage; //Amount of money you get if mortgaged
	int owner; //Owner of property, originally set to null
	int position; //Position on the board
	bool Mortgage; //Is it mortgaged?
public:
	gameRailRoad(int price, int rent, int mortgage, int owner, int position, bool Mortgage)


};

class Card{
private:
	int type; // chance or community chest
	string text; // the instructions on the card
	int amount; // amount of money to add or subtract from the player according to the card
	int position;
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


//Here is where all the properties are initiated
//gameProperty(int price, int rent, int mortgage, int owner, int position, int houses, int build, int category, bool Mortgage)
//Brown = category 1
gameProperty MediterraneanAvenue(60, 2, 30, 0, 1, 0, 50, 1, 0);
gameProperty BalticAvenue(60, 4, 30, 0, 3, 0, 50, 1, 0);
//LightBlue = category 2
gameProperty OrientalAvenue(100, 6, 50, 0, 6, 0, 50, 2, 0);
gameProperty VermontAvenue(100, 6, 50, 0, 8, 0, 50, 2, 0);
gameProperty MediterraneanAvenue(120, 8, 60, 0, 9, 0, 50, 2, 0);
//Pink = category 3
gameProperty StCharlesPlace(140, 10, 70, 0, 11, 0, 100, 3, 0);
gameProperty StatesAvenue(140, 10, 70, 0, 13, 0, 100, 3, 0);
gameProperty VirginiaAvenue(160, 12, 80, 0, 14, 0, 100, 3, 0);
//Orange = category 4
gameProperty StJamesPlace(180, 14, 90, 0, 16, 0, 100, 4, 0);
gameProperty TennesseeAvenue(180, 14, 90, 0, 18, 0, 100, 4, 0);
gameProperty NewYorkAvenue(200, 16, 100, 0, 19, 0, 100, 4, 0);
//Red = category 5
gameProperty KentuckyAvenue(220, 18, 110, 0, 21, 0, 150, 5, 0);
gameProperty IndianaAvenue(220, 18, 110, 0, 23, 0, 150, 5, 0);
gameProperty IllinoisAvenue(240, 20, 120, 0, 24, 0, 150, 5, 0);
//Yellow = category 6
gameProperty AtlanticAvenue(260, 22, 130, 0, 26, 0, 150, 6, 0);
gameProperty VentnorAvenue(260, 22, 130, 0, 27, 0, 150, 6, 0);
gameProperty MarvinGardens(280, 24, 140, 0, 29, 0, 150, 6, 0);
//Green = category 7
gameProperty PacificAvenue(300, 26, 150, 0, 31, 0, 200, 7, 0);
gameProperty NorthCarolinaAvenue(300, 26, 150, 0, 32, 0, 200, 7, 0);
gameProperty PennsylvaniaAvenue(320, 28, 160, 0, 34, 0, 200, 7, 0);
//DarkBlue = category 8
gameProperty ParkPlace(350, 35, 175, 0, 37, 0, 200, 8, 0);
gameProperty Boardwalk(400, 50, 200, 0, 39, 0, 200, 8, 0);


//gameRailRoad(int price, int rent, int mortgage, int owner, int position, bool Mortgage)
gameRailRoad Reading_Railroad(200, 25, 100, 0, 5, 0);
gameRailRoad Pennsylvania_Railroad(200, 25, 100, 0, 15, 0);
gameRailRoad BandO_Railroad(200, 25, 100, 0, 25, 0);
gameRailRoad ShortLine_Railroad(200, 25, 100, 0, 35, 0);

//Utilities == gameRailRoad(int price, int rent, int mortgage, int owner, int position, bool Mortgage)
gameRailRoad Electric_Company(150, (4 * dieroll), 75, 0, 12, 0);
gameRailRoad Electric_Company(150, (4 * dieroll), 75, 0, 28, 0);


//Community Chest == Card(int type, string text, int amount)

Card a(1,"Advance to Go (Collect $200)", 200);
Card b(1, "Bank error in your favor – collect $75 ", 75);
Card c(1, "Doctor's fees – Pay $50 ", -50)
Card d(1, "Get out of jail free – this card may be kept until needed, or sold", 0)



int main() {

}
