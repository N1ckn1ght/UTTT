#pragma once
#include "Ratio.h"

class EuristMove {
public:
	size_t by;
	size_t bx;
	size_t y;
	size_t x;
	float chance;
	// thir is only for making recursive deep search a lil' bit faster
	size_t moveId;

	EuristMove(size_t by_, size_t bx_, size_t y_, size_t x_, float chance_, size_t moveId_ = -1);
};

extern bool euristMoveCmp(EuristMove a, EuristMove b);