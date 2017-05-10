#include "games/GameStateTicTacToe.h"

void GameStateTicTacToe::tick(GameManager* gameManager) {
    this->gameManager = gameManager;
    AnsiImage* img = gameManager->getOutputImage();

    if(this->gameSpaceInitNeeded){
        initGameSpace(img);
        std::srand(gameManager->getFrameCount());
        //Also create a new Board object here
        this->board = new Board(3,this->xmin,this->xmax,this->ymin,this->ymax);
        this->gameSpaceInitNeeded = false;    
    }

    // Check for end of game
    Symbol winningSymbol = this->board->getWinningSymbol();
    if(winningSymbol != Symbol::NONE || !this->board->hasAvailableSpaces()){
        this->gameOver = true;
        if(this->players[0].getSymbol() == winningSymbol){
            this->winningPlayIndex = 0;
        } else if(this->players[1].getSymbol() == winningSymbol) {
            this->winningPlayIndex = 1;
        } else {
            // Well, I guess it's a draw!'
            this->winningPlayIndex = -1;
        }
    }

    // Draw the background
    img->drawRect(
        0, 0, img->getWidth(), img->getHeight(),
        new AnsiPixel(Colors::fromGray(25), Colors::fromGray(25), ' ')
    );

    // Draw the board
    this->board->drawBoard(true,this->xmin,this->xmax,this->ymin,this->ymax,img);
    
    // Draw the top bar
    img->drawRect(
        0,0, img->getWidth(), 1,
        new AnsiPixel(Colors::fromGray(5), Colors::fromGray(5), ' ')
    );
        //Player1
    img->drawString(1,0, this->players[0].getName(), Colors::fromGray(5), Colors::fromGray(25));
    if(this->activePlayerIndex == 0){
        img->drawString(this->players[0].getName().length() + 2,0, this->players[0].getSymbolStr(), Colors::fromGray(20), Colors::fromGray(2));
    } else {
        img->drawString(this->players[0].getName().length() + 2,0, this->players[0].getSymbolStr(), Colors::fromGray(5), Colors::fromGray(25));
    }
        //Player2
    img->drawString(this->xmax - this->players[1].getName().length(),0, this->players[1].getName(), Colors::fromGray(5), Colors::fromGray(25));
    if(this->activePlayerIndex == 1){
        img->drawString(this->xmax - this->players[1].getName().length()-2,0, this->players[1].getSymbolStr(), Colors::fromGray(20), Colors::fromGray(2));
    } else {
        img->drawString(this->xmax - this->players[1].getName().length()-2,0, this->players[1].getSymbolStr(), Colors::fromGray(5), Colors::fromGray(25));
    }

    //If the game is over, print the game over screen
    if(this->gameOver){
        int32_t width = (img->getWidth()/2)-2;
        int32_t height = 7;
        int32_t box_x = width/2;
        int32_t box_y = (img->getHeight()/2)-3;

        img->drawRect(
            box_x,box_y,width,height,
            new AnsiPixel(Colors::fromGray(5),Colors::fromGray(5))
        );

        img->drawString(box_x+1,box_y+1,"Game Over!",Colors::fromGray(5),Colors::fromGray(25));
        if(this->winningPlayIndex < 0){
            //It's a draw!
            img->drawString(box_x+1,box_y+3,"It's a Draw",Colors::fromGray(5),Colors::fromGray(25));
        }else{
            Player winningPlayer = this->players[this->winningPlayIndex];
            std::string winnerString = winningPlayer.getName() + " (" + winningPlayer.getSymbolStr() + ") Wins!";
            img->drawString(box_x+1,box_y+3,winnerString,Colors::fromGray(5),Colors::fromGray(25));
        }

        img->drawString(box_x+1,box_y+5,"Press Space to Continue...",Colors::fromGray(5),Colors::fromGray(25));
    }

    // Check if Computer should make a move
    if(!this->gameOver && this->players[this->activePlayerIndex].getPlayerType() == PlayerType::COMPUTER){
        // Let the CPU take it's turn
        Player player = this->players[this->activePlayerIndex];
        PlayerComputerRandom cpuPlayer = PlayerComputerRandom(player.getPlayerType(),player.getName(),player.getSymbol());
        cpuPlayer.takeAction(this->board);
        // Move on the next player when it has finished
        nextPlayer();
    }
}

void GameStateTicTacToe::handleInput(Key key){
    if(!this->gameOver && this->players[this->activePlayerIndex].getPlayerType() == PlayerType::HUMAN){
        if(key.isUp()){
            this->board->updateSelector(Direction::UP);    
        }else if(key.isDown()){
            this->board->updateSelector(Direction::DOWN);
        }else if(key.isLeft()){
            this->board->updateSelector(Direction::LEFT);
        }else if(key.isRight()){
            this->board->updateSelector(Direction::RIGHT);
        }else if(key.isSelect()){
            struct Space selected = this->board->getSelectedSpace();
            if(this->board->updateSymbol(selected.x, selected.y, getCurrentPlayer().getSymbol())){
                nextPlayer();
            }
        }
    }else{
        //Handle end of game space feature
        if(key.isSelect()){
            this->gameManager->start(new GameStateMainMenu());
        }
    }
}

void GameStateTicTacToe::initGameSpace(AnsiImage* img){
    //We're reserving the top row for player names
    this->xmin = 1;
    this->xmax = img->getWidth()-1;
    this->ymin = 2;
    this->ymax = img->getHeight()-1;         
}

Player GameStateTicTacToe::getCurrentPlayer(){
    return this->players[this->activePlayerIndex];
}

void GameStateTicTacToe::nextPlayer(){
    this->activePlayerIndex = (this->activePlayerIndex + 1) % 2;
}
