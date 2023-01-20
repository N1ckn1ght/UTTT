#include "Coord.h"

Coord::Coord(size_t y_, size_t x_)
{
	y = y_;
	x = x_;
}

bool operator == (const Coord &lhs, const Coord &rhs)
{
    return (lhs.y == rhs.y && lhs.x == rhs.x);
}