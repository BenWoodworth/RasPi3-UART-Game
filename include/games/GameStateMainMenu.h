#ifndef GAMESTATEMAINMENU_H_
#define GAMESTATEMAINMENU_H_

#include "gameapi/GameState.h"
#include "games/GameStateSnake.h"
#include "games/GameStateTicTacToe.h"

class GameStateMainMenu : public GameState {
private:
    uint8_t color;
    uint8_t ch;
    std::string label_1;
    std::string label_2;
    std::string inputString;
    bool hasInput;
    uint8_t selectedState;
    GameManager* gameManager;
    GameState* selectedStateObject;
public:
    GameStateMainMenu() {
        color = Colors::fromRgb(0, 0, 0);
        ch = '0';
        label_1 = "Snake";
        label_2 = "Tic-Tac-Toe";
        inputString = "Press arrow keys then enter...";
        hasInput = false;
        selectedState = 1;
        selectedStateObject = NULL;
    }

    void tick(GameManager* gameManager);

    void handleInput(char input);
};

#endif
