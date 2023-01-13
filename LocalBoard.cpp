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

void LocalBoard::set(Coord coord, Cell cell)
{
    field[coord.y][coord.x] = cell;
    history.push(coord);
}

void LocalBoard::set(size_t y, size_t x, Cell cell)
{
    field[y][x] = cell;
    history.push(Coord(y, x));
}

void LocalBoard::revert()
{
    Coord lastMove = history.top();
    field[lastMove.y][lastMove.x] = Cell::Empty;
    winner = Cell::Empty;
    history.pop();
}

Cell LocalBoard::get(Coord coord)
{
    return field[coord.y][coord.x];
}

Cell LocalBoard::get(size_t y, size_t x)
{
    return field[y][x];
}

Cell LocalBoard::getWinner()
{
    return winner;
}

Coord LocalBoard::getLastMove()
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