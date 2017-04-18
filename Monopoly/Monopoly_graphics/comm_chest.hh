#ifndef comm_chest_HH_
#define comm_chest_HH_

#include <string>

class Card{
private:
	int type; // chance or community chest
	string text; // the instructions on the card
	int amount; // amount of money to add or subtract from the player according to the card
	int position;
public:
	Card(int type, string text, int amount, int position) : type(type), text(text), amount(amount), position(position){}


	Card a(1,"Advance to Go (Collect $200)", 200);
	Card b(1, "Bank error in your favor – collect $75 ", 75);
	Card c(1, "Doctor's fee – Pay $50 ", -50);
	Card d(1,"From sale of stock you get $50", 50);
	Card e(1, "Get out of jail free – this card may be kept until needed, or sold", 0);
	Card f(1,"Go to Jail – Go directly to jail – Do not pass Go – Do not collect $200",0);
	Card g(1,"Grand Opera Night – Collect $50 from every player for opening night seats",50 * numPlayers);
	Card h(1,"Holiday Fund matures - Collect $100 ",100);
	Card i(1,"Income tax refund – Collect $20",20);
	Card j(1,"It is your birthday - Collect $10 from each player",10 * numPlayers);
	Card k(1,"Life insurance matures – Collect $100",100);
	Card l(1,"Pay hospital fees of $100",-100);
	Card m(1,"Pay school fees of $150",-150);
	Card n(1,"Receive $25 consultancy fee",25);
	Card o(1,"You are assessed for street repairs – $40 per house – $115 per hotel",?);
	Card p(1,"You have won second prize in a beauty contest – Collect $10", 10);
	Card q(1,"You inherit $100",100);
};
