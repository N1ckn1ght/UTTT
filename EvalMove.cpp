#include "EvalMove.h"

EvalMove::EvalMove(GlobalCoord move_, double eval_)
{
	move = move_;
	eval = eval_;
}

bool evalMoveCmp(EvalMove a, EvalMove b)
{
	return a.eval > b.eval;
}