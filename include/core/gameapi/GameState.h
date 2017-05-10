#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "gameapi/GameManager.h"
#include "terminal/Key.h"

class GameManager; // Forward declare for circular dependency

enum class Direction { UP,DOWN,LEFT,RIGHT };

class GameState {
public:
    /// Perform a game tick.
    virtual void tick(GameManager* gameManager) = 0;

    /// Handle user input from the terminal
    virtual void handleInput(Key key) = 0;
};

#endif
