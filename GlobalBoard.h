#pragma once
#include <stack>
#include "Cell.h"
#include "Coord.h"
#include "LocalBoard.h"

class GlobalBoard
{
private:
    LocalBoard** field;
    Cell winner;
    std::stack <Coord> history;

    void check();
public:
    GlobalBoard();
    ~GlobalBoard();

    // Warning: there are no safety checks in methods
    void set(Coord global, Coord local, Cell cell);
    void set(size_t by, size_t bx, size_t y, size_t x, Cell cell); 
    void revert();
    Cell get(Coord global, Coord local);
    Cell get(size_t by, size_t bx, size_t y, size_t x);
    Cell getWinner();

    // Will return Coord(-1, -1) if next board is any
    Coord nextBoard();
};