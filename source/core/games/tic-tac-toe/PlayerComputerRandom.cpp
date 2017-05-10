#include "games/tic-tac-toe/PlayerComputerRandom.h"

void PlayerComputerRandom::takeAction(Board* board){
    int x, y;
    do{
        x = std::rand() % board->getBoardSize();
        y = std::rand() % board->getBoardSize();
    }while(!board->updateSymbol(x,y,this->symbol));
}