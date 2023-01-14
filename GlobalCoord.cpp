#include "GlobalCoord.h"

GlobalCoord::GlobalCoord(size_t by_, size_t bx_, size_t y_, size_t x_)
{
	by = by_;
	bx = bx_;
	y = y_;
	x = x_;
}

bool operator==(const GlobalCoord &lhs, const GlobalCoord &rhs)
{
    return (lhs.by == rhs.by && lhs.bx == rhs.bx && lhs.y == rhs.y && lhs.x == rhs.x);
}