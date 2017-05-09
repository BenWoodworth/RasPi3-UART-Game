#ifndef GAMESTATESNAKE_H_
#define GAMESTATESNAKE_H_

#include "core/gameapi/GameState.h"

class GameStateSnake : public GameState {
private:
    // TODO: Fill in
    GameManager* gameManager;
public:
    GameStateSnake() {
        // TODO: Fill in
    }

    void tick(GameManager* gameManager);

    void handleInput(Key key);
};

#endif
