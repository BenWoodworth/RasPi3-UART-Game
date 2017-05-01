#ifndef GAMESTATETICTACTOE_H_
#define GAMESTATETICTACTOW_H_

#include "gameapi/GameState.h"

class GameStateTicTacToe : public GameState {
private:
    // TODO: Fill in
    GameManager* gameManager;
public:
    GameStateTicTacToe() {
        // TODO: Fill in
    }

    void tick(GameManager* gameManager);

    void handleInput(char input);
};

#endif
