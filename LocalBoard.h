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
    void set(const size_t y, const size_t x, const Cell& cell); 
    void revert();
    Cell get(const size_t y, const size_t x) const;
    Cell getWinner() const;
    Coord getLastMove() const;
};