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
	// Line analysis multiplier in case of any board move as first move
	float k;
	// Should it write debug information in std::cout?
	bool debug;
	// Eval addition on positional threats
	float tweak;

	// getChance() will return probability of winning on this move from 0 to 1
	Ratio**** ratios;
	// which moves are possible, basically contains array of Coord(y, x) on certain(by, bx) board
	Coord*** possible;
	// auxiliary array for Coord*** possible that contains amount of moves
	size_t** count;
	// general counter of possible moves (no matter which board)
	size_t countAll;
	// arays of positional eval multipliers
	float*** positionalMult;

	// General amount of moves has been made during the analysis
	size_t moves;

	void clear();
	void clearArrays();
	void init(Field& field);
	void eval(Field& field, size_t by, size_t bx, std::vector <EuristMove>& euristMoves, size_t lines_, Cell side);
public:
	// lines_: how much analysis line shall be distributed upon a choice
	// k     : multiplier of lines_ in case of any board first choice
	// debug : this stands just for an additional output of how many moves algo did calculate
	// tweak : eval modificator for certain positional threats
	//         when set to 0 it won't make a difference, recommended must be in (0; 1)
	Eurist(size_t lines_, float k_, bool debug_ = false, float tweak_ = 0);
	~Eurist();
	
	// Will return AMOUNT of moves algorithm has been made;
	// For geting best moves use vector <EuristMove> eval method
	size_t getMoves();

	// Returns sorted vector of possible moves in format (by, bx, y, x, winning chance [0-1])
	std::vector <EuristMove> eval(Field& field);
};