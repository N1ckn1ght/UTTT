#pragma once
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
    void set(const size_t by, const size_t bx, const size_t y, const size_t x, const Cell& cell);
    void revert();
    const Cell get(const size_t by, const size_t bx, const size_t y, const size_t x);
    const Cell getWinner();
    // Will return Coord(-1, -1) if next board is any
    const Coord getNextBoard();
};