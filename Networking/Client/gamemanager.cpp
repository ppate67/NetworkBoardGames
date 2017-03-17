#include "gamemanager.h"
GameManager* GameManager::head=nullptr;
int GameManager::clientID=0;
bool GameManager::hasPlayerID=false;
std::vector<std::vector<std::vector<int>>> GameManager:: games;
GameManager::GameManager()
{

}
void GameManager::removePlayer(GameManager *player,GameManager*game){
    if(head==nullptr){
        //no games or players exist or massive error has happened
    }
    else{
        GameManager* temp=head;
        while(temp->nextGame!=nullptr){
            if(temp==game){
                while(temp!=nullptr){
                    if(temp->nextPlayer==player){
                        temp->nextPlayer=player->nextPlayer;
                        if(temp->nextPlayer==nullptr && temp->nextGame!=nullptr){
                            temp->nextGame=player->nextGame;
                        }
                        break;
                    }
                    temp=temp->nextPlayer;
                }
                break;
            }
            temp=temp->nextGame;
        }
    }
}
void GameManager::addPlayer(GameManager *game, GameManager *&player){
    if(GameManager::head==nullptr){
        GameManager::head=game;
        game->nextGame=nullptr;
        game->nextPlayer=nullptr;
        player=game;
    }
    else{
        GameManager* temp=head;
        while(temp->nextGame!=nullptr){
            if(temp==game){
                while(temp!=nullptr){
                    if(temp->nextPlayer==nullptr){
                        temp->nextPlayer=player;
                        player->nextPlayer=nullptr;
                        player->nextGame=nullptr;

                        break;
                    }
                    temp=temp->nextPlayer;
                }
                break;
            }
            temp=temp->nextGame;
        }
        temp->nextGame=player;
        player->nextGame=nullptr;
        player->nextPlayer=nullptr;
    }
}
GameManager* GameManager::findGame1(int playerid){//returns player's manager pointer
    GameManager* temp=head;
    while(temp!=nullptr){
        GameManager *temp2=temp;
        while(temp=nullptr){
            if(temp->playerid==playerid){
                return temp;
            }
            temp=temp->nextPlayer;
        }
        temp=temp2;
        temp=temp->nextGame;
    }
    return nullptr;
}
GameManager* GameManager::findGame2(int gType){
    GameManager* temp=head;
    while(temp!=nullptr){
        if(temp->gameType==gType){
            return temp;
        }
        temp=temp->nextGame;
    }
    return nullptr;
}
GameManager* GameManager::findGame3(int gID){
    GameManager* temp=head;
    while(temp!=nullptr){
        if(temp->gameID==gID){
            return temp;
        }
        temp=temp->nextGame;
    }
    return nullptr;
}
