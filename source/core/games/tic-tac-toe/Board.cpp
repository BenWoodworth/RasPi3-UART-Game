#include "games/GameStateTicTacToe.h"

Symbol Board::getWinningSymbol(){

    bool allSame;
    Symbol lastSymbol;

    //Check Columns
    for(int x=0; x < this->boardSize; x++){
        allSame = false;
        lastSymbol = this->board[x*this->boardSize].symbol;
        for(int y=0; y < this->boardSize; y++){
            if(this->board[x*this->boardSize + y].symbol == lastSymbol){
                lastSymbol = this->board[x*this->boardSize + y].symbol;
                allSame = true;
            } else {
                allSame = false;
                break;
            }
        }
        if(allSame){
            return lastSymbol;
        }
    }

    //Check Rows
    for(int y=0; y < this->boardSize; y++){
        allSame = false;
        lastSymbol = this->board[y].symbol;
        for(int x=0; x < this->boardSize; x++){
            if(this->board[x*this->boardSize + y].symbol == lastSymbol){
                lastSymbol = this->board[x*this->boardSize + y].symbol;
                allSame = true;
            } else {
                allSame = false;
                break;
            }
        }
        if(allSame){
            return lastSymbol;
        }
    }

    //Check Left-Right Diag
    allSame = false;
    lastSymbol = this->board[0].symbol;
    for(int x=0, y=0; x < this->boardSize && y < this->boardSize; x++, y++){
        if(this->board[x*this->boardSize + y].symbol == lastSymbol){
            lastSymbol = this->board[x*this->boardSize + y].symbol;
            allSame = true;
        } else {
            allSame = false;
            break;
        }
    }
    if(allSame){
        return lastSymbol;
    }

    //Check Right-Left Diag
    allSame = false;
    lastSymbol = this->board[(this->boardSize-1)*this->boardSize].symbol;
    for(int x=this->boardSize-1, y=0; x >= 0 && y < this->boardSize; x--, y++){
        if(this->board[x*this->boardSize + y].symbol == lastSymbol){
            lastSymbol = this->board[x*this->boardSize + y].symbol;
            allSame = true;
        } else {
            allSame = false;
            break;
        }
    }
    if(allSame){
        return lastSymbol;
    }

    return Symbol::NONE;   
}

std::vector<Space> Board::getSpacesWithSymbol(Symbol sym){
    std::vector<Space> results;    

    for(int x=0; x < this->boardSize; x++){
        for(int y=0; y < this->boardSize; y++){
            if(this->board[x*this->boardSize + y].symbol == Symbol::NONE){
                results.push_back(this->board[x*this->boardSize + y]);
            }
        }    
    }

    return results;
}

void Board::drawBoard(bool showSelected,int32_t xmin,int32_t xmax,int32_t ymin,int32_t ymax, AnsiImage* img){
    
    int width = (xmax - xmin - (this->boardSize - 1)) / this->boardSize;
    int height = (ymax - ymin - (this->boardSize - 1)) / this->boardSize;

    for(int x=0; x < this->boardSize; x++){
        for(int y=0; y < this->boardSize; y++){
            //Draw the space itself
            drawSpace(
                this->board[x*this->boardSize + y],     //Space
                xmin + (x * width) + x,                 //x position
                ymin + (y * height) + y,                //y position
                width,                                  //width
                height,                                 //height
                img                                     //img
            );
            if(this->board[x*this->boardSize + y].selected){
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

bool Board::updateSymbol(int x, int y, Symbol symbol){
    if(this->board[x*this->boardSize + y].symbol == symbol){
        return false;
    }else{
        this->board[x*this->boardSize + y].symbol = symbol;
        return true;
    }
}

void Board::updateSelector(Direction dir){
    struct Space selected = getSelectedSpace();
    int32_t xNew = selected.x;
    int32_t yNew = selected.y;
    switch(dir){
        case Direction::UP:
            yNew = (selected.y - 1);
            // C++ Mod is dumb and will freak out wil negative numbers...
            if (yNew < 0){
                yNew += this->boardSize;
            }
            break;
        case Direction::DOWN:
            yNew = (selected.y + 1) % this->boardSize;
            break;
        case Direction::LEFT:
            xNew = (selected.x - 1);
            if (xNew < 0){
                xNew += this->boardSize;
            }
            break;
        case Direction::RIGHT:
            xNew = (selected.x + 1) % this->boardSize;
            break;
    }
    // Deselect Space
    this->board[selected.x*this->boardSize + selected.y].selected = false;
    // Select new Space
    this->board[xNew*this->boardSize + yNew].selected = true;
}

Space Board::getSelectedSpace(){
    for(int x=0; x < this->boardSize; x++){
        for(int y=0; y < this->boardSize; y++){
            if(this->board[x*this->boardSize + y].selected){
                return this->board[x*this->boardSize + y];
            }
        }    
    }
    // Default is 0,0. This should never happen
    return this->board[0];
}

void Board::drawSpace(Space space, int32_t x, int32_t y, int32_t width, int32_t height, AnsiImage* img){
    //TODO : Actually add the space symbol
    img->drawRect(
        x, y, width, height,
        new AnsiPixel(Colors::fromGray(0),Colors::fromGray(0), ' ')
    );
    switch(space.symbol){
        case Symbol::X:
            {
                AnsiImageBuilder* xBuilder = new AnsiImageBuilder(6,6,
                    "      "
                    " X  X "
                    "  XX  "
                    "  XX  "
                    " X  X "
                    "      "
                );
                xBuilder->mapChar('X', new AnsiPixel(Colors::fromRgb(0,5,0)));
                AnsiImage* xImage = xBuilder->build();
                img->drawImage(x+(width/2)-3,y,xImage);
            }
            break;
        case Symbol::O:
            {
                AnsiImageBuilder* oBuilder = new AnsiImageBuilder(6,6,
                    "      "
                    "  OO  "
                    " O  O "
                    " O  O "
                    "  OO  "
                    "      "
                );
                oBuilder->mapChar('O', new AnsiPixel(Colors::fromRgb(0,0,5)));
                AnsiImage* oImage = oBuilder->build();
                img->drawImage(x+(width/2)-3,y,oImage);
            }
            break;
        case Symbol::NONE:
            break;
    }
}

void Board::drawSelector(int32_t x, int32_t y, int32_t width, AnsiImage* img){
    img->drawRect(
        x, y, width, 1,
        new AnsiPixel(Colors::fromGray(10),Colors::fromGray(10),' ')
    );
}