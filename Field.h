#pragma once
#include <iostream>
#include <stack>
#include "Cell.h"
#include "Coord.h"

class Field
{
private:
	// Entire field of 3x3 boards of 3x3 cells (by, bx, y, x)
	// unsigned char**** ptr;
	// Which turn it is now
	unsigned char turn;
	// Next board to move
	
	// Last move by (y, x)
	Coord lastMove;
	// Adjudicated boards
	Cell** boards;

	// Adjudicate certain board - if there's a winner, make it to **boards
	void adjudicateFor(size_t by, size_t bx);
	// Used for printing already adjudicated boards, also prevents from moving on them
	void fill(size_t by, size_t bx, Cell elem);

	std::stack <unsigned char> history;
public:
	Field();
	~Field();

	// This method has protection and will return false on failure or it will place CROSS or NULL accordingly to its Cell turn
	bool insert(const size_t by, const size_t bx, const size_t y, const size_t x);
	// This method has no protection from illegal (any > 2) values
	Cell get(const size_t by, const size_t bx, const size_t y, const size_t x);
	// Will check **boards and determine winner by it, or Cell::Any if no legal moves left
	// TODO: maybe return draw also if there's also no way to get any other result?
	// TODO: possible move it to private and store a winner (if there is) in a variable inside of the class
	Cell adjudicate();
	// Will return a winner of exact (by, bx) board, or Cell::Any on draw, or Cell::Empty
	Cell adjudicatedFor(const size_t by, const size_t bx);
	// Will return true if the next move can be done at any empty board:
	bool nextMoveIsAnywhere();
	// Will return true if this move is possible but won't make a move on itself
	bool isPossibleMove(const size_t by, const size_t bx, const size_t y, const size_t x);

	Cell getTurn();
	Coord getLastBoard();
	Coord getLastMove();
	Cell getBoard(size_t by, size_t bx);

	// The next method section is only usable for making copies
	
	// This method has no protection any from illegal values or moves, also doesn't modify any field variables
	void set(const size_t by, const size_t bx, const size_t y, const size_t x, const Cell elem);
	// Don't call this if you didn't use set previously
	void setTurn(Cell cell);
	// Don't call this if you didn't use set previously
	void setLastBoard(Coord board);
	// Don't call this if you didn't use set previously
	void setLastMove(Coord coord);
	// Don't call this if you didn't use set previously
	void setBoard(const size_t by, const size_t bx, Cell elem);

	friend std::ostream& operator << (std::ostream& out, Field& field);
};