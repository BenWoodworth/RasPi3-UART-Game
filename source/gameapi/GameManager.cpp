#include "gameapi/GameManager.h"

void GameManager::start(GameState* startState) {
    setState(startState);

    // Clear screen first
    this->terminal->clear();

    // Hide cursor and clear screen
    this->terminal->setCursorVisibility(false);
    this->terminal->clear();

    bool firstLoop = true;

    // Main game loop
    while (this->gameState != NULL) {
        this->timer->start();

        // Update output image
        if (firstLoop) {
            firstLoop = false;
        } else {
            this->terminal->moveCursor(
                -this->getOutputImage()->getHeight(), 0
            );
        }
        this->drawOutputImage();
        
        // Execute game tick
        this->gameState->tick(this);
 
        // Consume unused key presses
        while (this->terminal->hasChar()) {
            this->gameState->handleInput(this->terminal->getChar());
        }

        // Wait for tick to elapse
        this->timer->waitMilli(this->tickDuration);
    }

    this->drawOutputImage();
    this->terminal->resetStyling();
}

void GameManager::drawOutputImage() {
    this->getOutputImage()->writeToTerminal(this->terminal);
}
