#include "games/GameStateSnake.h"

void GameStateSnake::tick(GameManager* gameManager) {
    this->gameManager = gameManager;

    AnsiImage* img = gameManager->getOutputImage();
   
    if(this->gameSpaceInitNeeded){
        initGameSpace(img);
        this->gameSpaceInitNeeded = false;    
    }
    
    // Draw the background
    img->drawRect(
        0, 0, img->getWidth(), img->getHeight(),
        new AnsiPixel(Colors::fromGray(25), Colors::fromGray(25), ' ')
    );

    // Draw the score bar
    // TODO: Put a score here
    img->drawRect(
        0,0, img->getWidth(), 1,
        new AnsiPixel(Colors::fromGray(5), Colors::fromGray(5), ' ')
    );

    // *Create new game *
    if(this->newGame == true){
        GameStateSnake::createSnake(256,img->getWidth()/2,img->getHeight()/2);
        this->newGame = false;
    }

    // *Set next point here*
    struct Point nextPoint;
    switch(this->dir){
        case Direction::UP:
            nextPoint.x = this->snake.front().x;
            nextPoint.y = this->snake.front().y-1;
            if(nextPoint.y < this->ymin){
                nextPoint.y = this->ymax;    
            }
            break;
        case Direction::DOWN:
            nextPoint.x = this->snake.front().x;
            nextPoint.y = this->snake.front().y+1;
            if(nextPoint.y > this->ymax){
                nextPoint.y = this->ymin;    
            }
            break;
        case Direction::LEFT:
            nextPoint.x = this->snake.front().x-1;
            nextPoint.y = this->snake.front().y;
            if(nextPoint.x < this->xmin){
                nextPoint.x = this->xmax;    
            }
            break;
        case Direction::RIGHT:
            nextPoint.x = this->snake.front().x+1;
            nextPoint.y = this->snake.front().y;
            if(nextPoint.x > this->xmax){
                nextPoint.x = this->xmin;    
            }
            break;
    }

    // *Check for collisions here*
    // Check food collision
    if(isInBoundsOfFood(this->snake.front().x,this->snake.front().y)){
        // Add one element to tail
        struct Point tail;
        tail.x = this->snake.back().x;
        tail.y = this->snake.back().y;
        this->snake.push_back(tail);
        // Fire generation of new food
        this->newFoodNeeded = true;
    }
    // Check for collision with snake
    if(isInBoundsOfSnakeNotHead(this->snake.front().x,this->snake.front().y)){
        // TODO: Handle end of game case    
    }

    // *Move and draw the snake*
    std::vector<Point>::iterator it = this->snake.end();
    while (it != this->snake.begin())
    {
        //There's an off by one error here somewhere...
        --it;
        if(it - 1 > this->snake.begin()){
            it->x = (it-1)->x;
            it->y = (it-1)->y;    
        } else {
            it->x = nextPoint.x;
            it->y = nextPoint.y;    
        }
        img->setPixel(it->x,it->y,new AnsiPixel(Colors::fromGray(0),Colors::fromGray(0),' '));       
    }

    // *Draw/Generate food*
    if(this->newFoodNeeded){
        generateNextFood();
        this->newFoodNeeded = false;    
    }
    img->setPixel(this->food.x,this->food.y,new AnsiPixel(Colors::fromGray(15),Colors::fromGray(15),' '));

}

void GameStateSnake::handleInput(Key key){
    if(key.isUp()){
        this->dir = Direction::UP;    
    }else if(key.isDown()){
        this->dir = Direction::DOWN;
    }else if(key.isLeft()){
        this->dir = Direction::LEFT;
    }else if(key.isRight()){
        this->dir = Direction::RIGHT;
    }
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
    struct Point p3;
    p3.x = x-1;
    p3.y = y-1;
    this->snake.push_back(p3);
    return this->snake;
}

bool GameStateSnake::isInBoundsOfFood(int32_t x, int32_t y){
    return this->food.x == x && this->food.y == y;    
}

void GameStateSnake::generateNextFood(){
    struct Point food;
    do{
        food.x = this->xmin + (std::rand() % (this->xmax - this->xmin + 1));
        food.y = this->ymin + (std::rand() % (this->ymax - this->ymin + 1));
    }while(isInBoundsOfSnake(food.x,food.y));
    this->food = food;
}

void GameStateSnake::initGameSpace(AnsiImage* img){
    //We're reserving the top row for score
    this->xmin = 0;
    this->xmax = img->getWidth();
    this->ymin = 1;
    this->ymax = img->getHeight();  
}

bool GameStateSnake::isInBoundsOfSnake(int32_t x, int32_t y){
     std::vector<Point>::iterator it;
     for(it = this->snake.begin(); it < this->snake.end(); it++){
        if(it->x == x && it->y == y){
            return true;
        }    
     }
     return false;
}

bool GameStateSnake::isInBoundsOfSnakeNotHead(int32_t x, int32_t y){
     std::vector<Point>::iterator it;
     // Note the ++ here to skip the first element
     for(it = this->snake.begin()++; it < this->snake.end(); it++){
        if(it->x == x && it->y == y){
            return true;
        }    
     }
     return false;
}
