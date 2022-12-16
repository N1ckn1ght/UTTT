#pragma once
#include <cstdlib>
#include "Field.h"
#include "Ratio.h"
#include "Coord.h"
#include "EuristMove.h"
// sorting eval output vector
#include <algorithm>
#include <vector>

class Eurist {
private:
	// How many random non-unique lines will be analyzed per move?
	size_t lines;
	// Line analysis multiplier in case of any board move
	float k;
	// Should it write debug information in std::cout?
	bool debug;

	// getChance() will return probability of winning on this move from 0 to 1
	Ratio**** ratios;
	// which moves are possible, basically contains array of Coord(y, x) on certain(by, bx) board
	Coord*** possible;
	// auxiliary array for Coord*** possible that contains amount of moves
	size_t** count;
	// general counter of possible moves (no matter which board)
	size_t countAll;

	// General amount of moves has been made during the analysis
	size_t moves;

	void clear();
	void clearArrays();
	void init(Field& field);
	void eval(Field& field, size_t by, size_t bx, std::vector <EuristMove>& euristMoves, size_t lines_, Cell side);
public:
	Eurist(size_t lines_, float k_, bool debug_ = false);
	~Eurist();
	
	// Returns sorted vector of possible moves in format (by, bx, y, x, winning chance [0-1])
	std::vector <EuristMove> eval(Field& field);
};