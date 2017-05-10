#include "games/GameStateTicTacToe.h"

void GameStateTicTacToe::tick(GameManager* gameManager) {
    this->gameManager = gameManager;
    AnsiImage* img = gameManager->getOutputImage();

    if(this->gameSpaceInitNeeded){
        initGameSpace(img);
        this->gameSpaceInitNeeded = false;    
    }

    // Draw the background
    img->drawRect(
        0, 0, img->getWidth(), img->getHeight(),
        new AnsiPixel(Colors::fromGray(25), Colors::fromGray(25), ' ')
    );


    
}

void GameStateTicTacToe::handleInput(Key key){
    // TODO: Fill in
}

void GameStateTicTacToe::initGameSpace(AnsiImage* img){
    //We're reserving the top row for player names
    this->xmin = 1;
    this->xmax = img->getWidth()-1;
    this->ymin = 2;
    this->ymax = img->getHeight()-1;         
}
