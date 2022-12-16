#include "Cell.h"

Cell nextCell(const Cell cell)
{
	if (cell == Cell::Cross) {
		return Cell::Null;
	}
	if (cell == Cell::Null) {
		return Cell::Cross;
	}
	return Cell::Empty;
}

Cell wonCell(const Cell cell)
{
	if (cell == Cell::Cross) {
		return Cell::Cwon;
	}
	if (cell == Cell::Null) {
		return Cell::Nwon;
	}
	return Cell::Any;
}