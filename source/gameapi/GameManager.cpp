#include "gameapi/GameManager.h"

void GameManager::start(GameState* startState) {
    setState(startState);

    // Hide cursor and clear screen
    this->terminal->setCursorVisibility(false);
    this->terminal->clear();

    // Main game loop
    while (this->gameState != NULL) {
        this->timer->start();

        // Update output image
        this->terminal->saveCursorPos();
        this->drawOutputImage();
        this->terminal->restoreCursorPos();
        
        // Execute game tick
        this->gameState->tick(this);

        // Wait for tick to elapse
        this->timer->waitMilli(this->tickDuration);
    }

    this->drawOutputImage();
    this->terminal->resetStyling();
}

void GameManager::drawOutputImage() {
    this->getOutputImage()->writeToTerminal(this->terminal);
}
