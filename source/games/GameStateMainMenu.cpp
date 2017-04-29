#include "games/GameStateMainMenu.h"

void GameStateMainMenu::tick(GameManager* gameManager) {
    AnsiImage* img = gameManager->getOutputImage();
    img->drawRect(
        0, 0, img->getWidth(), img->getHeight(),
        new AnsiPixel(this->color, Colors::fromRgb(0, 0, 0), ' ')
    );

    // Draw left box
    img->drawRect(
        2, 2, ((img->getWidth()) / 2)-3, 8,
        new AnsiPixel(Colors::fromRgb(0,0,0),Colors::fromRgb(0,0,0), ' ')
    );

    // Draw left box label
    uint32_t x_1 = 3;
    uint32_t y_1 = 6;
    for (uint8_t letterIndex = 0; letterIndex < sizeof(label_1); letterIndex++){
        img->setPixel(
            x_1 + letterIndex, y_1,
            new AnsiPixel(Colors::fromRgb(0,0,0), Colors::fromRgb(256,256,256), label_1[letterIndex])
        );    
    }
    

    // Draw right box
    img->drawRect(
        ((img->getWidth()) / 2)+1, 2, ((img->getWidth()) / 2)-3, 8,
        new AnsiPixel(Colors::fromRgb(0,0,0),Colors::fromRgb(0,0,0), ' ')
    );

    //Draw right box label

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
