#include "GlobalBoard.h"

GlobalBoard::GlobalBoard()
{
    field = new LocalBoard**[3];
    for (size_t i = 0; i < 3; i++) {
        field[i] = new LocalBoard*[3];
        for (size_t j = 0; j < 3; j++) {
            field[i][j] = new LocalBoard;
        }
    }
    winner = Cell::Empty;
}

GlobalBoard::~GlobalBoard()
{
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            delete field[i][j];
        }
        delete[] field[i];
    }
    delete[] field;
}

void GlobalBoard::set(const size_t by, const size_t bx, const size_t y, const size_t x, const Cell& cell)
{
    history.push(Coord(by, bx));
    field[by][bx]->set(y, x, cell);
    if (field[by][bx]->getWinner() != Cell::Empty) {
        check();
    }
}

void GlobalBoard::revert()
{
    Coord lastBoard = history.top();
    field[lastBoard.y][lastBoard.x]->revert();
    winner = Cell::Empty;
    history.pop();
}

Cell GlobalBoard::get(const size_t by, const size_t bx, const size_t y, const size_t x) const
{
    return field[by][bx]->get(y, x);
}

Cell GlobalBoard::getWinner() const
{
    return winner;
}

Cell GlobalBoard::getWinner(const size_t by, const size_t bx) const
{
    return field[by][bx]->getWinner();
}

Coord GlobalBoard::getNextBoard() const
{
    if (history.size() > 0) {
        Coord lastBoard = history.top();
        Coord lastMove = field[lastBoard.y][lastBoard.x]->getLastMove();
        if (field[lastMove.y][lastMove.x]->getWinner() == Cell::Empty) {
            return lastMove;
        }
    }
    return Coord(-1, -1);
}

void GlobalBoard::check()
{
    // vertical and horizontal checks
    for (size_t i = 0; i < 3; i++) {
        if (field[0][i]->getWinner() != Cell::Empty && field[0][i]->getWinner() != Cell::Any) {
            if (field[0][i]->getWinner() == field[1][i]->getWinner() && field[0][i]->getWinner() == field[2][i]->getWinner()) {
                winner = field[0][i]->getWinner();
                return;
            }
        }
        if (field[i][0]->getWinner() != Cell::Empty && field[i][0]->getWinner() != Cell::Any) {
            if (field[i][0]->getWinner() != Cell::Empty && field[i][0]->getWinner() == field[i][1]->getWinner() && field[i][0]->getWinner() == field[i][2]->getWinner()) {
                winner = field[i][0]->getWinner();
                return;
            }
        }
    }
    // diagonal checks
    if (field[1][1]->getWinner() != Cell::Empty && field[1][1]->getWinner() != Cell::Any) {
        if (field[1][1]->getWinner() == field[0][0]->getWinner() && field[1][1]->getWinner() == field[2][2]->getWinner()) {
            winner = field[1][1]->getWinner();
            return;
        }
        if (field[1][1]->getWinner() == field[0][2]->getWinner() && field[1][1]->getWinner() == field[2][0]->getWinner()) {
            winner = field[1][1]->getWinner();
            return;
        }
    }
    // draw case check
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            if (field[i][j]->getWinner() == Cell::Empty) {
                winner = Cell::Empty;
                return;
            }
        }
    }
    winner = Cell::Any;
    return;
}