#include "Heurist_v2_0.h"

Heurist_v2_0::Heurist_v2_0(size_t branches_)
{
	branches = branches_;
}

double Heurist_v2_0::staticEval(Field& field)
{
	double result = 0;
	for (size_t i = 0; i < branches; i++) {
		size_t count = 0;
		while (field.getWinner() == Cell::Empty) {
			std::vector <GlobalCoord> moves = field.getValidMoves();
			field.move(moves[rand() % moves.size()]);
			count++;
		};
		result += k(field.getWinner());
		for (size_t j = 0; j < count; j++) {
			field.revert();
		}
	}
	result /= (double)branches;
	return result;
}

void Heurist_v2_0::modEvals(std::vector<EvalMove>& evals)
{
	for (EvalMove& eval : evals) {
		eval.eval = eval.eval * 100;
	}
}

double Heurist_v2_0::k(const Cell& cell) const
{
	switch (cell) {
	case Cell::Cross:
		return 1.0;
	case Cell::Null:
		return 0.0;
	case Cell::Any:
		return 0.5;
	default:
		return 0.5;
	}
}