#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include <stdint.h>
#include "graphics/AnsiImage.h"
#include "graphics/AnsiImageBuilder.h"

/// Symbol in a point. 'NONE' is no symbol
enum class Symbol { X,O,NONE };

/// Space on the board 
struct Space {
    int x;
    int y;
    Symbol symbol;
    bool selected;
};

class Board{

private:
    // Define where the board can be drawn
    int32_t xmin;
    int32_t xmax;
    int32_t ymin;
    int32_t ymax;
    
    int boardSize;
    Space* board;
public:
    Board(int size, int32_t xmin, int32_t xmax, int32_t ymin, int32_t ymax){
        this->boardSize = size;
        this->xmin = xmin;
        this->xmax = xmax;
        this->ymin = ymin;
        this->ymax = ymax;
        // Init the board
        // Try to init the board 2D ary here
        // ...
        board = (struct Space*) malloc(sizeof(struct Space) * boardSize * boardSize);
        for(int i=0; i<boardSize; i++){
            for(int j=0; j<boardSize; j++){
                struct Space s;
                s.x = i;
                s.y = j;
                s.symbol = Symbol::NONE;
                s.selected = false;
                board[i*boardSize+j] = s;
            }    
        }
        // Select the first one
        board[0].selected = true;
    }
    
    /// Place a symbol in the specified location (x,y) in the grid. Bool for sucess/failure
    bool updateSymbol(int x, int y, Symbol symbol);

    /// Update the selection with direction
    void updateSelector(Direction dir);

    /// Return the space currently selected
    Space getSelectedSpace();

    /// Returns the symbol that has won, NONE if no winner
    Symbol getWinningSymbol();

    /// Returns vector of Points that have Symbol of NONE
    inline std::vector<Space> getAvailableSpaces(){
        return getSpacesWithSymbol(Symbol::NONE);
    }

    /// Returns vector of Points that have the given Symbol
    std::vector<Space> getSpacesWithSymbol(Symbol sym);

    /// Draw the board stored in memory
    void drawBoard(bool showSelected,int32_t xmin,int32_t xmax,int32_t ymin,int32_t ymax, AnsiImage* img);

    /// Draw the given board with the given information
    void drawSpace(Space space, int32_t x, int32_t y, int32_t width, int32_t height, AnsiImage* img);

    void drawSelector(int32_t x, int32_t y, int32_t width, AnsiImage* img);

};

#endif
