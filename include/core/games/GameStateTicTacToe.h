#ifndef GAMESTATETICTACTOE_H_
#define GAMESTATETICTACTOE_H_

#include "gameapi/GameState.h"
#include "games/GameStateMainMenu.h"
#include "games/tic-tac-toe/Player.h"
#include "games/tic-tac-toe/Board.h"

class GameStateTicTacToe : public GameState {
private:
    GameManager* gameManager;
    Board* board;
    std::vector<Player> players;
    int activePlayerIndex;
    bool gameSpaceInitNeeded;
    int32_t xmin;
    int32_t xmax;
    int32_t ymin;
    int32_t ymax;
    bool gameOver;
    int winningPlayIndex;
public:
    GameStateTicTacToe() {
        gameSpaceInitNeeded = true;
        //For now, have the game be played by two Humans
        players.clear();
        players.push_back(Player(PlayerType::HUMAN,"Player 1",Symbol::X));
        players.push_back(Player(PlayerType::HUMAN,"Player 2",Symbol::O));
        activePlayerIndex = 0;

        gameOver = false;
        winningPlayIndex = -1;
    }

    void tick(GameManager* gameManager);

    void initGameSpace(AnsiImage* img);

    void handleInput(Key key);

    Player getCurrentPlayer();

    void nextPlayer();
};

#endif
