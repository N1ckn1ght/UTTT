#pragma once
#include <iostream>
#include <vector>
#include "GlobalBoard.h"

class GameException {};

class Field
{
private:
	GlobalBoard* board;
	Cell turn;
public:
	Field();
	~Field();

	// Warning: there are no safety checks in most methods
	void move(const GlobalCoord& coord);
	void move(const Coord& global, Coord& local);
	void move(size_t by, size_t bx, size_t y, size_t x);
	void revert();
	bool isLegalMove(const GlobalCoord& coord) const;
	bool isLegalMove(const Coord& global, const Coord& local) const;
	bool isLegalMove(size_t by, size_t bx, size_t y, size_t x) const;
	Cell get(const GlobalCoord& coord) const;
    Cell get(const Coord& global, const Coord& local) const;
    Cell get(size_t by, size_t bx, size_t y, size_t x) const;
	Cell getTurn() const;
    Cell getWinner() const;
	// Will return Coord(-1, -1) if next board is any
    Coord getNextBoard() const;
	// Heavy on time and memory, better to avoid overusing these in engine logic:
	// getEmptyCells will return valid moves by (y, x) on every board, where by = i / 3, bx = i % 3
	std::vector <std::vector <Coord>> getEmptyCells() const;
	// getValidMoves will return valid moves by full coordinate in a single vector
	std::vector <GlobalCoord> getValidMoves() const;

	friend std::ostream& operator << (std::ostream& out, Field& field);
};