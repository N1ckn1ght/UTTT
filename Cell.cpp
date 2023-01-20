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