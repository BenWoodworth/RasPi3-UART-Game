#ifndef BOARD_H_
#define BOARD_H_

/// Symbol in a point. 'NONE' is no symbol
enum class Symbol { X,O,NONE };

/// Point to 
struct Point {
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
    
    int size;
    Point board[size][size];
public:
    Board(int size, int32_t xmin, int32_t xmax, int32_t ymin, int32_t ymax){
        this->size = size;
        this->xmin = xmin;
        this->xmax = xmax;
        this->ymin = ymin;
        this->ymax = ymax;
        // Init the board
        for(int i=0; i<size; i++){
            for(int j=0; j<size; j++){
                struct Point p;
                p.x = i;
                p.y = j;
                p.symbol = Symbol::NONE;
                p.selected = false;
                board[i][j] = p;
            }    
        }
        // Select the first one
        board[0][0].selected = true;
    }
    
    /// Returns the symbol that has won, NONE if no winner
    Symbol getWinningSymbol();

    /// Returns vector of Points that have Symbol of NONE
    inline std::vector<Point> getAvailablePoints(){
        return getAvailablePoints(Symbol::NONE);
    }

    /// Returns vector of Points that have the given Symbol
    std::vector<Point> getPointsWithSymbol(Symbol sym);

    /// Draw the board stored in memory
    void drawBoard(bool showSelected, AnsiImage* img);

    /// Draw the given board with the given information
    void drawPoint(Point point, int32_t x, int32_t y, AnsiImage* img);

}

#endif
