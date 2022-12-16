#pragma once
#include "Ratio.h"

class EuristMove {
public:
	size_t by;
	size_t bx;
	size_t y;
	size_t x;
	float chance;

	EuristMove(size_t by_, size_t bx_, size_t y_, size_t x_, Ratio chance_);
};

extern bool euristMoveCmp(EuristMove a, EuristMove b);