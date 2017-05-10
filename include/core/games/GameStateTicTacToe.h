#ifndef GAMESTATETICTACTOE_H_
#define GAMESTATETICTACTOW_H_

#include "gameapi/GameState.h"
#include "games/tic-tac-toe/Player.h"

class GameStateTicTacToe : public GameState {
private:
    GameManager* gameManager;
    Board* board;
    std::vector<Player*> players;
    bool gameSpaceInitNeeded;
    int32_t xmin;
    int32_t xmax;
    int32_t ymin;
    int32_t ymax;
public:
    GameStateTicTacToe() {
        gameSpaceInitNeeded = true;
        //For now, have the game be played by two Humans
        players.clear();
        players.push_back(new Player(PlayerType::HUMAN,"Player 1",Symbol::X));
        players.push_back(new Player(PlayerType::HUMAN,"Player 2",Symbol::O));
    }

    void tick(GameManager* gameManager);

    void initGameSpace(AnsiImage* img);

    void handleInput(Key key);
};

#endif
