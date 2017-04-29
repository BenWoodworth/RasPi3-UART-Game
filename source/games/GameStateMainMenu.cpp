#include "games/GameStateMainMenu.h"

void GameStateMainMenu::tick(GameManager* gameManager) {
    AnsiImage* img = gameManager->getOutputImage();
    img->drawRect(
        0, 0, img->getWidth(), img->getHeight(),
        new AnsiPixel(this->color, Colors::fromRgb(0, 0, 0), this->ch)
    );

    // Draw left box
    img->drawRect(
        2, 2, ((img->getWidth()) / 2)-3, 8,
        new AnsiPixel(Colors::fromRgb(0,0,0),Colors::fromRgb(0,0,0), ' ')
    );


    // Draw left box label
    uint32_t x_1 = 3;
    uint32_t y_1 = 6;
    uint8_t letterIndex = 0;
    while(label_1[letterIndex] != '\0'){
        img->setPixel(
            x_1 + letterIndex, y_1,
            new AnsiPixel(Colors::fromRgb(0,0,0), Colors::fromRgb(8,8,8), label_1[letterIndex])
        );  
        letterIndex++;    
    } 

    // Draw right box
    img->drawRect(
        ((img->getWidth()) / 2)+1, 2, ((img->getWidth()) / 2)-3, 8,
        new AnsiPixel(Colors::fromRgb(0,0,0),Colors::fromRgb(0,0,0), ' ')
    );

    //Draw right box label
    uint32_t x_2 = ((img->getWidth())/ 2)+2;
    uint32_t y_2 = y_1;
    letterIndex = 0;
    while(label_2[letterIndex] != '\0'){
        img->setPixel(
            x_2 + letterIndex, y_2,
            new AnsiPixel(Colors::fromRgb(0,0,0), Colors::fromRgb(8,8,8), label_2[letterIndex])
        );  
        letterIndex++;    
    }

    if (++this->color > Colors::fromRgb(5, 5, 5)) {
        this->color = Colors::fromRgb(0, 0, 0);
    }

    if (++this->ch > '9') {
        this->ch = '0';
    }
}

void GameStateMainMenu::handleInput(char input){
    // TODO
}
