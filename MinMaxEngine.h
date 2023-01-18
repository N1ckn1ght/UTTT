#pragma once
#include <algorithm>
#include <climits>
#include "Field.h"
#include "EvalMove.h"

class MinMaxEngine
{
private:
	double minimax(Field& field, size_t depth, double alpha, double beta, bool isMaximizing) const;
	
	// Every evaluation score can be modified here;
	// By example, for some cases it's (total_score = limit / max_possible_score).
	// In fact, just to be more visually appealing (and to provide more information to the end user).
	virtual void modEvals(std::vector <EvalMove>& evals) const = 0;
	// This is the main, static evaluation function.
	// This, with the combination of min-max algo optimisations, will define the strength of the engine.
	// Also it's possible to make it not *that* strong, but more random, and just fun to play.
	virtual double staticEval(const Field& field) const = 0;
public:
	std::vector <EvalMove> eval(Field& field, size_t depth) const;
};