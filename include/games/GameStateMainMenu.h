#ifndef GAMESTATEMAINMENU_H_
#define GAMESTATEMAINMENU_H_

#include "gameapi/GameState.h"

class GameStateMainMenu : public GameState {
private:
    uint8_t color;
    uint8_t ch;
    char label_1[11];
    char label_2[11];
public:
    GameStateMainMenu() {
        color = Colors::fromRgb(0, 0, 0);
        ch = '0';
        // TODO find a better way to do this
        // label_1 "Snake"
        label_1[0] = 'S';
        label_1[1] = 'n';
        label_1[2] = 'a';
        label_1[3] = 'k';
        label_1[4] = 'e';
        // label_2 "Tic-Tac-Toe"
        label_2[0] = 'T';
        label_2[1] = 'i';
        label_2[2] = 'c';
        label_2[3] = '-';
        label_2[4] = 'T';
        label_2[5] = 'a';
        label_2[6] = 'c';
        label_2[7] = '-';
        label_2[8] = 'T';
        label_2[9] = 'o';
        label_2[10] = 'e';
    }

    void tick(GameManager* gameManager);

    void handleInput(char input);
};

#endif
