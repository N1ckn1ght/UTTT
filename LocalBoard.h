#pragma once
#include <stack>
#include "Cell.h"
#include "Coord.h"

class LocalBoard
{
private:
    Cell** field;
    Cell winner;
    std::stack <Coord> history;

    void check();
public:
    LocalBoard();
    ~LocalBoard();
    
    // Warning: there are no safety checks in methods
    void set(Coord coord, Cell cell);
    void set(size_t y, size_t x, Cell cell); 
    void revert();
    Cell get(Coord coord);
    Cell get(size_t y, size_t x);
    Cell getWinner();
    Coord getLastMove();
};