#include "EuristMove.h"

EuristMove::EuristMove(size_t by_, size_t bx_, size_t y_, size_t x_, Ratio chance_)
{
	by = by_;
	bx = bx_;
	y = y_;
	x = x_;
	chance = chance_.getChance();
}

bool euristMoveCmp(EuristMove a, EuristMove b)
{
	return a.chance > b.chance;
}