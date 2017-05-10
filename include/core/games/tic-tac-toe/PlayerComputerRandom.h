#ifndef PLAYERCOMPUTERRANDOM_H_
#define PLAYERCOMPUTERRANDOM_H_

#include "games/tic-tac-toe/Player.h"

class PlayerComputerRandom : public Player{
    
private:
    PlayerType playerType;
    std::string name;
    Symbol symbol;
public:
    PlayerComputerRandom(PlayerType pType, std::string pName, Symbol sym) : 
        Player(pType, pName, sym)
    {
        playerType = pType;
        name = pName;
        symbol = sym;
    }

    /// Preform an action on the board
    void takeAction(Board* board);

};


#endif
