#pragma once

enum class Cell {
	Cross,
	Null,
	Empty,
	Any,	// this is for draw scenario
	Cwon,	// this is for scenario of a won board as cross
	Nwon	// this is for scenario of a won board as nulls
};

extern Cell nextCell(const Cell cell);
extern Cell wonCell(const Cell cell);