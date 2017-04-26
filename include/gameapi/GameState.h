#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "gameapi/GameManager.h"

class GameState {
public:
    /// Perform a game tick.
    virtual void tick(GameManager* gameManager) = 0;
};

#endif
