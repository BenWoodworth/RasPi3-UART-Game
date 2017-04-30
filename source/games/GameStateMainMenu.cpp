#include "games/GameStateMainMenu.h"

void GameStateMainMenu::tick(GameManager* gameManager) {
    this->gameManager = gameManager;
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

    // Draw input text if it exists
    if (!(this->inputString.empty())){
        uint32_t x_3 = ((img->getWidth())/4);
        uint32_t y_3 = 7;
        img->drawString(x_3,y_3,this->inputString,Colors::fromGray(0),Colors::fromGray(25));    
    }

    // TODO: remove
    if (this->hasInput == true){
        img->drawRect(
            1,img->getHeight()-3,2,2, new AnsiPixel(Colors::fromGray(0),Colors::fromGray(0), 'A')
        );
    } else {
        img->drawRect(
            1,img->getHeight()-3,2,2, new AnsiPixel(Colors::fromGray(25),Colors::fromGray(25), 'B')
        );
    }

    if (++this->color > Colors::fromRgb(5, 5, 5)) {
        this->color = Colors::fromRgb(0, 0, 0);
    }

    if (++this->ch > '9') {
        this->ch = '0';
    }
}

void GameStateMainMenu::handleInput(char input){
    this->hasInput = true;
    std::string s = std::string(1,input);
    switch(this->gameManager->getTerminal()->getKey(input)){
        case 1:
            s = "Up key";
            break;
        case 2:
            s = "Down key";
            break;
        case 3:
            s = "Left key";
            break;
        case 4:
            s = "Right key";
            break;
        case 5:
            s = "Enter key";
            break;
        case 6:
            s = "Space key";
            break;
    }
    this->inputString = s;
}
