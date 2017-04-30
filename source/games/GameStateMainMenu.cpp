#include "games/GameStateMainMenu.h"

void GameStateMainMenu::tick(GameManager* gameManager) {
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

    //Draw right box label
    uint32_t x_2 = ((img->getWidth())/ 2)+2;
    uint32_t y_2 = y_1;
    img->drawString(x_2,y_2,label_2,Colors::fromGray(0),Colors::fromGray(25));

    if (++this->color > Colors::fromRgb(5, 5, 5)) {
        this->color = Colors::fromRgb(0, 0, 0);
    }

    if (++this->ch > '9') {
        this->ch = '0';
    }
}

void GameStateMainMenu::handleInput(char input){
    
}
