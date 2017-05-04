#include "games/GameStateTicTacToe.h"

void GameStateTicTacToe::tick(GameManager* gameManager) {
    this->gameManager = gameManager;
    AnsiImage* img = gameManager->getOutputImage();

}

void GameStateTicTacToe::handleInput(Key key){
    // TODO: Fill in
}
