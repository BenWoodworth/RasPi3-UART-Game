#include "core/games/GameStateMainMenu.h"

#define STATE_1 1
#define STATE_2 2

void GameStateMainMenu::tick(GameManager* gameManager) {
    this->gameManager = gameManager;

    // Check if a game state object has been set and should be loaded
    if(this->selectedStateObject != NULL){
        gameManager->start(this->selectedStateObject);
    }

    AnsiImage* img = gameManager->getOutputImage();
    img->drawRect(
        0, 0, img->getWidth(), img->getHeight(),
        new AnsiPixel(this->color, Colors::fromRgb(0, 0, 0), ' ')
    );

    // Draw left box
    img->drawRect(
        2, 2, ((img->getWidth()) / 2)-3, 3,
        new AnsiPixel(Colors::fromGray(0),Colors::fromGray(0), ' ')
    );

    // Draw left box label
    uint32_t x_1 = 3;
    uint32_t y_1 = 3;
    img->drawString(x_1,y_1,label_1,Colors::fromGray(0),Colors::fromGray(25));

    // Draw right box
    img->drawRect(
        ((img->getWidth()) / 2)+1, 2, ((img->getWidth()) / 2)-3, 3,
        new AnsiPixel(Colors::fromGray(0),Colors::fromGray(0), ' ')
    );

    // Draw right box label
    uint32_t x_2 = ((img->getWidth())/ 2)+2;
    uint32_t y_2 = y_1;
    img->drawString(x_2,y_2,label_2,Colors::fromGray(0),Colors::fromGray(25));

    if (this->selectedState == STATE_1){
        // Draw select box under 1
        img->drawRect(
            2, 5, ((img->getWidth())/2)-3,1,
            new AnsiPixel(Colors::fromGray(25),Colors::fromGray(25), ' ')
        );
    } else if (this->selectedState == STATE_2){
        // Draw seelct box under 2
        img->drawRect(
            ((img->getWidth()) / 2)+1, 5, ((img->getWidth()) / 2)-3, 1,
            new AnsiPixel(Colors::fromGray(25),Colors::fromGray(25), ' ')        
        );
    }

    if (++this->color > Colors::fromRgb(5, 5, 5)) {
        this->color = Colors::fromRgb(0, 0, 0);
    }

    if (++this->ch > '9') {
        this->ch = '0';
    }
}

void GameStateMainMenu::handleInput(Key key){
    this->hasInput = true;
    std::string s = std::string(1,key.getChar());

    if(key.isLeft() || key.isRight()){
        if(this->selectedState == STATE_1){
            this->selectedState = STATE_2;
        } else {
            this->selectedState = STATE_1;
        }
    } else if(key.isSelect()){
        if(this->selectedState == STATE_1){
            this->selectedStateObject = new GameStateSnake();    
        } else {
            this->selectedStateObject = new GameStateTicTacToe();    
        }
    }
}
