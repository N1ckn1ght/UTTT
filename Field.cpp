#include "Field.h"

Field::Field()
{
    board = new GlobalBoard;
    turn = Cell::Cross;
}

Field::~Field()
{
    delete board;
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
    board->set(by, bx, y, x, turn);
    turn = nextCell(turn);
}

void Field::revert()
{
    board->revert();
    turn = nextCell(turn);
}

bool Field::isLegalMove(const GlobalCoord &coord) const
{
    return isLegalMove(coord.by, coord.bx, coord.y, coord.x);
}

bool Field::isLegalMove(const Coord &global, const Coord &local) const
{
    return isLegalMove(global.y, global.x, local.y, local.x);
}

bool Field::isLegalMove(size_t by, size_t bx, size_t y, size_t x) const
{
    if (by > 2 || bx > 2 || y > 2 || x > 2) {
        return false;
    }
    Coord next = board->getNextBoard();
    if (next.y != -1 && (next.y != by || next.x != bx)) {
        return false;
    }
    if (board->getWinner(by, bx) != Cell::Empty) {
        return false;
    }
    if (board->get(by, bx, y, x) != Cell::Empty) {
        return false;
    }
    return true;
}

Cell Field::get(const GlobalCoord &coord) const
{
    return get(coord.by, coord.bx, coord.y, coord.x);
}

Cell Field::get(const Coord &global, const Coord &local) const
{
    return get(global.y, global.x, local.y, local.x);
}

Cell Field::get(size_t by, size_t bx, size_t y, size_t x) const
{
    return board->get(by, bx, y, x);
}

Cell Field::getTurn() const
{
    return turn;
}

Cell Field::getWinner() const
{
    return board->getWinner();
}

Cell Field::getWinner(const size_t by, const size_t bx) const
{
    return board->getWinner(by, bx);
}

Coord Field::getNextBoard() const
{
    return board->getNextBoard();
}

std::vector<std::vector<Coord>> Field::getEmptyCells() const
{
    std::vector <std::vector <Coord>> moves(9, std::vector <Coord>());
    for (size_t by = 0; by < 3; by++) {
        for (size_t bx = 0; bx < 3; bx++) {
            for (size_t y = 0; y < 3; y++) {
                for (size_t x = 0; x < 3; x++) {
                    if (board->get(by, bx, y, x) == Cell::Empty) {
                        moves[by * 3 + bx].push_back(Coord(y, x));
                    }
                }
            }
        }
    }
    return moves;
}

std::vector<GlobalCoord> Field::getValidMoves() const
{
    std::vector <GlobalCoord> moves;
    size_t by = board->getNextBoard().y;
    size_t bx = board->getNextBoard().x;
    if (by == -1) {
        for (size_t by = 0; by < 3; by++) {
            for (size_t bx = 0; bx < 3; bx++) {
                if (getWinner(by, bx) != Cell::Empty) {
                    continue;
                }
                for (size_t y = 0; y < 3; y++) {
                    for (size_t x = 0; x < 3; x++) {
                        if (board->get(by, bx, y, x) == Cell::Empty) {
                            moves.push_back(GlobalCoord(by, bx, y, x));
                        }
                    }
                }
            }
        }
    }
    else {
        for (size_t y = 0; y < 3; y++) {
            for (size_t x = 0; x < 3; x++) {
                if (board->get(by, bx, y, x) == Cell::Empty) {
                    moves.push_back(GlobalCoord(by, bx, y, x));
                }
            }
        }
    }
    return moves;
}

std::ostream &operator<<(std::ostream &out, Field &field)
{
    Coord nextBoard = field.getNextBoard();

    out << "\n       1     2     3   bx\n     1 2 3 1 2 3 1 2 3 x\n    +-----+-----+-----+\n";
    for (size_t by = 0; by < 3; by++) {
        for (size_t y = 0; y < 3; y++) {
            if (y == 1) {
                out << (by + 1) << " ";
            }
            else {
                out << "  ";
            }
            out << (y + 1) << " |";
            for (size_t bx = 0; bx < 3; bx++) {
                switch (field.getWinner(by, bx)) {
                case Cell::Cross:
                    out << "x x x|";
                    break;
                case Cell::Null:
                    out << "o o o|";
                    break;
                case Cell::Any:
                    out << "/ / /|";
                    break;
                default:
                    char cell = ' ';
                    if (nextBoard.y == -1 || nextBoard == Coord(by, bx)) {
                        cell = '.';
                    }
                    for (size_t x = 0; x < 3; x++) {
                        if (field.get(by, bx, y, x) == Cell::Empty) {
                            out << cell;
                        } 
                        else {
                            switch (field.get(by, bx, y, x)) {
                            case Cell::Cross:
                                out << "X";
                                break;
                            case Cell::Null:
                                out << "O";
                                break;
                            default:
                                throw GameException();
                                break;
                            }
                        }
                        if (x < 2) {
                            out << " ";
                        }
                        else {
                            out << "|";
                        }
                    }
                }
            }
            out << "\n";
        }
        if (by == 2) {
            out << "byy ";
        }
        else {
            out << "    ";
        }
        out << "+-----+-----+-----+\n";
    }
    out << "\n";
    return out;
}