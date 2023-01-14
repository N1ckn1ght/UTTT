#pragma once
#include <cstddef>

class GlobalCoord {
public:
	size_t by;
	size_t bx;
	size_t y;
	size_t x;

	GlobalCoord(size_t by_ = -1, size_t bx_ = -1, size_t y_ = -1, size_t x_ = -1);

	friend bool operator == (const GlobalCoord& lhs, const GlobalCoord& rhs);
};