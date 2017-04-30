#ifndef GAMESTATEMAINMENU_H_
#define GAMESTATEMAINMENU_H_

#include "gameapi/GameState.h"

class GameStateMainMenu : public GameState {
private:
    uint8_t color;
    uint8_t ch;
    std::string label_1;
    std::string label_2;
    char inputBuffer[8];

public:
    GameStateMainMenu() {
        color = Colors::fromRgb(0, 0, 0);
        ch = '0';
        label_1 = "Snake";
        label_2 = "Tic-Tac-Toe";
    }

    void tick(GameManager* gameManager);

    void handleInput(char input);
};

#endif
