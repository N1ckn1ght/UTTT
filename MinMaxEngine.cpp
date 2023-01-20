#include "MinMaxEngine.h"

std::vector<EvalMove> MinMaxEngine::eval(Field& field, size_t depth)
{
	bool maximizing = (field.getTurn() == Cell::Cross);
	std::vector <GlobalCoord> legalMoves = field.getValidMoves();
	std::vector <EvalMove> evals;
	// This outer cycle's purpose is to save evals of all possible moves in current position.
	for (const GlobalCoord& move : legalMoves) {
		field.move(move);
		evals.push_back(EvalMove(move, minimax(field, depth - 1, -INT_MAX, INT_MAX, !maximizing)));
		field.revert();
	}
	modEvals(evals);
	if (maximizing) {
		std::sort(evals.begin(), evals.end(), evalMoveCmp);
	}
	else {
		std::sort(evals.rbegin(), evals.rend(), evalMoveCmp);
	}
	return evals;
}

double MinMaxEngine::minimax(Field& field, size_t depth, double alpha, double beta, bool isMaximizing)
{
	if (depth < 1 || field.getWinner() != Cell::Empty) {
		return staticEval(field);
	}
	double eval;
	// TODO: this is bad overusing of inefficient method that needs rework.
	std::vector <GlobalCoord> legalMoves = field.getValidMoves();
	if (isMaximizing) {
		eval = -INT_MAX;
		for (const GlobalCoord& move : legalMoves) {
			field.move(move);
			double temp = minimax(field, depth - 1, alpha, beta, false);
			field.revert();
			eval = std::max(eval, temp);
			alpha = std::max(alpha, temp);
			if (beta <= alpha) {
				break;
			}
		}
	}
	else {
		eval = INT_MAX;
		for (const GlobalCoord& move : legalMoves) {
			field.move(move);
			double temp = minimax(field, depth - 1, alpha, beta, true);
			field.revert();
			eval = std::min(eval, temp);
			beta = std::min(beta, temp);
			if (beta <= alpha) {
				break;
			}
		}
	}
	return eval;
}