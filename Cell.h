#pragma once

enum class Cell {
	Cross,
	Null,
	Empty,
	Any
};

extern Cell nextCell(const Cell cell);