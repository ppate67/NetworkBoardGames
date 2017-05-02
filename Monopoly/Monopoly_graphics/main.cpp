#include <iostream>
#include <cstdlib>
#include "mainwindow.h"
#include <QApplication>
#include "boardspace.h"
#include "cards.h"
#include "player.h"

using namespace std;


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



    w.show();



    return a.exec();
}
