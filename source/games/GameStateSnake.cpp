#include "games/GameStateSnake.h"

void GameStateSnake::tick(GameManager* gameManager) {
    this->gameManager = gameManager;

    AnsiImage* img = gameManager->getOutputImage();
    img->drawRect(
        0, 0, img->getWidth(), img->getHeight(),
        new AnsiPixel(Colors::fromGray(25), Colors::fromRgb(0, 0, 0), ' ')
    );

    // Draw left box
    img->drawRect(
        2, 2, ((img->getWidth()) / 2)-3, 3,
        new AnsiPixel(Colors::fromGray(0),Colors::fromGray(0), ' ')
    );

}

void GameStateSnake::handleInput(char input){
    // TODO: Fill in
}
