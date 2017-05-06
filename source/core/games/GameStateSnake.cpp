#include "games/GameStateSnake.h"

void GameStateSnake::tick(GameManager* gameManager) {
    this->gameManager = gameManager;

    AnsiImage* img = gameManager->getOutputImage();
    
    // *Create new game *
    if(this->newGame == true){
        GameStateSnake::createSnake(256,img->getWidth()/2,img->getHeight()/2);
        this->newGame == false;
    }

    // *Set next point here*
    struct Point nextPoint;
    switch(this->dir){
        case Direction::UP:
            nextPoint.x = this->snake.front().x;
            nextPoint.y = this->snake.front().y-1;
            if(nextPoint.y < 0){
                nextPoint.y = img->getHeight();    
            }
            break;
        case Direction::DOWN:
            nextPoint.x = this->snake.front().x;
            nextPoint.y = this->snake.front().y+1;
            if(nextPoint.y > img->getHeight()){
                nextPoint.y = 0;    
            }
            break;
        case Direction::LEFT:
            nextPoint.x = this->snake.front().x-1;
            nextPoint.y = this->snake.front().y;
            if(nextPoint.x > img->getWidth()){
                nextPoint.x = 0;    
            }
            break;
        case Direction::RIGHT:
            nextPoint.x = this->snake.front().x+1;
            nextPoint.y = this->snake.front().y;
            if(nextPoint.x < 0){
                nextPoint.x = img->getWidth();    
            }
            break;
    }

    // *Check for collisions here*


    // *Move and draw the snake*
    std::vector<Point>::iterator it;
    for(it=this->snake.end(); it<this->snake.begin(); it--){
        if(it - 1 >= this->snake.begin()){
            it->x = (it-1)->x;
            it->y = (it-1)->y;    
        } else {
            it->x = nextPoint.x;
            it->y = nextPoint.y;    
        }
        img->setPixel(it->x,it->y,new AnsiPixel(Colors::fromGray(0),Colors::fromGray(0),' '));
    }
    
}

void GameStateSnake::handleInput(Key key){
    // TODO: Fill in
}

std::vector<Point> GameStateSnake::createSnake(int size, int32_t x, int32_t y){
    this->snake.clear();
    struct Point p1;
    p1.x = x;
    p1.y = y;
    this->snake.push_back(p1);
    struct Point p2;
    p2.x = x;
    p2.y = y-1;
    this->snake.push_back(p2);
    return this->snake;
}
