#pragma once
#include <iostream>
#include <vector>
#include "GlobalBoard.h"

class Field
{
private:
	GlobalBoard board;
	Cell turn;
public:
	Field();

	// Warning: there are no safety checks in most methods
	void move(const GlobalCoord& coord);
	void move(const Coord& global, Coord& local);
	void move(size_t by, size_t bx, size_t y, size_t x);
	void revert();
	const bool isLegalMove(const GlobalCoord& coord);
	const bool isLegalMove(const Coord& global, const Coord& local);
	const bool isLegalMove(size_t by, size_t bx, size_t y, size_t x);
	const Cell get(const GlobalCoord& coord);
    const Cell get(const Coord& global, const Coord& local);
    const Cell get(size_t by, size_t bx, size_t y, size_t x);
	const Cell getTurn();
    const Cell getWinner();
	// Will return Coord(-1, -1) if next board is any
    const Coord getNextBoard();
	// Heavy on time, better to avoid overusing these in engine logic
	const std::vector <GlobalCoord> getEmptyCells();
	const std::vector <GlobalCoord> getValidMoves();

	friend std::ostream& operator << (std::ostream& out, Field& field);
};