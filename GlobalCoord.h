#pragma once
#include <iostream>
#include <cstddef>

class GlobalCoord {
public:
	size_t by;
	size_t bx;
	size_t y;
	size_t x;

	GlobalCoord(size_t by_ = -1, size_t bx_ = -1, size_t y_ = -1, size_t x_ = -1);

	friend bool operator == (const GlobalCoord& lhs, const GlobalCoord& rhs);
	// Note: output format is (bx + 1, by + 1, x + 1, y + 1), not (by, bx, y, x)!
	friend std::ostream& operator << (std::ostream& out, const GlobalCoord& gc);
};