#include <iostream>
#include <cstdlib>
#include "mainwindow.h"
#include <QApplication>
#include "boardspace.h"
#include "cards.h"
#include "player.h"

using namespace std;


void dieroll(int& roll1, int& roll2, int& totalRoll) {
    srand(time(NULL));
    roll1 = rand()%6+1;
    roll2 = rand()%6+1;
    totalRoll = roll1 + roll2;
}

int randomCard(){
    int num;
    srand(time(NULL));
    num = rand()%14;
    return num;
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

// -------INITIALIZE BOARDSPACES-------

    boardSpace spaces[40];

    //Space 0
    spaces[0].setName("   GO!   ");
    spaces[0].setType("START");
    spaces[0].setPropertyCost(0);
    spaces[0].setFreeParking(0);
    spaces[0].setOccupied(true);
    spaces[0].setOwnership(-1);
    spaces[0].setMortgaged(false);
    spaces[0].setRent(0);
    spaces[0].setTax(0);
    spaces[0].setActionText("Pass GO, Get $200");

    //Space 1
    spaces[1].setName("Old Kent Road");
    spaces[1].setType("Property");
    spaces[1].setPropertyCost(60);
    spaces[1].setFreeParking(0);
    spaces[1].setOccupied(false);
    spaces[1].setOwnership(-1);
    spaces[1].setMortgaged(false);
    spaces[1].setRent(2);
    spaces[1].setTax(0);
    spaces[1].setActionText("$60");

    //Space 2
    spaces[2].setName("Community Chest");
    spaces[2].setType("Community Chest");
    spaces[2].setPropertyCost(0);
    spaces[2].setFreeParking(0);
    spaces[2].setOccupied(false);
    spaces[2].setOwnership(-1);
    spaces[2].setMortgaged(false);
    spaces[2].setRent(0);
    spaces[2].setTax(0);
    spaces[2].setActionText("Draw a Card");

    //Space 3
    spaces[3].setName("White Chapel Road");
    spaces[3].setType("Property");
    spaces[3].setPropertyCost(60);
    spaces[3].setFreeParking(0);
    spaces[3].setOccupied(false);
    spaces[3].setOwnership(-1);
    spaces[3].setMortgaged(false);
    spaces[3].setRent(4);
    spaces[3].setTax(0);
    spaces[3].setActionText("$60");


    //Space 4
    spaces[4].setName("Income Tax");
    spaces[4].setType("Tax");
    spaces[4].setPropertyCost(0);
    spaces[4].setFreeParking(0);
    spaces[4].setOccupied(false);
    spaces[4].setOwnership(-1);
    spaces[4].setMortgaged(false);
    spaces[4].setRent(4);
    spaces[4].setTax(200);
    spaces[4].setActionText("Pay $200");

    //Space 5
    spaces[5].setName("Kings Cross Station");
    spaces[5].setType("RailRoad");
    spaces[5].setPropertyCost(200);
    spaces[5].setFreeParking(0);
    spaces[5].setOccupied(false);
    spaces[5].setOwnership(-1);
    spaces[5].setMortgaged(false);
    spaces[5].setRent(25);
    spaces[5].setTax(0);
    spaces[5].setActionText("$200");

    //Space 6
    spaces[6].setName("The Angel, Islington");
    spaces[6].setType("Property");
    spaces[6].setPropertyCost(100);
    spaces[6].setFreeParking(0);
    spaces[6].setOccupied(false);
    spaces[6].setOwnership(-1);
    spaces[6].setMortgaged(false);
    spaces[6].setRent(6);
    spaces[6].setTax(0);
    spaces[6].setActionText("$100");

    //Space 7
    spaces[7].setName("Chance");
    spaces[7].setType("Chance");
    spaces[7].setPropertyCost(0);
    spaces[7].setFreeParking(0);
    spaces[7].setOccupied(false);
    spaces[7].setOwnership(-1);
    spaces[7].setMortgaged(false);
    spaces[7].setRent(0);
    spaces[7].setTax(0);
    spaces[7].setActionText("Draw a card");

    //Space 8
    spaces[8].setName("Euston Road");
    spaces[8].setType("Property");
    spaces[8].setPropertyCost(100);
    spaces[8].setFreeParking(0);
    spaces[8].setOccupied(false);
    spaces[8].setOwnership(-1);
    spaces[8].setMortgaged(false);
    spaces[8].setRent(6);
    spaces[8].setTax(0);
    spaces[8].setActionText("$100");

    //Space 9
    spaces[9].setName("Pentonville Road");
    spaces[9].setType("Property");
    spaces[9].setPropertyCost(120);
    spaces[9].setFreeParking(0);
    spaces[9].setOccupied(false);
    spaces[9].setOwnership(-1);
    spaces[9].setMortgaged(false);
    spaces[9].setRent(8);
    spaces[9].setTax(0);
    spaces[9].setActionText("$120");


    //Space 10
    spaces[10].setName("Jail!");
    spaces[10].setType("Jail");
    spaces[10].setPropertyCost(0);
    spaces[10].setFreeParking(0);
    spaces[10].setOccupied(false);
    spaces[10].setOwnership(-1);
    spaces[10].setMortgaged(false);
    spaces[10].setRent(0);
    spaces[10].setTax(0);
    spaces[10].setActionText("Just Visiting");

    //Space 11
    spaces[11].setName("Pall Mall");
    spaces[11].setType("Property");
    spaces[11].setPropertyCost(140);
    spaces[11].setFreeParking(0);
    spaces[11].setOccupied(false);
    spaces[11].setOwnership(-1);
    spaces[11].setMortgaged(false);
    spaces[11].setRent(10);
    spaces[11].setTax(0);
    spaces[11].setActionText("$140");

    //Space 12
    spaces[12].setName("ELectic Company");
    spaces[12].setType("Utility");
    spaces[12].setPropertyCost(150);
    spaces[12].setFreeParking(0);
    spaces[12].setOccupied(false);
    spaces[12].setOwnership(-1);
    spaces[12].setMortgaged(false);
    spaces[12].setRent(10);
    spaces[12].setTax(0);
    spaces[12].setActionText("$150");


    //Space 13
    spaces[13].setName("Whitehall");
    spaces[13].setType("Property");
    spaces[13].setPropertyCost(140);
    spaces[13].setFreeParking(0);
    spaces[13].setOccupied(false);
    spaces[13].setOwnership(-1);
    spaces[13].setMortgaged(false);
    spaces[13].setRent(10);
    spaces[13].setTax(0);
    spaces[13].setActionText("$140");

    //Space 14
    spaces[14].setName("Northumrl'd Avenue");
    spaces[14].setType("Property");
    spaces[14].setPropertyCost(160);
    spaces[14].setFreeParking(0);
    spaces[14].setOccupied(false);
    spaces[14].setOwnership(-1);
    spaces[14].setMortgaged(false);
    spaces[14].setRent(12);
    spaces[14].setTax(0);
    spaces[14].setActionText("$160");

    //Space 15
    spaces[15].setName("Marylebone Station");
    spaces[15].setType("RailRoad");
    spaces[15].setPropertyCost(200);
    spaces[15].setFreeParking(0);
    spaces[15].setOccupied(false);
    spaces[15].setOwnership(-1);
    spaces[15].setMortgaged(false);
    spaces[15].setRent(25);
    spaces[15].setTax(0);
    spaces[15].setActionText("$200");

    //Space 16
    spaces[16].setName("Bow Street");
    spaces[16].setType("Property");
    spaces[16].setPropertyCost(180);
    spaces[16].setFreeParking(0);
    spaces[16].setOccupied(false);
    spaces[16].setOwnership(-1);
    spaces[16].setMortgaged(false);
    spaces[16].setRent(14);
    spaces[16].setTax(0);
    spaces[16].setActionText("$180");

    //Space 17
    spaces[17].setName("Community Chest");
    spaces[17].setType("Community Chest");
    spaces[17].setPropertyCost(0);
    spaces[17].setFreeParking(0);
    spaces[17].setOccupied(false);
    spaces[17].setOwnership(-1);
    spaces[17].setMortgaged(false);
    spaces[17].setRent(0);
    spaces[17].setTax(0);
    spaces[17].setActionText("Draw a Card");

    //Space 18
    spaces[18].setName("Marlborough Street");
    spaces[18].setType("Property");
    spaces[18].setPropertyCost(180);
    spaces[18].setFreeParking(0);
    spaces[18].setOccupied(false);
    spaces[18].setOwnership(-1);
    spaces[18].setMortgaged(false);
    spaces[18].setRent(14);
    spaces[18].setTax(0);
    spaces[18].setActionText("$180");

    //Space 19
    spaces[19].setName("Vine Street");
    spaces[19].setType("Property");
    spaces[19].setPropertyCost(200);
    spaces[19].setFreeParking(0);
    spaces[19].setOccupied(false);
    spaces[19].setOwnership(-1);
    spaces[19].setMortgaged(false);
    spaces[19].setRent(16);
    spaces[19].setTax(0);
    spaces[19].setActionText("$200");

    //Space 20
    spaces[20].setName("FREE PARKING");
    spaces[20].setType("FreeParking");
    spaces[20].setPropertyCost(0);
    spaces[20].setFreeParking(0);
    spaces[20].setOccupied(false);
    spaces[20].setOwnership(-1);
    spaces[20].setMortgaged(false);
    spaces[20].setRent(0);
    spaces[20].setTax(0);
    spaces[20].setActionText(" ");

    //Space 21
    spaces[21].setName("Strand");
    spaces[21].setType("Property");
    spaces[21].setPropertyCost(220);
    spaces[21].setFreeParking(0);
    spaces[21].setOccupied(false);
    spaces[21].setOwnership(-1);
    spaces[21].setMortgaged(false);
    spaces[21].setRent(18);
    spaces[21].setTax(0);
    spaces[21].setActionText("$220");

    //Space 22
    spaces[22].setName("Chance");
    spaces[22].setType("Chance");
    spaces[22].setPropertyCost(0);
    spaces[22].setFreeParking(0);
    spaces[22].setOccupied(false);
    spaces[22].setOwnership(-1);
    spaces[22].setMortgaged(false);
    spaces[22].setRent(0);
    spaces[22].setTax(0);
    spaces[22].setActionText("Draw a Card");

    //Space 23
    spaces[23].setName("Fleet Street");
    spaces[23].setType("Property");
    spaces[23].setPropertyCost(220);
    spaces[23].setFreeParking(0);
    spaces[23].setOccupied(false);
    spaces[23].setOwnership(-1);
    spaces[23].setMortgaged(false);
    spaces[23].setRent(18);
    spaces[23].setTax(0);
    spaces[23].setActionText("$220");

    //Space 24
    spaces[24].setName("Trafalgar Square");
    spaces[24].setType("Property");
    spaces[24].setPropertyCost(240);
    spaces[24].setFreeParking(0);
    spaces[24].setOccupied(false);
    spaces[24].setOwnership(-1);
    spaces[24].setMortgaged(false);
    spaces[24].setRent(20);
    spaces[24].setTax(0);
    spaces[24].setActionText("$240");

    //Space 25
    spaces[25].setName("Fenchurch St. Station");
    spaces[25].setType("RailRoad");
    spaces[25].setPropertyCost(200);
    spaces[25].setFreeParking(0);
    spaces[25].setOccupied(false);
    spaces[25].setOwnership(-1);
    spaces[25].setMortgaged(false);
    spaces[25].setRent(25);
    spaces[25].setTax(0);
    spaces[25].setActionText("$200");

    //Space 26
    spaces[26].setName("Leicester Square");
    spaces[26].setType("Property");
    spaces[26].setPropertyCost(260);
    spaces[26].setFreeParking(0);
    spaces[26].setOccupied(false);
    spaces[26].setOwnership(-1);
    spaces[26].setMortgaged(false);
    spaces[26].setRent(22);
    spaces[26].setTax(0);
    spaces[26].setActionText("$260");

    //Space 27
    spaces[27].setName("Covenry Street");
    spaces[27].setType("Property");
    spaces[27].setPropertyCost(260);
    spaces[27].setFreeParking(0);
    spaces[27].setOccupied(false);
    spaces[27].setOwnership(-1);
    spaces[27].setMortgaged(false);
    spaces[27].setRent(22);
    spaces[27].setTax(0);
    spaces[27].setActionText("$260");

    //Space 28
    spaces[28].setName("Water Works");
    spaces[28].setType("Utility");
    spaces[28].setPropertyCost(150);
    spaces[28].setFreeParking(0);
    spaces[28].setOccupied(false);
    spaces[28].setOwnership(-1);
    spaces[28].setMortgaged(false);
    spaces[28].setRent(10);
    spaces[28].setTax(0);
    spaces[28].setActionText("$150");

    //Space 29
    spaces[29].setName("Piccadilly");
    spaces[29].setType("Property");
    spaces[29].setPropertyCost(280);
    spaces[29].setFreeParking(0);
    spaces[29].setOccupied(false);
    spaces[29].setOwnership(-1);
    spaces[29].setMortgaged(false);
    spaces[29].setRent(22);
    spaces[29].setTax(0);
    spaces[29].setActionText("280");

    //Space 30
    spaces[30].setName("Go to Jail!");
    spaces[30].setType("GoJail");
    spaces[30].setPropertyCost(0);
    spaces[30].setFreeParking(0);
    spaces[30].setOccupied(false);
    spaces[30].setOwnership(-1);
    spaces[30].setMortgaged(false);
    spaces[30].setRent(0);
    spaces[30].setTax(0);
    spaces[30].setActionText(" ");

    //Space 31
    spaces[31].setName("Regent Street");
    spaces[31].setType("Property");
    spaces[31].setPropertyCost(300);
    spaces[31].setFreeParking(0);
    spaces[31].setOccupied(false);
    spaces[31].setOwnership(-1);
    spaces[31].setMortgaged(false);
    spaces[31].setRent(26);
    spaces[31].setTax(0);
    spaces[31].setActionText("$300");

    //Space 32
    spaces[32].setName("Oxford Street");
    spaces[32].setType("Property");
    spaces[32].setPropertyCost(300);
    spaces[32].setFreeParking(0);
    spaces[32].setOccupied(false);
    spaces[32].setOwnership(-1);
    spaces[32].setMortgaged(false);
    spaces[32].setRent(26);
    spaces[32].setTax(0);
    spaces[32].setActionText("$300");

    //Space 33
    spaces[33].setName("Commnunity Chest");
    spaces[33].setType("Community Chest");
    spaces[33].setPropertyCost(0);
    spaces[33].setFreeParking(0);
    spaces[33].setOccupied(false);
    spaces[33].setOwnership(-1);
    spaces[33].setMortgaged(false);
    spaces[33].setRent(0);
    spaces[33].setTax(0);
    spaces[33].setActionText("Draw a card");

    //Space 34
    spaces[34].setName("Bond Street");
    spaces[34].setType("Property");
    spaces[34].setPropertyCost(320);
    spaces[34].setFreeParking(0);
    spaces[34].setOccupied(false);
    spaces[34].setOwnership(-1);
    spaces[34].setMortgaged(false);
    spaces[34].setRent(28);
    spaces[34].setTax(0);
    spaces[34].setActionText("$320");

    //Space 35
    spaces[35].setName("Liverpool St. Station");
    spaces[35].setType("RailRoad");
    spaces[35].setPropertyCost(200);
    spaces[35].setFreeParking(0);
    spaces[35].setOccupied(false);
    spaces[35].setOwnership(-1);
    spaces[35].setMortgaged(false);
    spaces[35].setRent(25);
    spaces[35].setTax(0);
    spaces[35].setActionText("$200");

    //Space 36
    spaces[36].setName("Chance");
    spaces[36].setType("Chance");
    spaces[36].setPropertyCost(0);
    spaces[36].setFreeParking(0);
    spaces[36].setOccupied(false);
    spaces[36].setOwnership(-1);
    spaces[36].setMortgaged(false);
    spaces[36].setRent(0);
    spaces[36].setTax(0);
    spaces[36].setActionText("Draw a Card");

    //Space 37
    spaces[37].setName("Park Lane");
    spaces[37].setType("Property");
    spaces[37].setPropertyCost(350);
    spaces[37].setFreeParking(0);
    spaces[37].setOccupied(false);
    spaces[37].setOwnership(-1);
    spaces[37].setMortgaged(false);
    spaces[37].setRent(35);
    spaces[37].setTax(0);
    spaces[37].setActionText("$350");

    //Space 38
    spaces[38].setName("Super Tax");
    spaces[38].setType("Tax");
    spaces[38].setPropertyCost(0);
    spaces[38].setFreeParking(0);
    spaces[38].setOccupied(false);
    spaces[38].setOwnership(-1);
    spaces[38].setMortgaged(false);
    spaces[38].setRent(0);
    spaces[38].setTax(75);
    spaces[38].setActionText("Pay $100");

    //Space 39
    spaces[39].setName("Mayfair");
    spaces[39].setType("Property");
    spaces[39].setPropertyCost(400);
    spaces[39].setFreeParking(0);
    spaces[39].setOccupied(false);
    spaces[39].setOwnership(-1);
    spaces[39].setMortgaged(false);
    spaces[39].setRent(50);
    spaces[39].setTax(0);
    spaces[39].setActionText("$400");

    for(int i = 0; i < 40; i++){
        spaces[i].setHouses(0);
    }

//-------END BOARD SPACE INITIALIZATION-------

//-------START OF COMMUNITY CHEST INITIALIZATION-------

    Card CommunityChest[14];

    //Community Chest 0
    CommunityChest[0].setText("COMMUNITY CHEST: Here is a free $200");
    CommunityChest[0].setAmount(200);

    //Community Chest 1
    CommunityChest[1].setText("COMMUNITY CHEST: Bank error in your favor – collect $75");
    CommunityChest[1].setAmount(75);

    //Community Chest 2
    CommunityChest[2].setText("COMMUNITY CHEST: Doctor's fee – Pay $50");
    CommunityChest[2].setAmount(-50);

    //Community Chest 3
    CommunityChest[3].setText("COMMUNITY CHEST: From sale of stock you get $50");
    CommunityChest[3].setAmount(50);

    //Community Chest 4
    CommunityChest[4].setText("COMMUNITY CHEST: Get out of jail free – this card may be kept until needed, or sold");
    CommunityChest[4].setAmount(0);

    //Community Chest 5
    CommunityChest[5].setText("COMMUNITY CHEST: Go to Jail – Go directly to jail – Do not pass Go – Do not collect $200");
    CommunityChest[5].setAmount(0);

    //Community Chest 6
    CommunityChest[6].setText("COMMUNITY CHEST: Holiday Fund matures - Collect $100");
    CommunityChest[6].setAmount(100);

    //Community Chest 7
    CommunityChest[7].setText("COMMUNITY CHEST: Income tax refund – Collect $20");
    CommunityChest[7].setAmount(20);

    //Community Chest 8
    CommunityChest[8].setText("COMMUNITY CHEST: Life insurance matures – Collect $100");
    CommunityChest[8].setAmount(100);

    //Community Chest 9
    CommunityChest[9].setText("COMMUNITY CHEST: Pay hospital fees of $100");
    CommunityChest[9].setAmount(-100);

    //Community Chest 10
    CommunityChest[10].setText("COMMUNITY CHEST: Pay school fees of $150");
    CommunityChest[10].setAmount(-150);

    //Community Chest 11
    CommunityChest[11].setText("COMMUNITY CHEST: Receive $25 consultancy fee");
    CommunityChest[11].setAmount(25);

    //Community Chest 12
    CommunityChest[12].setText("COMMUNITY CHEST:You have won second prize in a beauty contest – Collect $10");
    CommunityChest[12].setAmount(10);

    //Community Chest 13
    CommunityChest[13].setText("COMMUNITY CHEST: You inherit $100");
    CommunityChest[13].setAmount(100);


    //-------END OF COMMUNITY CHEST INITIALIZATION-------

    //-------START OF CHANCE CARD INITIALIZATION-------

    Card Chance[14];

    //Chance 0
    Chance[0].setText("CHANCE: Here is a free $200");
    Chance[0].setAmount(200);

    //Chance 1
    Chance[1].setText("CHANCE: Bank pays you dividend of $50");
    Chance[1].setAmount(50);

    //Chance 2
    Chance[2].setText("CHANCE: Pay poor tax of $15");
    Chance[2].setAmount(-15);

    //Chance 3
    Chance[3].setText("CHANCE: Your building and loan matures – Collect $150");
    Chance[3].setAmount(150);

    //Chance 4
    Chance[4].setText("CHANCE: Get out of jail free – this card may be kept until needed, or sold");
    Chance[4].setAmount(0);

    //Chance 5
    Chance[5].setText("CHANCE: Go to Jail – Go directly to jail – Do not pass Go – Do not collect $200");
    Chance[5].setAmount(0);

    //Chance 6
    Chance[6].setText("CHANCE: You have won a crossword competition -  Collect $100");
    Chance[6].setAmount(100);

    //Chance 7
    Chance[7].setText("CHANCE: Holiday Fund matures - Collect $100");
    Chance[7].setAmount(100);

    //Chance 8
    Chance[8].setText("CHANCE: Life insurance matures – Collect $100");
    Chance[8].setAmount(100);

    //Chance 9
    Chance[9].setText("CHANCE: Pay hospital fees of $100");
    Chance[9].setAmount(-100);

    //Chance 10
    Chance[10].setText("CHANCE: Pay school fees of $150");
    Chance[10].setAmount(-150);

    //Chance 11
    Chance[11].setText("CHANCE: Receive $25 consultancy fee");
    Chance[11].setAmount(25);

    //Chance 12
    Chance[12].setText("CHANCE:You have won second prize in a beauty contest – Collect $10");
    Chance[12].setAmount(10);

    //Chance 13
    Chance[13].setText("CHANCE: You inherit $100");
    Chance[13].setAmount(100);


    //-------END OF CHANCE CARD INITIALIZATION-------

    //-------START OF PLAYER INITIALIZATION-------
    //Making game only 2 players to start out
    Player player1("Player 1", 1, 500, 0, 0);
    Player player2("Player 2", 1, 500, 0, 0);

    //-------END OF PLAYER INITIALIZATION-------

    return a.exec();
}
