#include "Field.h"

Field::Field()
{
	turn = Cell::Cross;
	ptr = new Cell * **[3];
	boards = new Cell * [3];
	for (size_t by = 0; by < 3; by++) {
		ptr[by] = new Cell * *[3];
		boards[by] = new Cell[3];
		for (size_t bx = 0; bx < 3; bx++) {
			ptr[by][bx] = new Cell * [3];
			boards[by][bx] = Cell::Empty;
			for (size_t y = 0; y < 3; y++) {
				ptr[by][bx][y] = new Cell[3];
				for (size_t x = 0; x < 3; x++) {
					ptr[by][bx][y][x] = Cell::Empty;
				}
			}
		}
	}
}

Field::~Field()
{
	for (size_t by = 0; by < 3; by++) {
		for (size_t bx = 0; bx < 3; bx++) {
			for (size_t y = 0; y < 3; y++) {
				delete[] ptr[by][bx][y];
			}
			delete[] ptr[by][bx];
		}
		delete[] ptr[by];
		delete[] boards[by];
	}
	delete[] ptr;
	delete[] boards;
}

bool Field::insert(const size_t by, const size_t bx, const size_t y, const size_t x)
{
	if (by > 2 || bx > 2 || y > 2 || x > 2 || (!nextMoveIsAnywhere() && (by != lastMove.y || bx != lastMove.x)) || ptr[by][bx][y][x] != Cell::Empty) {
		return false;
	}
	ptr[by][bx][y][x] = turn;
	turn = nextCell(turn);
	lastBoard = Coord(by, bx);
	lastMove = Coord(y, x);
	adjudicateFor(by, bx);
	return true;
}

Cell Field::get(size_t by, size_t bx, size_t y, size_t x)
{
	return ptr[by][bx][y][x];
}

Cell Field::adjudicate()
{
	// vertical & horizontal check
	for (size_t i = 0; i < 3; i++) {
		if (boards[i][0] != Cell::Empty && boards[i][0] != Cell::Any) {
			if (boards[i][0] == boards[i][1] && boards[i][0] == boards[i][2]) {
				return boards[i][0];
			}
		}
		if (boards[0][i] != Cell::Empty && boards[0][i] != Cell::Any) {
			if (boards[0][i] == boards[1][i] && boards[0][i] == boards[2][i]) {
				return boards[0][i];
			}
		}
	}
	// diagonal check
	if (boards[1][1] != Cell::Empty && boards[1][1] != Cell::Any) {
		if (boards[1][1] == boards[0][0] && boards[1][1] == boards[2][2]) {
			return boards[1][1];
		}
		if (boards[1][1] == boards[0][2] && boards[1][1] == boards[2][0]) {
			return boards[1][1];
		}
	}
	// no legal moves check
	// if there are legal moves available, the game continues even in case of a dead draw
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			if (boards[i][j] == Cell::Empty) {
				return Cell::Empty;
			}
		}
	}
	// if there aren't any legal moves, it's sure a draw
	return Cell::Any;
}

Cell Field::adjudicatedFor(size_t by, size_t bx)
{
	return boards[by][bx];
}

Cell Field::getTurn()
{
	return turn;
}

Coord Field::getLastBoard()
{
	return lastBoard;
}

Coord Field::getLastMove()
{
	return lastMove;
}

Cell Field::getBoard(size_t by, size_t bx)
{
	return boards[by][bx];
}

bool Field::nextMoveIsAnywhere()
{
	if (lastMove.y == -1 || adjudicatedFor(lastMove.y, lastMove.x) != Cell::Empty) {
		return true;
	}
	return false;
}

void Field::set(const size_t by, const size_t bx, const size_t y, const size_t x, const Cell elem)
{
	ptr[by][bx][y][x] = elem;
}

void Field::setTurn(Cell cell)
{
	turn = cell;
}

void Field::setLastBoard(Coord board)
{
	lastBoard = board;
}

void Field::setLastMove(Coord coord)
{
	lastMove = coord;
}

void Field::setBoard(const size_t by, const size_t bx, Cell elem)
{
	boards[by][bx] = elem;
}

std::ostream& operator<<(std::ostream& out, const Field& field)
{
	for (size_t by = 0; by < 3; by++) {
		out << " _ _ _   _ _ _   _ _ _";
		if (by == 0) {
			out << "  Y";
		}
		out << "\n";
		for (size_t y = 0; y < 3; y++) {
			for (size_t bx = 0; bx < 3; bx++) {
				out << "|";
				for (size_t x = 0; x < 3; x++) {
					switch (field.ptr[by][bx][y][x]) {
					// real cases
					case Cell::Cross:
						out << "X";
						break;
					case Cell::Null:
						out << "O";
						break;
					case Cell::Empty:
						out << " ";
						break;
					// interface cases
					case Cell::Any:
						out << ".";
						break;
					case Cell::Cwon:
						out << "x";
						break;
					case Cell::Nwon:
						out << "o";
						break;
					default:
						out << " ";
						break;
					}
					if (x < 2) {
						out << " ";
					}
				}
				out << "| ";
				if (bx == 2) {
					out << (y + 1);
				}
			}
			out << "\n";
		}
		out << " - - -   - - -   - - -\n";
	}
	out << " 1 2 3   1 2 3   1 2 3  X\n";
	return out;
}

void Field::adjudicateFor(size_t by, size_t bx) {
	// vertical & horizontal check
	for (size_t i = 0; i < 3; i++) {
		if (ptr[by][bx][i][0] != Cell::Empty && ptr[by][bx][i][0] == ptr[by][bx][i][1] && ptr[by][bx][i][0] == ptr[by][bx][i][2]) {
			boards[by][bx] = ptr[by][bx][i][0];
			fill(by, bx, wonCell(ptr[by][bx][i][0]));
			return;
		}
		if (ptr[by][bx][0][i] != Cell::Empty && ptr[by][bx][0][i] == ptr[by][bx][1][i] && ptr[by][bx][0][i] == ptr[by][bx][2][i]) {
			boards[by][bx] = ptr[by][bx][0][i];
			fill(by, bx, wonCell(ptr[by][bx][0][i]));
			return;
		}
	}
	// diagonal check
	if (ptr[by][bx][1][1] != Cell::Empty) {
		if ((ptr[by][bx][1][1] == ptr[by][bx][0][0] && ptr[by][bx][1][1] == ptr[by][bx][2][2]) || (ptr[by][bx][1][1] == ptr[by][bx][0][2] && ptr[by][bx][1][1] == ptr[by][bx][2][0])) {
			boards[by][bx] = ptr[by][bx][1][1];
			fill(by, bx, wonCell(ptr[by][bx][1][1]));
			return;
		}
	}
	// no legal moves check
	// if there are legal moves available, this will count as Cell::Empty
	for (size_t y = 0; y < 3; y++) {
		for (size_t x = 0; x < 3; x++) {
			if (ptr[by][bx][y][x] == Cell::Empty) {
				return;
			}
		}
	}
	// if there aren't any moves available, it's a draw case
	boards[by][bx] = Cell::Any;
	fill(by, bx, Cell::Any);
}

void Field::fill(size_t by, size_t bx, Cell elem)
{
	for (size_t y = 0; y < 3; y++) {
		for (size_t x = 0; x < 3; x++) {
			ptr[by][bx][y][x] = elem;
		}
	}
}