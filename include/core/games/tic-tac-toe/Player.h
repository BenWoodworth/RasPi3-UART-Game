#ifndef PLAYER_H_
#define PLAYER_H_

#include "games/tic-tac-toe/Board.h"

enum class PlayerType { HUMAN, COMPUTER };

class Player{

private:
    PlayerType playerType;
    std::string name;
    Symbol symbol;
public:
    Player(PlayerType pType, std::string pName, Symbol sym){
        playerType = pType;
        name = pName;
        symbol = sym;
    }

    inline PlayerType getPlayerType(){
        return playerType;
    }

    inline std::string getName(){
        return name;
    }

    inline Symbol getSymbol(){
        return symbol;
    }

    inline std::string getSymbolStr(){
        if(symbol == Symbol::X){
            return "X";
        } else if(symbol == Symbol::O){
            return "O";
        } else {
            return " ";
        }
    }

    /// Preform an action on the board
    void takeAction(Board* board);
};

#endif
