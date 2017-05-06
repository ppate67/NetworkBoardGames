#include <ctime>
#include <cstdlib>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "player.h"
#include "boardspace.h"
#include "cards.h"
#include <QPixmap>
#include<QMessageBox>
#include <string>
#include <iostream>

using namespace std;

//Dice Roll Function (Random of Two Dice Rolls then summed together)
void dieRoll(int& roll1, int& roll2, int& totalRoll) {
    srand(time(NULL));
    roll1 = rand()%6+1;
    roll2 = rand()%6+1;
    totalRoll = roll1 + roll2;
}
//Picks a random number 0-13 so that a card can be chosen
int randomCard(){
    int num;
    srand(time(NULL));
    num = rand()%14;
    return num;
}


//Initializes the Player Classes


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    turnNumber = 0; //Tracks Whose turn it is (player 1 or Player 2)
    numberOfTurns =1; //Tracks How many total Turns have been Taken


    //Initializes the Players 1 and 2
    players = new Player*[2];
    players[0] = new Player;
    players[1] = new Player;

    players[0]->setName("Player 1");
    players[0]->setUserID(1);
    players[0]->setBank(2000);
    players[0]->setJailFree(0);
    players[0]->setPosition(0);
    players[0]->setJail(false);

    players[1]->setName("Player 2");
    players[1]->setUserID(2);
    players[1]->setBank(2000);
    players[1]->setJailFree(0);
    players[1]->setPosition(0);
    players[1]->setJail(false);

    // -------INITIALIZE BOARDSPACES-------

    spaces = new boardSpace*[40];
    //boardSpace spaces[40];

    for( int i = 0; i < 40; i++) {
        spaces[i] = new boardSpace;
    }

    //Space 0
    spaces[0]->setName("GO!");
    spaces[0]->setType("START");
    spaces[0]->setPropertyCost(0);
    spaces[0]->setFreeParking(0);
    spaces[0]->setOccupied(true);
    spaces[0]->setOwnership(100);
    spaces[0]->setMortgaged(false);
    spaces[0]->setRent(0);
    spaces[0]->setTax(0);
    spaces[0]->setActionText("Pass GO, Get $200");
    spaces[0]->setXcoordinate(730);
    spaces[0]->setYcoordinate(630);

    //Space 1
    spaces[1]->setName("Old Kent Road");
    spaces[1]->setType("Property");
    spaces[1]->setPropertyCost(60);
    spaces[1]->setFreeParking(0);
    spaces[1]->setOccupied(false);
    spaces[1]->setOwnership(100);
    spaces[1]->setMortgaged(false);
    spaces[1]->setRent(20);
    spaces[1]->setTax(0);
    spaces[1]->setActionText("$60");
    spaces[1]->setXcoordinate(640);
    spaces[1]->setYcoordinate(640);

    //Space 2
    spaces[2]->setName("Community Chest");
    spaces[2]->setType("Community Chest");
    spaces[2]->setPropertyCost(0);
    spaces[2]->setFreeParking(0);
    spaces[2]->setOccupied(false);
    spaces[2]->setOwnership(100);
    spaces[2]->setMortgaged(false);
    spaces[2]->setRent(0);
    spaces[2]->setTax(0);
    spaces[2]->setActionText("Draw a Card");
    spaces[2]->setXcoordinate(580);
    spaces[2]->setYcoordinate(640);

    //Space 3
    spaces[3]->setName("White Chapel Road");
    spaces[3]->setType("Property");
    spaces[3]->setPropertyCost(60);
    spaces[3]->setFreeParking(0);
    spaces[3]->setOccupied(false);
    spaces[3]->setOwnership(100);
    spaces[3]->setMortgaged(false);
    spaces[3]->setRent(40);
    spaces[3]->setTax(0);
    spaces[3]->setActionText("$60");
    spaces[3]->setXcoordinate(510);
    spaces[3]->setYcoordinate(640);


    //Space 4
    spaces[4]->setName("Income Tax");
    spaces[4]->setType("Tax");
    spaces[4]->setPropertyCost(0);
    spaces[4]->setFreeParking(0);
    spaces[4]->setOccupied(false);
    spaces[4]->setOwnership(100);
    spaces[4]->setMortgaged(false);
    spaces[4]->setRent(200);
    spaces[4]->setTax(200);
    spaces[4]->setActionText("Pay $200");
    spaces[4]->setXcoordinate(450);
    spaces[4]->setYcoordinate(640);

    //Space 5
    spaces[5]->setName("Kings Cross Station");
    spaces[5]->setType("RailRoad");
    spaces[5]->setPropertyCost(200);
    spaces[5]->setFreeParking(0);
    spaces[5]->setOccupied(false);
    spaces[5]->setOwnership(100);
    spaces[5]->setMortgaged(false);
    spaces[5]->setRent(100);
    spaces[5]->setTax(0);
    spaces[5]->setActionText("$200");
    spaces[5]->setXcoordinate(390);
    spaces[5]->setYcoordinate(640);

    //Space 6
    spaces[6]->setName("The Angel, Islington");
    spaces[6]->setType("Property");
    spaces[6]->setPropertyCost(100);
    spaces[6]->setFreeParking(0);
    spaces[6]->setOccupied(false);
    spaces[6]->setOwnership(100);
    spaces[6]->setMortgaged(false);
    spaces[6]->setRent(60);
    spaces[6]->setTax(0);
    spaces[6]->setActionText("$100");
    spaces[6]->setXcoordinate(330);
    spaces[6]->setYcoordinate(640);

    //Space 7
    spaces[7]->setName("Chance");
    spaces[7]->setType("Chance");
    spaces[7]->setPropertyCost(0);
    spaces[7]->setFreeParking(0);
    spaces[7]->setOccupied(false);
    spaces[7]->setOwnership(100);
    spaces[7]->setMortgaged(false);
    spaces[7]->setRent(0);
    spaces[7]->setTax(0);
    spaces[7]->setActionText("Draw a card");
    spaces[7]->setXcoordinate(270);
    spaces[7]->setYcoordinate(640);

    //Space 8
    spaces[8]->setName("Euston Road");
    spaces[8]->setType("Property");
    spaces[8]->setPropertyCost(100);
    spaces[8]->setFreeParking(0);
    spaces[8]->setOccupied(false);
    spaces[8]->setOwnership(100);
    spaces[8]->setMortgaged(false);
    spaces[8]->setRent(60);
    spaces[8]->setTax(0);
    spaces[8]->setActionText("$100");
    spaces[8]->setXcoordinate(200);
    spaces[8]->setYcoordinate(640);

    //Space 9
    spaces[9]->setName("Pentonville Road");
    spaces[9]->setType("Property");
    spaces[9]->setPropertyCost(120);
    spaces[9]->setFreeParking(0);
    spaces[9]->setOccupied(false);
    spaces[9]->setOwnership(100);
    spaces[9]->setMortgaged(false);
    spaces[9]->setRent(80);
    spaces[9]->setTax(0);
    spaces[9]->setActionText("$120");
    spaces[9]->setXcoordinate(140);
    spaces[9]->setYcoordinate(640);


    //Space 10
    spaces[10]->setName("Jail!");
    spaces[10]->setType("Jail");
    spaces[10]->setPropertyCost(0);
    spaces[10]->setFreeParking(0);
    spaces[10]->setOccupied(false);
    spaces[10]->setOwnership(100);
    spaces[10]->setMortgaged(false);
    spaces[10]->setRent(0);
    spaces[10]->setTax(0);
    spaces[10]->setActionText("Just Visiting");
    spaces[10]->setXcoordinate(30);
    spaces[10]->setYcoordinate(650);

    //Space 11
    spaces[11]->setName("Pall Mall");
    spaces[11]->setType("Property");
    spaces[11]->setPropertyCost(140);
    spaces[11]->setFreeParking(0);
    spaces[11]->setOccupied(false);
    spaces[11]->setOwnership(100);
    spaces[11]->setMortgaged(false);
    spaces[11]->setRent(100);
    spaces[11]->setTax(0);
    spaces[11]->setActionText("$140");
    spaces[11]->setXcoordinate(50);
    spaces[11]->setYcoordinate(550);

    //Space 12
    spaces[12]->setName("Electic Company");
    spaces[12]->setType("Utility");
    spaces[12]->setPropertyCost(150);
    spaces[12]->setFreeParking(0);
    spaces[12]->setOccupied(false);
    spaces[12]->setOwnership(100);
    spaces[12]->setMortgaged(false);
    spaces[12]->setRent(100);
    spaces[12]->setTax(0);
    spaces[12]->setActionText("$150");
    spaces[12]->setXcoordinate(50);
    spaces[12]->setYcoordinate(500);

    //Space 13
    spaces[13]->setName("Whitehall");
    spaces[13]->setType("Property");
    spaces[13]->setPropertyCost(140);
    spaces[13]->setFreeParking(0);
    spaces[13]->setOccupied(false);
    spaces[13]->setOwnership(100);
    spaces[13]->setMortgaged(false);
    spaces[13]->setRent(100);
    spaces[13]->setTax(0);
    spaces[13]->setActionText("$140");
    spaces[13]->setXcoordinate(50);
    spaces[13]->setYcoordinate(450);

    //Space 14
    spaces[14]->setName("Northumrl'd Avenue");
    spaces[14]->setType("Property");
    spaces[14]->setPropertyCost(160);
    spaces[14]->setFreeParking(0);
    spaces[14]->setOccupied(false);
    spaces[14]->setOwnership(100);
    spaces[14]->setMortgaged(false);
    spaces[14]->setRent(120);
    spaces[14]->setTax(0);
    spaces[14]->setActionText("$160");
    spaces[14]->setXcoordinate(50);
    spaces[14]->setYcoordinate(390);

    //Space 15
    spaces[15]->setName("Marylebone Station");
    spaces[15]->setType("RailRoad");
    spaces[15]->setPropertyCost(200);
    spaces[15]->setFreeParking(0);
    spaces[15]->setOccupied(false);
    spaces[15]->setOwnership(100);
    spaces[15]->setMortgaged(false);
    spaces[15]->setRent(100);
    spaces[15]->setTax(0);
    spaces[15]->setActionText("$200");
    spaces[15]->setXcoordinate(50);
    spaces[15]->setYcoordinate(340);

    //Space 16
    spaces[16]->setName("Bow Street");
    spaces[16]->setType("Property");
    spaces[16]->setPropertyCost(180);
    spaces[16]->setFreeParking(0);
    spaces[16]->setOccupied(false);
    spaces[16]->setOwnership(100);
    spaces[16]->setMortgaged(false);
    spaces[16]->setRent(140);
    spaces[16]->setTax(0);
    spaces[16]->setActionText("$180");
    spaces[16]->setXcoordinate(50);
    spaces[16]->setYcoordinate(280);

    //Space 17
    spaces[17]->setName("Community Chest");
    spaces[17]->setType("Community Chest");
    spaces[17]->setPropertyCost(0);
    spaces[17]->setFreeParking(0);
    spaces[17]->setOccupied(false);
    spaces[17]->setOwnership(100);
    spaces[17]->setMortgaged(false);
    spaces[17]->setRent(0);
    spaces[17]->setTax(0);
    spaces[17]->setActionText("Draw a Card");
    spaces[17]->setXcoordinate(50);
    spaces[17]->setYcoordinate(230);

    //Space 18
    spaces[18]->setName("Marlborough Street");
    spaces[18]->setType("Property");
    spaces[18]->setPropertyCost(180);
    spaces[18]->setFreeParking(0);
    spaces[18]->setOccupied(false);
    spaces[18]->setOwnership(100);
    spaces[18]->setMortgaged(false);
    spaces[18]->setRent(140);
    spaces[18]->setTax(0);
    spaces[18]->setActionText("$180");
    spaces[18]->setXcoordinate(50);
    spaces[18]->setYcoordinate(180);

    //Space 19
    spaces[19]->setName("Vine Street");
    spaces[19]->setType("Property");
    spaces[19]->setPropertyCost(200);
    spaces[19]->setFreeParking(0);
    spaces[19]->setOccupied(false);
    spaces[19]->setOwnership(100);
    spaces[19]->setMortgaged(false);
    spaces[19]->setRent(160);
    spaces[19]->setTax(0);
    spaces[19]->setActionText("$200");
    spaces[19]->setXcoordinate(50);
    spaces[19]->setYcoordinate(120);

    //Space 20
    spaces[20]->setName("FREE PARKING");
    spaces[20]->setType("FreeParking");
    spaces[20]->setPropertyCost(0);
    spaces[20]->setFreeParking(0);
    spaces[20]->setOccupied(false);
    spaces[20]->setOwnership(100);
    spaces[20]->setMortgaged(false);
    spaces[20]->setRent(0);
    spaces[20]->setTax(0);
    spaces[20]->setActionText(" ");
    spaces[20]->setXcoordinate(50);
    spaces[20]->setYcoordinate(50);

    //Space 21
    spaces[21]->setName("Strand");
    spaces[21]->setType("Property");
    spaces[21]->setPropertyCost(220);
    spaces[21]->setFreeParking(0);
    spaces[21]->setOccupied(false);
    spaces[21]->setOwnership(100);
    spaces[21]->setMortgaged(false);
    spaces[21]->setRent(180);
    spaces[21]->setTax(0);
    spaces[21]->setActionText("$220");
    spaces[21]->setXcoordinate(140);
    spaces[21]->setYcoordinate(40);

    //Space 22
    spaces[22]->setName("Chance");
    spaces[22]->setType("Chance");
    spaces[22]->setPropertyCost(0);
    spaces[22]->setFreeParking(0);
    spaces[22]->setOccupied(false);
    spaces[22]->setOwnership(100);
    spaces[22]->setMortgaged(false);
    spaces[22]->setRent(0);
    spaces[22]->setTax(0);
    spaces[22]->setActionText("Draw a Card");
    spaces[22]->setXcoordinate(200);
    spaces[22]->setYcoordinate(40);

    //Space 23
    spaces[23]->setName("Fleet Street");
    spaces[23]->setType("Property");
    spaces[23]->setPropertyCost(220);
    spaces[23]->setFreeParking(0);
    spaces[23]->setOccupied(false);
    spaces[23]->setOwnership(100);
    spaces[23]->setMortgaged(false);
    spaces[23]->setRent(180);
    spaces[23]->setTax(0);
    spaces[23]->setActionText("$220");
    spaces[23]->setXcoordinate(270);
    spaces[23]->setYcoordinate(40);

    //Space 24
    spaces[24]->setName("Trafalgar Square");
    spaces[24]->setType("Property");
    spaces[24]->setPropertyCost(240);
    spaces[24]->setFreeParking(0);
    spaces[24]->setOccupied(false);
    spaces[24]->setOwnership(100);
    spaces[24]->setMortgaged(false);
    spaces[24]->setRent(200);
    spaces[24]->setTax(0);
    spaces[24]->setActionText("$240");
    spaces[24]->setXcoordinate(330);
    spaces[24]->setYcoordinate(40);

    //Space 25
    spaces[25]->setName("Fenchurch St-> Station");
    spaces[25]->setType("RailRoad");
    spaces[25]->setPropertyCost(200);
    spaces[25]->setFreeParking(0);
    spaces[25]->setOccupied(false);
    spaces[25]->setOwnership(100);
    spaces[25]->setMortgaged(false);
    spaces[25]->setRent(250);
    spaces[25]->setTax(0);
    spaces[25]->setActionText("$200");
    spaces[25]->setXcoordinate(390);
    spaces[25]->setYcoordinate(40);

    //Space 26
    spaces[26]->setName("Leicester Square");
    spaces[26]->setType("Property");
    spaces[26]->setPropertyCost(260);
    spaces[26]->setFreeParking(0);
    spaces[26]->setOccupied(false);
    spaces[26]->setOwnership(100);
    spaces[26]->setMortgaged(false);
    spaces[26]->setRent(220);
    spaces[26]->setTax(0);
    spaces[26]->setActionText("$260");
    spaces[26]->setXcoordinate(450);
    spaces[26]->setYcoordinate(40);

    //Space 27
    spaces[27]->setName("Covenry Street");
    spaces[27]->setType("Property");
    spaces[27]->setPropertyCost(260);
    spaces[27]->setFreeParking(0);
    spaces[27]->setOccupied(false);
    spaces[27]->setOwnership(100);
    spaces[27]->setMortgaged(false);
    spaces[27]->setRent(220);
    spaces[27]->setTax(0);
    spaces[27]->setActionText("$260");
    spaces[27]->setXcoordinate(510);
    spaces[27]->setYcoordinate(40);

    //Space 28
    spaces[28]->setName("Water Works");
    spaces[28]->setType("Utility");
    spaces[28]->setPropertyCost(150);
    spaces[28]->setFreeParking(0);
    spaces[28]->setOccupied(false);
    spaces[28]->setOwnership(100);
    spaces[28]->setMortgaged(false);
    spaces[28]->setRent(100);
    spaces[28]->setTax(0);
    spaces[28]->setActionText("$150");
    spaces[28]->setXcoordinate(580);
    spaces[28]->setYcoordinate(40);

    //Space 29
    spaces[29]->setName("Piccadilly");
    spaces[29]->setType("Property");
    spaces[29]->setPropertyCost(280);
    spaces[29]->setFreeParking(0);
    spaces[29]->setOccupied(false);
    spaces[29]->setOwnership(100);
    spaces[29]->setMortgaged(false);
    spaces[29]->setRent(220);
    spaces[29]->setTax(0);
    spaces[29]->setActionText("280");
    spaces[29]->setXcoordinate(640);
    spaces[29]->setYcoordinate(40);

    //Space 30
    spaces[30]->setName("Go to Jail!");
    spaces[30]->setType("GoJail");
    spaces[30]->setPropertyCost(0);
    spaces[30]->setFreeParking(0);
    spaces[30]->setOccupied(false);
    spaces[30]->setOwnership(100);
    spaces[30]->setMortgaged(false);
    spaces[30]->setRent(0);
    spaces[30]->setTax(0);
    spaces[30]->setActionText(" ");
    spaces[30]->setXcoordinate(730);
    spaces[30]->setYcoordinate(40);

    //Space 31
    spaces[31]->setName("Regent Street");
    spaces[31]->setType("Property");
    spaces[31]->setPropertyCost(300);
    spaces[31]->setFreeParking(0);
    spaces[31]->setOccupied(false);
    spaces[31]->setOwnership(100);
    spaces[31]->setMortgaged(false);
    spaces[31]->setRent(260);
    spaces[31]->setTax(0);
    spaces[31]->setActionText("$300");
    spaces[31]->setXcoordinate(730);
    spaces[31]->setYcoordinate(120);

    //Space 32
    spaces[32]->setName("Oxford Street");
    spaces[32]->setType("Property");
    spaces[32]->setPropertyCost(300);
    spaces[32]->setFreeParking(0);
    spaces[32]->setOccupied(false);
    spaces[32]->setOwnership(100);
    spaces[32]->setMortgaged(false);
    spaces[32]->setRent(260);
    spaces[32]->setTax(0);
    spaces[32]->setActionText("$300");
    spaces[32]->setXcoordinate(730);
    spaces[32]->setYcoordinate(180);

    //Space 33
    spaces[33]->setName("Community Chest");
    spaces[33]->setType("Community Chest");
    spaces[33]->setPropertyCost(0);
    spaces[33]->setFreeParking(0);
    spaces[33]->setOccupied(false);
    spaces[33]->setOwnership(100);
    spaces[33]->setMortgaged(false);
    spaces[33]->setRent(0);
    spaces[33]->setTax(0);
    spaces[33]->setActionText("Draw a card");
    spaces[33]->setXcoordinate(730);
    spaces[33]->setYcoordinate(230);

    //Space 34
    spaces[34]->setName("Bond Street");
    spaces[34]->setType("Property");
    spaces[34]->setPropertyCost(320);
    spaces[34]->setFreeParking(0);
    spaces[34]->setOccupied(false);
    spaces[34]->setOwnership(100);
    spaces[34]->setMortgaged(false);
    spaces[34]->setRent(280);
    spaces[34]->setTax(0);
    spaces[34]->setActionText("$320");
    spaces[34]->setXcoordinate(730);
    spaces[34]->setYcoordinate(280);

    //Space 35
    spaces[35]->setName("Liverpool St-> Station");
    spaces[35]->setType("RailRoad");
    spaces[35]->setPropertyCost(200);
    spaces[35]->setFreeParking(0);
    spaces[35]->setOccupied(false);
    spaces[35]->setOwnership(100);
    spaces[35]->setMortgaged(false);
    spaces[35]->setRent(250);
    spaces[35]->setTax(0);
    spaces[35]->setActionText("$200");
    spaces[35]->setXcoordinate(730);
    spaces[35]->setYcoordinate(340);

    //Space 36
    spaces[36]->setName("Chance");
    spaces[36]->setType("Chance");
    spaces[36]->setPropertyCost(0);
    spaces[36]->setFreeParking(0);
    spaces[36]->setOccupied(false);
    spaces[36]->setOwnership(100);
    spaces[36]->setMortgaged(false);
    spaces[36]->setRent(0);
    spaces[36]->setTax(0);
    spaces[36]->setActionText("Draw a Card");
    spaces[36]->setXcoordinate(730);
    spaces[36]->setYcoordinate(390);

    //Space 37
    spaces[37]->setName("Park Lane");
    spaces[37]->setType("Property");
    spaces[37]->setPropertyCost(350);
    spaces[37]->setFreeParking(0);
    spaces[37]->setOccupied(false);
    spaces[37]->setOwnership(100);
    spaces[37]->setMortgaged(false);
    spaces[37]->setRent(350);
    spaces[37]->setTax(0);
    spaces[37]->setActionText("$350");
    spaces[37]->setXcoordinate(730);
    spaces[37]->setYcoordinate(450);

    //Space 38
    spaces[38]->setName("Super Tax");
    spaces[38]->setType("Tax");
    spaces[38]->setPropertyCost(0);
    spaces[38]->setFreeParking(0);
    spaces[38]->setOccupied(false);
    spaces[38]->setOwnership(100);
    spaces[38]->setMortgaged(false);
    spaces[38]->setRent(100);
    spaces[38]->setTax(100);
    spaces[38]->setActionText("Pay $100");
    spaces[38]->setXcoordinate(730);
    spaces[38]->setYcoordinate(500);

    //Space 39
    spaces[39]->setName("Mayfair");
    spaces[39]->setType("Property");
    spaces[39]->setPropertyCost(400);
    spaces[39]->setFreeParking(0);
    spaces[39]->setOccupied(false);
    spaces[39]->setOwnership(100);
    spaces[39]->setMortgaged(false);
    spaces[39]->setRent(400);
    spaces[39]->setTax(0);
    spaces[39]->setActionText("$400");
    spaces[39]->setXcoordinate(730);
    spaces[39]->setYcoordinate(560);

    for(int i = 0; i < 40; i++){
        spaces[i]->setHouses(0);
    }

    CommunityChest = new Card*[14];

    for( int i = 0; i < 14; i++) {
        CommunityChest[i] = new Card;
    }

    //Community Chest 0
    CommunityChest[0]->setText("COMMUNITY CHEST: Here is a free $200");
    CommunityChest[0]->setAmount(200);

    //Community Chest 1
    CommunityChest[1]->setText("COMMUNITY CHEST: Bank error in your favor – collect $75");
    CommunityChest[1]->setAmount(75);

    //Community Chest 2
    CommunityChest[2]->setText("COMMUNITY CHEST: Doctor's fee – Pay $50");
    CommunityChest[2]->setAmount(-50);

    //Community Chest 3
    CommunityChest[3]->setText("COMMUNITY CHEST: From sale of stock you get $50");
    CommunityChest[3]->setAmount(50);

    //Community Chest 4
    CommunityChest[4]->setText("COMMUNITY CHEST: Get out of jail free – this card may be kept until needed, or sold");
    CommunityChest[4]->setAmount(0);

    //Community Chest 5
    CommunityChest[5]->setText("COMMUNITY CHEST: Go to Jail – Go directly to jail – Do not pass Go – Do not collect $200");
    CommunityChest[5]->setAmount(0);

    //Community Chest 6
    CommunityChest[6]->setText("COMMUNITY CHEST: Holiday Fund matures - Collect $100");
    CommunityChest[6]->setAmount(100);

    //Community Chest 7
    CommunityChest[7]->setText("COMMUNITY CHEST: Income tax refund – Collect $20");
    CommunityChest[7]->setAmount(20);

    //Community Chest 8
    CommunityChest[8]->setText("COMMUNITY CHEST: Life insurance matures – Collect $100");
    CommunityChest[8]->setAmount(100);

    //Community Chest 9
    CommunityChest[9]->setText("COMMUNITY CHEST: Pay hospital fees of $100");
    CommunityChest[9]->setAmount(-100);

    //Community Chest 10
    CommunityChest[10]->setText("COMMUNITY CHEST: Pay school fees of $150");
    CommunityChest[10]->setAmount(-150);

    //Community Chest 11
    CommunityChest[11]->setText("COMMUNITY CHEST: Receive $25 consultancy fee");
    CommunityChest[11]->setAmount(25);

    //Community Chest 12
    CommunityChest[12]->setText("COMMUNITY CHEST:You have won second prize in a beauty contest – Collect $10");
    CommunityChest[12]->setAmount(10);

    //Community Chest 13
    CommunityChest[13]->setText("COMMUNITY CHEST: You inherit $100");
    CommunityChest[13]->setAmount(100);


    //-------START OF CHANCE CARD INITIALIZATION-------

    Chance = new Card*[14];

    for( int i = 0; i < 14; i++) {
        Chance[i] = new Card;
    }

    //Chance 0
    Chance[0]->setText("CHANCE: Here is a free $200");
    Chance[0]->setAmount(200);

    //Chance 0
    Chance[0]->setText("CHANCE: Here is a free $200");
    Chance[0]->setAmount(200);

    //Chance 1
    Chance[1]->setText("CHANCE: Bank pays you dividend of $50");
    Chance[1]->setAmount(50);

    //Chance 2
    Chance[2]->setText("CHANCE: Pay poor tax of $15");
    Chance[2]->setAmount(-15);

    //Chance 3
    Chance[3]->setText("CHANCE: Your building and loan matures – Collect $150");
    Chance[3]->setAmount(150);

    //Chance 4
    Chance[4]->setText("CHANCE: Get out of jail free – this card may be kept until needed, or sold");
    Chance[4]->setAmount(0);

    //Chance 5
    Chance[5]->setText("CHANCE: Go to Jail – Go directly to jail – Do not pass Go – Do not collect $200");
    Chance[5]->setAmount(0);

    //Chance 6
    Chance[6]->setText("CHANCE: You have won a crossword competition -  Collect $100");
    Chance[6]->setAmount(100);

    //Chance 7
    Chance[7]->setText("CHANCE: Holiday Fund matures - Collect $100");
    Chance[7]->setAmount(100);

    //Chance 8
    Chance[8]->setText("CHANCE: Life insurance matures – Collect $100");
    Chance[8]->setAmount(100);

    //Chance 9
    Chance[9]->setText("CHANCE: Pay hospital fees of $100");
    Chance[9]->setAmount(-100);

    //Chance 10
    Chance[10]->setText("CHANCE: Pay school fees of $150");
    Chance[10]->setAmount(-150);

    //Chance 11
    Chance[11]->setText("CHANCE: Receive $25 consultancy fee");
    Chance[11]->setAmount(25);

    //Chance 12
    Chance[12]->setText("CHANCE:You have won second prize in a beauty contest – Collect $10");
    Chance[12]->setAmount(10);

    //Chance 13
    Chance[13]->setText("CHANCE: You inherit $100");
    Chance[13]->setAmount(100);



    //Display the board
    QPixmap board(":/board.jpg");
    ui->label->setPixmap(board.scaled(551,551,Qt::KeepAspectRatio));

    //Display Piece 1
    QPixmap piece1(":/piece1.png");
    ui->label_3->setPixmap(piece1.scaled(100,100, Qt::KeepAspectRatio));

    //Display Piece 2
    QPixmap piece2(":/piece2.png");
    ui->label_4->setPixmap(piece2.scaled(100,100, Qt::KeepAspectRatio));


    //Display ScoreBoard
    ui->Player1_Space->setText(QString::number(players[0]->getPosition()) + "- " + QString::fromStdString(spaces[players[0]->getPosition()]->getName()));
    ui->Player1_Bank_Amount->setText("$" + QString::number(players[0]->getBank()));
    ui->Player1_Jailfree_amount->setText(QString::number(players[0]->getJailFree()));

    ui->Player2_Space->setText(QString::number(players[1]->getPosition()) + "- " +QString::fromStdString(spaces[players[1]->getPosition()]->getName()));
    ui->Player2_Bank_Amount->setText("$" + QString::number(players[1]->getBank()));
    ui->Player2_Jailfree_amount->setText(QString::number(players[1]->getJailFree()));

    //Quit Button
    connect(ui->pushButton, SIGNAL (clicked()), QApplication::instance(), SLOT(quit()));
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    //initializes the roll values to zero
    int roll1 = 0;
    int roll2 = 0;
    int totalRoll =0;

    //Asks the player if they want to use their get out of jail free card
    if (players[turnNumber]->getJailStatus() == true && players[turnNumber]->getJailFree() > 0){
        QMessageBox JailFreeCheck;
        JailFreeCheck.setWindowTitle("Monopoly: You are in Jail");
        JailFreeCheck.setText("Would you like to use your 'Get out of Jail Free' card?");
        JailFreeCheck.setStandardButtons(QMessageBox::Yes);
        JailFreeCheck.addButton(QMessageBox::No);
        JailFreeCheck.setDefaultButton(QMessageBox::No);
        if(JailFreeCheck.exec() == QMessageBox::Yes){
            QMessageBox::information(this, tr("Monopoly"),tr("You have been Freed!") );
            players[turnNumber]->subJailFree();
            players[turnNumber]->setJail(false);
        }else {
            QMessageBox::information(this, tr("Monopoly"),tr("You have declined to use your 'Get out of Jail Free' card."));
        }
    }



    //Rolls Dice and Moves The Player
    dieRoll(roll1, roll2, totalRoll);

    //Checks if player is in jail and needs doubles on the roll
    if (players[turnNumber]->getJailStatus() == true){
        if (roll1 == roll2){
            QMessageBox::information(this, tr("Monopoly"),tr("You rolled a double!"));
            players[turnNumber]->setJail(false);
            players[turnNumber]->movePlayer(totalRoll);
        }
        else {
            QMessageBox::information(this, tr("Monopoly"),tr("You failed to roll a double, you are stuck in jail."));
            players[turnNumber]->movePlayer(0);
        }
    }
    else{
    players[turnNumber]->movePlayer(totalRoll);
    }

    //Displays the TotalRoll value so the player can see what they rolled
    ui->DiceRoll->setText("Your Roll: " + QString::number(totalRoll));




    //move players piece on board
    if (turnNumber == 0) //Adjust Player one's position
        ui->label_3->move(spaces[players[0]->getPosition()]->getX() , spaces[players[0]->getPosition()]->getY());

    if (turnNumber == 1) //Adjust Player Two's position
        ui->label_4->move(spaces[players[1]->getPosition()]->getX(), spaces[players[1]->getPosition()]->getY());


    //Loops Player Back Around the Board and Pays them $200 as they pass go
    if(players[turnNumber]->getPosition()>40){
        players[turnNumber]->setPosition(players[turnNumber]->getPosition()-40);
        players[turnNumber]->setBank(players[turnNumber]->getBank()+200);
    }


    string typeOfSpace = spaces[players[turnNumber]->getPosition()]->getSpaceType();
    int Ownership = spaces[players[turnNumber]->getPosition()]->getOwnership();
    string Name = spaces[players[turnNumber]->getPosition()]->getName();
    int PropertyCost = spaces[players[turnNumber]->getPosition()]->getPrice();
    int Rent = spaces[players[turnNumber]->getPosition()]->getRent();
    int PlayerOwner = players[turnNumber]->getUserID();

    ui->label_2->setText(QString::fromStdString(typeOfSpace));


    //Checks to See if the Spot is a Chance Location
    if(typeOfSpace == "Chance"){
        int tempBank = players[turnNumber]->getBank(); //Gets the Value of the Players Bank so they can get paid or pay their dues
        int randFourteen = randomCard(); //Random Card Drawn

        //This pays to deducts money from player
        players[turnNumber]->setBank(tempBank + Chance[randFourteen]->getAmount());

        //Checks to see if a Get out of jail free card or a go to jail card
        /*if (Chance[randFourteen]->getText() == "CHANCE: Get out of jail free – this card may be kept until needed, or sold"){
            players[turnNumber]->addJailFree();
        }
        else if (Chance[randFourteen]->getText() == "CHANCE: Go to Jail – Go directly to jail – Do not pass Go – Do not collect $200"){
             players[turnNumber]->setJail(true);
             players[turnNumber]->setPosition(10);
        }*/
        if(randFourteen == 4){
            players[turnNumber]->addJailFree();
        }
        else if(randFourteen == 5){
             players[turnNumber]->setJail(true);
             players[turnNumber]->setPosition(10);
             ui->label_3->move(spaces[players[0]->getPosition()]->getX() , spaces[players[0]->getPosition()]->getY());
             ui->label_4->move(spaces[players[1]->getPosition()]->getX(), spaces[players[1]->getPosition()]->getY());
        }

        //Displays Message Box With What Card You Drew
        QMessageBox::information(this, "Draw A Chance Card", "You Drew the Card: " + QString::fromStdString(Chance[randFourteen]->getText()));
    }


    //Checks to See if the Spot is a Community Chest Location
    if(typeOfSpace == "Community Chest"){
        int tempBank = players[turnNumber]->getBank(); //Gets the Value of the Players Bank so they can get paid or pay their dues
        int randFourteen = randomCard(); //Random Card Drawn
        players[turnNumber]->setBank(tempBank + CommunityChest[randFourteen]->getAmount());

        //Checks to see if a Get out of jail free card or a go to jail card
        /*if (Chance[randFourteen]->getText() == "COMMUNITY CHEST: Get out of jail free – this card may be kept until needed, or sold"){
            players[turnNumber]->addJailFree();
        }
        else if (Chance[randFourteen]->getText() == "COMMUNITY CHEST: Go to Jail – Go directly to jail – Do not pass Go – Do not collect $200"){
             players[turnNumber]->setJail(true);
             players[turnNumber]->setPosition(10);
        }*/
        if(randFourteen == 4){
            players[turnNumber]->addJailFree();

        }
        else if(randFourteen == 5){
             players[turnNumber]->setJail(true);
             players[turnNumber]->setPosition(10);
             ui->label_3->move(spaces[players[0]->getPosition()]->getX() , spaces[players[0]->getPosition()]->getY());
             ui->label_4->move(spaces[players[1]->getPosition()]->getX(), spaces[players[1]->getPosition()]->getY());
        }

        //Displays Message Box With What Card You Drew
        QMessageBox::information(this, "Draw A Community Chest Card", "You Drew the Card: " + QString::fromStdString(CommunityChest[randFourteen]->getText()));
    }

    //Buying Property, paying rent, etc.
    if (typeOfSpace == "Property"  ||typeOfSpace ==  "Utility" || typeOfSpace == "RailRoad"){
        if (spaces[players[turnNumber]->getPosition()]->getOwnership() == 100) {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Buying Property", "Would you like to purchase "+QString::fromStdString(spaces[players[turnNumber]->getPosition()]->getName()), QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                qDebug() << "You have purchased "+QString::fromStdString(spaces[players[turnNumber]->getPosition()]->getName());
                int tempBank = players[turnNumber]->getBank(); //Gets the Value of the Players Bank so they can get paid or pay their dues>
                //This pays to deducts money from player
                players[turnNumber]->setBank(tempBank - PropertyCost);
                spaces[players[turnNumber]->getPosition()]->setOwnership(PlayerOwner);
                players[turnNumber]->setOwned(players[turnNumber]->getPosition());
                //QApplication::quit();
            }
            else {
                qDebug() << "You have declined to purchase "+QString::fromStdString(spaces[players[turnNumber]->getPosition()]->getName());
                //QApplication::quit();
            }
        }
        else if (Ownership != 100 || Ownership != turnNumber+1) {
            QMessageBox::information(this, "Pay Rent", "You landed on owned property. Pay $" + QString::number(Rent) + " to the Owner");
            int tempBankPayer = players[turnNumber]->getBank();
            players[turnNumber]->setBank(tempBankPayer - Rent);

            if(turnNumber  == 0){
                   int tempBankReceiver = players[1]->getBank();
                   players[1]->setBank(tempBankReceiver + Rent);
                   ui->Player2_Bank_Amount->setText("$" + QString::number(players[1]->getBank()));
            }
            if(turnNumber  == 1){
                   int tempBankReceiver = players[0]->getBank();
                   players[0]->setBank(tempBankReceiver + Rent);
                   ui->Player1_Bank_Amount->setText("$" + QString::number(players[0]->getBank()));
            }


        }
    }

    //Checks for monopolies and adjusts rent
    if ((spaces[1]->getOwnership() !=100) &&  (spaces[3]->getOwnership() != 100)) {
        if (spaces[1]->getOwnership() ==  spaces[3]->getOwnership()) {
            int temprent1 = spaces[1]->getRent();
            int temprent2 = spaces[3]->getRent();
            spaces[1]->setRent(temprent1*2);
            spaces[3]->setRent(temprent2*2);
            spaces[1]->setOwnership(4);
            spaces[3]->setOwnership(5);
        }
    }
    if ((spaces[6]->getOwnership() !=100) &&  (spaces[8]->getOwnership() != 100) && (spaces[9]->getOwnership() !=100)) {
        if (spaces[6]->getOwnership() ==  spaces[8]->getOwnership() == spaces[9]->getOwnership()) {
            int temprent1 = spaces[6]->getRent();
            int temprent2 = spaces[8]->getRent();
            int temprent3 = spaces[9]->getRent();
            spaces[6]->setRent(temprent1*3);
            spaces[8]->setRent(temprent2*3);
            spaces[9]->setRent(temprent3*3);
            spaces[6]->setOwnership(4);
            spaces[8]->setOwnership(5);
            spaces[9]->setOwnership(6);
        }
    }
    if ((spaces[11]->getOwnership() !=100) &&  (spaces[13]->getOwnership() != 100) && (spaces[14]->getOwnership() !=100)) {
        if (spaces[11]->getOwnership() ==  spaces[13]->getOwnership() == spaces[14]->getOwnership()) {
            int temprent1 = spaces[11]->getRent();
            int temprent2 = spaces[13]->getRent();
            int temprent3 = spaces[14]->getRent();
            spaces[11]->setRent(temprent1*3);
            spaces[13]->setRent(temprent2*3);
            spaces[14]->setRent(temprent3*3);
            spaces[11]->setOwnership(4);
            spaces[13]->setOwnership(5);
            spaces[14]->setOwnership(6);
        }
    }
    if ((spaces[16]->getOwnership() !=100) &&  (spaces[18]->getOwnership() != 100) && (spaces[19]->getOwnership() !=100)) {
        if (spaces[16]->getOwnership() ==  spaces[18]->getOwnership() == spaces[19]->getOwnership()) {
            int temprent1 = spaces[16]->getRent();
            int temprent2 = spaces[18]->getRent();
            int temprent3 = spaces[19]->getRent();
            spaces[16]->setRent(temprent1*3);
            spaces[18]->setRent(temprent2*3);
            spaces[19]->setRent(temprent3*3);
            spaces[16]->setOwnership(4);
            spaces[18]->setOwnership(5);
            spaces[19]->setOwnership(6);
        }
    }
    if ((spaces[21]->getOwnership() !=100) &&  (spaces[23]->getOwnership() != 100) && (spaces[24]->getOwnership() !=100)) {
        if (spaces[21]->getOwnership() ==  spaces[23]->getOwnership() == spaces[24]->getOwnership()) {
            int temprent1 = spaces[21]->getRent();
            int temprent2 = spaces[23]->getRent();
            int temprent3 = spaces[24]->getRent();
            spaces[21]->setRent(temprent1*3);
            spaces[23]->setRent(temprent2*3);
            spaces[24]->setRent(temprent3*3);
            spaces[21]->setOwnership(4);
            spaces[23]->setOwnership(5);
            spaces[24]->setOwnership(6);
        }
    }
    if ((spaces[26]->getOwnership() !=100) &&  (spaces[27]->getOwnership() != 100) && (spaces[29]->getOwnership() !=100)) {
        if (spaces[26]->getOwnership() ==  spaces[27]->getOwnership() == spaces[29]->getOwnership()) {
            int temprent1 = spaces[26]->getRent();
            int temprent2 = spaces[27]->getRent();
            int temprent3 = spaces[29]->getRent();
            spaces[26]->setRent(temprent1*3);
            spaces[27]->setRent(temprent2*3);
            spaces[29]->setRent(temprent3*3);
            spaces[26]->setOwnership(4);
            spaces[27]->setOwnership(5);
            spaces[29]->setOwnership(6);
        }
    }
    if ((spaces[31]->getOwnership() !=100) &&  (spaces[32]->getOwnership() != 100) && (spaces[34]->getOwnership() !=100)) {
        if (spaces[31]->getOwnership() ==  spaces[32]->getOwnership() == spaces[34]->getOwnership()) {
            int temprent1 = spaces[31]->getRent();
            int temprent2 = spaces[32]->getRent();
            int temprent3 = spaces[34]->getRent();
            spaces[31]->setRent(temprent1*3);
            spaces[32]->setRent(temprent2*3);
            spaces[34]->setRent(temprent3*3);
            spaces[31]->setOwnership(4);
            spaces[32]->setOwnership(5);
            spaces[34]->setOwnership(6);
        }
    }
    if ((spaces[37]->getOwnership() !=100) &&  (spaces[39]->getOwnership() != 100)) {
        if (spaces[37]->getOwnership() ==  spaces[39]->getOwnership()) {
            int temprent1 = spaces[37]->getRent();
            int temprent2 = spaces[39]->getRent();
            spaces[37]->setRent(temprent1*2);
            spaces[39]->setRent(temprent2*2);
            spaces[37]->setOwnership(4);
            spaces[39]->setOwnership(5);
        }
    }

    //Checks to See if the player is on the go directly to jail space
    if(typeOfSpace == "GoJail"){
            QMessageBox::information(this, "Go to Jail", "Go directly to Jail. Do not Pass Go or Collect $200");
            players[turnNumber]->setJail(true);
            players[turnNumber]->setPosition(10);
            ui->label_3->move(spaces[players[0]->getPosition()]->getX() , spaces[players[0]->getPosition()]->getY());
            ui->label_4->move(spaces[players[1]->getPosition()]->getX(), spaces[players[1]->getPosition()]->getY());
    }

    if(typeOfSpace == "Tax"){
        QMessageBox::information(this, "Pay Tax", "You landed on a Tax Space. Pay $" + QString::number(Rent) + " In Tax");
        int tempBank = players[turnNumber]->getBank();
        players[turnNumber]->setBank(tempBank - Rent);
    }

    int currentUserID = players[turnNumber]->getUserID();

    //Switch Turns
    if(currentUserID == 1){

        //Updates ScoreBoard
        ui->Player1_Space->setText(QString::number(players[0]->getPosition()) + "- " + QString::fromStdString(spaces[players[0]->getPosition()]->getName()));
        ui->Player1_Bank_Amount->setText("$" + QString::number(players[0]->getBank()));
        ui->Player1_Jailfree_amount->setText(QString::number(players[0]->getJailFree()));
        if (players[0]->getJailStatus() == true)
            ui->Player1_inJail->setText("Yes");
        else{
            ui->Player1_inJail->setText("No");
        }
        if(players[0]->getBank() < 0){
            QMessageBox::information(this, "Player 2 WINS", "Player 1's Bank account has been overdrawn. Player 2 Wins the game!!!!!!");
            QApplication::quit();
        }
        if(players[1]->getBank() < 0){
            QMessageBox::information(this, "Player 1 WINS", "Player 2's Bank account has been overdrawn. Player 1 Wins the game!!!!!!");
            QApplication::quit();
        }

        //ui->Player1_inJail->setText(QString::number(players[0]->getJailStatus()));
        turnNumber = 1;
        ui->TurnLabel->setText("Player 2's Turn");
        numberOfTurns = numberOfTurns +1;
        ui->TotalTurns->setText("Total Number of Turns: " + QString::number(numberOfTurns));
    }

    if(currentUserID == 2){

        //Updates ScoreBoard
        ui->Player2_Space->setText(QString::number(players[1]->getPosition()) + "- " +QString::fromStdString(spaces[players[1]->getPosition()]->getName()));
        ui->Player2_Bank_Amount->setText("$" + QString::number(players[1]->getBank()));
        ui->Player2_Jailfree_amount->setText(QString::number(players[1]->getJailFree()));
        if (players[1]->getJailStatus() == true)
            ui->Player2_inJail->setText("Yes");
        else{
            ui->Player2_inJail->setText("No");
        }
        if(players[0]->getBank() < 0){
            QMessageBox::information(this, "Player 2 WINS", "Player 1's Bank account has been overdrawn. Player 1 Wins the game!!!!!!");
            QApplication::quit();
        }
        if(players[1]->getBank() < 0){
            QMessageBox::information(this, "Player 1 WINS", "Player 2's Bank account has been overdrawn. Player 1 Wins the game!!!!!!");
            QApplication::quit();
        }

        //ui->Player2_inJail->setText(QString::number(players[1]->getJailStatus()));
        turnNumber = 0;
        ui->TurnLabel->setText("Player 1's Turn");
        numberOfTurns = numberOfTurns +1;
        ui->TotalTurns->setText("Total Number of Turns: " + QString::number(numberOfTurns));
    }


}
/*
void MainWindow::on_pushButton_3_clicked(){
    players[turnNumber]->setJail(true);

}
void MainWindow::on_pushButton_4_clicked(){
    players[turnNumber]->addJailFree();
    }
*/
