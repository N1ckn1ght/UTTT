#pragma once
#include "GlobalCoord.h"

class EvalMove {
public:
	GlobalCoord move;
	double eval;

	EvalMove(GlobalCoord move_, double eval_ = 0);
};

extern bool evalMoveCmp(EvalMove a, EvalMove b);