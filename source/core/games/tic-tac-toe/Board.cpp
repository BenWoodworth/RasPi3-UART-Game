#include "games/tic-tac-toe/Board.h"

Symbol Board::getWinningSymbol(){
    // TODO 
    return Symbol::NONE;   
}

std::vector<Space> Board::getSpacesWithSymbol(Symbol sym){
    // TODO
    std::vector<Space> results;
    return results;
}

void Board::drawBoard(bool showSelected,int32_t xmin,int32_t xmax,int32_t ymin,int32_t ymax, AnsiImage* img){
    
    int width = (xmax - xmin - (this->boardSize - 1)) / this->boardSize;
    int height = (ymax - ymin - (this->boardSize - 1)) / this->boardSize;

    for(int x=0; x < this->boardSize; x++){
        for(int y=0; y < this->boardSize; y++){
            //Draw the space itself
            drawSpace(
                this->board[x][y],          //Space
                xmin + (x * width) + x,     //x position
                ymin + (y * height) + y,    //y position
                width,                      //width
                height,                     //height
                img                         //img
            );
            if(this->board[x][y].selected){
                //Draw the selected bar
                drawSelector(
                    xmin + (x * width) + x,
                    ymin + ((y+1) * height) + y,
                    width,
                    img
                );
            }
        }    
    }
}

void Board::drawSpace(Space space, int32_t x, int32_t y, int32_t width, int32_t height, AnsiImage* img){
    //TODO : Actually add the space symbol
    img->drawRect(
        x, y, width, height,
        new AnsiPixel(Colors::fromGray(0),Colors::fromGray(0), ' ')
    );
}

void Board::drawSelector(int32_t x, int32_t y, int32_t width, AnsiImage* img){
    img->drawRect(
        x, y, width, 1,
        new AnsiPixel(Colors::fromGray(10),Colors::fromGray(10),' ')
    );
}