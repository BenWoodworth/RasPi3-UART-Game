#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "core/gameapi/GameManager.h"
#include "core/terminal/Key.h"

class GameManager; // Forward declare for circular dependency

class GameState {
public:
    /// Perform a game tick.
    virtual void tick(GameManager* gameManager) = 0;

    /// Handle user input from the terminal
    virtual void handleInput(Key key) = 0;
};

#endif
