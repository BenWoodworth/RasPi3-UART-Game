#include "games/GameStateTicTacToe.h"

void GameStateTicTacToe::tick(GameManager* gameManager) {
    this->gameManager = gameManager;
    AnsiImage* img = gameManager->getOutputImage();

    if(this->gameSpaceInitNeeded){
        initGameSpace(img);
        //Also create a new Board object here
        this->board = new Board(3,this->xmin,this->xmax,this->ymin,this->ymax);
        this->gameSpaceInitNeeded = false;    
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
}

void GameStateTicTacToe::handleInput(Key key){
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
