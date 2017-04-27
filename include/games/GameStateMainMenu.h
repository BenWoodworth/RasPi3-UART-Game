#ifndef GAMESTATEMAINMENU_H_
#define GAMESTATEMAINMENU_H_

#include "gameapi/GameState.h"

class GameStateMainMenu : public GameState {
private:
    uint8_t color;
    uint8_t ch;
public:
    GameStateMainMenu() {
        color = Colors::fromRgb(0, 0, 0);
        ch = '0';
    }

    void tick(GameManager* gameManager);
};

#endif
