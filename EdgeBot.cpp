#include "EdgeBot.h"

EdgeBot::EdgeBot()
{
	EVAL_MAX = 255;

	// Points for a cell on a local board
	localPts = std::vector <std::vector <double>>({ {3, 2, 3}, {2, 4, 2}, {3, 2, 3} });
	// Points for a cell on a local board on the global board
	globalPts = std::vector <std::vector <double>>({ {3, 2, 3}, {2, 4, 2}, {3, 2, 3} });
	// Points for a board on the global board
	localWinPts = std::vector <std::vector <double>>({ {36, 24, 36}, {24, 48, 24}, {36, 24, 36} });
	// Points for winning the game
	globalWinPts = 65535;
	// Points for having an attack on a local board (e.g. [XX.] or [X.X])
	localAtkPts = 4;
	// Limit for points for attack on a local board
	localAtkLim = 5;
	// Points for having an attack on the global board (winning two board in row, like [OO.] or [O.O])
	globalAtkPts = 48;
	// Points for an attack on adjacent board in case of future potential global attack (limited to itself)
	// Not yet implemented
	// Points for having a self-referencing cell, meaning it's on (i, j, i, j) coordinates
	selfRefPts = 3;
}

double EdgeBot::staticEval(const Field& field)
{
	// checks for: globalWinPts
	switch (field.getWinner()) {
	case Cell::Cross:
		return globalWinPts;
	case Cell::Null:
		return -globalWinPts;
	case Cell::Any:
		return 0;
	default:
		break;
	}
	// checks for: localPts, globalPts, localWinPts, selfRefPts
	double result = 0;
	for (size_t by = 0; by < 3; by++) {
		for (size_t bx = 0; bx < 3; bx++) {
			double temp = localWinPts[by][bx] * k(field.getWinner(by, bx));
			if (temp != 0) {
				result += temp;
				continue;
			}
			result += selfRefPts * k(field.get(by, bx, by, bx));
			for (size_t y = 0; y < 3; y++) {
				for (size_t x = 0; x < 3; x++) {
					result += (globalPts[by][bx] + localPts[y][x]) * k(field.get(by, bx, y, x));
				}
			}
		}
	}
	// checks for: globalAtkPts
	for (size_t i = 0; i < 3; i++) {
		result += double(std::abs(k(field.getWinner(i, 0)) + k(field.getWinner(i, 1)) + k(field.getWinner(i, 2))) == 2) * k(field.getWinner(i, 0)) * globalAtkPts;
		result += double(std::abs(k(field.getWinner(0, i)) + k(field.getWinner(1, i)) + k(field.getWinner(2, i))) == 2) * k(field.getWinner(0, i)) * globalAtkPts;
	}
	result += double(std::abs(k(field.getWinner(0, 0)) + k(field.getWinner(1, 1)) + k(field.getWinner(2, 2))) == 2) * k(field.getWinner(1, 1)) * globalAtkPts;
	result += double(std::abs(k(field.getWinner(0, 2)) + k(field.getWinner(1, 1)) + k(field.getWinner(2, 0))) == 2) * k(field.getWinner(1, 1)) * globalAtkPts;
	// checks for: localAtkPts, localAtkLim
	double temp = 0;
	for (size_t by = 0; by < 3; by++) {
		for (size_t bx = 0; bx < 3; bx++) {
			for (size_t i = 0; i < 3; i++) {
				temp += (double)atk(field.get(by, bx, i, 0), field.get(by, bx, i, 1), field.get(by, bx, i, 2)) * localAtkPts;
				temp += (double)atk(field.get(by, bx, 0, i), field.get(by, bx, 1, i), field.get(by, bx, 2, i)) * localAtkPts;
			}
			temp += (double)atk(field.get(by, bx, 0, 0), field.get(by, bx, 1, 1), field.get(by, bx, 2, 2)) * localAtkPts;
			temp += (double)atk(field.get(by, bx, 0, 2), field.get(by, bx, 1, 1), field.get(by, bx, 2, 0)) * localAtkPts;
			result += std::min(std::max(temp, -localAtkLim), localAtkLim);
		}
	}
	return result;
}

void EdgeBot::modEvals(std::vector<EvalMove>& evals)
{
	for (EvalMove& eval : evals) {
		eval.eval = std::min(std::max(eval.eval, -EVAL_MAX), EVAL_MAX);
	}
}

int EdgeBot::k(const Cell& cell) const
{
	switch (cell) {
	case Cell::Empty:
		return 0;
	case Cell::Cross:
		return 1;
	case Cell::Null:
		return -1;
	case Cell::Any:
		return 0;
	default:
		return 0;
	}
}

int EdgeBot::atk(const Cell& a, const Cell& b, const Cell& c) const
{
	int v = k(a) + k(b) + k(c);
	if (v == 2) {
		return 1;
	}
	if (v == -2) {
		return -1;
	}
	return 0;
}