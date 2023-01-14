﻿#include "Field.h"

Field::Field()
{
    board = GlobalBoard();
    turn = Cell::Cross;
}

void Field::move(const GlobalCoord &coord)
{
    move(coord.by, coord.bx, coord.y, coord.x);
}

void Field::move(const Coord &global, Coord &local)
{
    move(global.y, global.x, local.y, local.x);
}

void Field::move(size_t by, size_t bx, size_t y, size_t x)
{
    board.set(by, bx, y, x, turn);
    turn = nextCell(turn);
}

void Field::revert()
{
    board.revert();
    turn = nextCell(turn);
}

const bool Field::isLegalMove(const GlobalCoord &coord)
{
    return isLegalMove(coord.by, coord.bx, coord.y, coord.x);
}

const bool Field::isLegalMove(const Coord &global, const Coord &local)
{
    return isLegalMove(global.y, global.x, local.y, local.x);
}

const bool Field::isLegalMove(size_t by, size_t bx, size_t y, size_t x)
{
    if (by > 2 || bx > 2 || y > 2 || x > 2) {
        return false;
    }
    if (board.getNextBoard().y != -1 && (board.getNextBoard().y != by || board.getNextBoard().x != bx)) {
        return false;
    }
    if (board.get(by, bx, y, x) != Cell::Empty) {
        return false;
    }
    return true;
}

const Cell Field::get(const GlobalCoord &coord)
{
    return get(coord.by, coord.bx, coord.y, coord.x);
}

const Cell Field::get(const Coord &global, const Coord &local)
{
    return get(global.y, global.x, local.y, local.x);
}

const Cell Field::get(size_t by, size_t bx, size_t y, size_t x)
{
    return board.get(by, bx, y, x);
}

const Cell Field::getTurn()
{
    return turn;
}

const Cell Field::getWinner()
{
    return board.getWinner();
}

const Coord Field::getNextBoard()
{
    return board.getNextBoard();
}

const std::vector<GlobalCoord> Field::getEmptyCells()
{
    std::vector <GlobalCoord> moves;
    for (size_t by = 0; by < 3; by++) {
        for (size_t bx = 0; bx < 3; bx++) {
            for (size_t y = 0; y < 3; y++) {
                for (size_t x = 0; x < 3; x++) {
                    if (board.get(by, bx, y, x) == Cell::Empty) {
                        moves.push_back(GlobalCoord(by, bx, y, x));
                    }
                }
            }
        }
    }
    return moves;
}

const std::vector<GlobalCoord> Field::getValidMoves()
{
    size_t by = board.getNextBoard().y;
    size_t bx = board.getNextBoard().x;
    if (by == -1) {
        return getEmptyCells();
    }
    std::vector <GlobalCoord> moves;
    for (size_t y = 0; y < 3; y++) {
        for (size_t x = 0; x < 3; x++) {
            if (board.get(by, bx, y, x) == Cell::Empty) {
                moves.push_back(GlobalCoord(by, bx, y, x));
            }
        }
    }
    return moves;
}