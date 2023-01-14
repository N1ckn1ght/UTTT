#include "LocalBoard.h"

LocalBoard::LocalBoard()
{
    field = new Cell*[3];
    for (size_t i = 0; i < 3; i++) {
        field[i] = new Cell[3];
        for (size_t j = 0; j < 3; j++) {
            field[i][j] = Cell::Empty;
        }
    }
    winner = Cell::Empty;
}

LocalBoard::~LocalBoard()
{
    for (size_t i = 0; i < 3; i++) {
        delete[] field[i];
    }
    delete[] field;
}

void LocalBoard::set(const size_t y, const size_t x, const Cell& cell)
{
    field[y][x] = cell;
    check();
    history.push(Coord(y, x));
}

void LocalBoard::revert()
{
    Coord lastMove = history.top();
    field[lastMove.y][lastMove.x] = Cell::Empty;
    winner = Cell::Empty;
    history.pop();
}

Cell LocalBoard::get(const size_t y, const size_t x) const
{
    return field[y][x];
}

Cell LocalBoard::getWinner() const
{
    return winner;
}

Coord LocalBoard::getLastMove() const
{
    return history.top();
}

void LocalBoard::check()
{
    // vertical and horizontal checks
    for (size_t i = 0; i < 3; i++) {
        if (field[0][i] != Cell::Empty && field[0][i] == field[1][i] && field[0][i] == field[2][i]) {
            winner = field[0][i];
            return;
        }
        if (field[i][0] != Cell::Empty && field[i][0] == field[i][1] && field[i][0] == field[i][2]) {
            winner = field[i][0];
            return;
        }
    }
    // diagonal checks
    if (field[1][1] != Cell::Empty) {
        if (field[1][1] == field[0][0] && field[1][1] == field[2][2]) {
            winner = field[1][1];
            return;
        }
        if (field[1][1] == field[0][2] && field[1][1] == field[2][0]) {
            winner = field[1][1];
            return;
        }
    }
    // draw case check
    if (history.size() > 8) {
        winner = Cell::Any;
    }
    // else winner is not specified yet
    else {
        winner = Cell::Empty;
    }
}