#pragma once
#include <algorithm>
#include <climits>
#include "Field.h"
#include "EvalMove.h"

class MinMaxEngine
{
private:
	double minimax(Field& field, size_t depth, double alpha, double beta, bool isMaximizing);
	
	// Every evaluation score can be modified here;
	// By example, for some cases it's (total_score = limit / max_possible_score).
	// In fact, just to be more visually appealing (and to provide more information to the end user).
	virtual void modEvals(std::vector <EvalMove>& evals) = 0;
	// This is the main, static evaluation function.
	// This, with the combination of min-max algo optimisations, will define the strength of the engine.
	// Also it's possible to make it not *that* strong, but more random, and just fun to play.
	virtual double staticEval(Field& field) = 0;
public:
	// Note: depth is set in HALF-moves!
	// So if you're willing to have n-depth analysis, set it to 2*n.
	std::vector <EvalMove> eval(Field& field, size_t depth);
};