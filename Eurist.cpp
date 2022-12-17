#include "Eurist.h"
#include <vector>

Eurist::Eurist(size_t lines_, float k_, bool debug_, 
	bool zTweaks_, 
	float positiveZBump_, float negativeZBump_, float positiveCTweak_, float negativeCTweak_, 
	bool bTweaks_, 
	float positiveBoardCentralDW_, float positiveBoardDiagDW_, float positiveBoardSideDW_, 
	float negativeBoardCentralDW_, float negativeBoardDiagDW_, float negativeBoardSideDW_)
{
	lines = lines_;
	k = k_;
	debug = debug_;

	ratios = nullptr;
	possible = nullptr;
	count = nullptr;
	positionalMult = nullptr;
	countAll = 0;
	moves = 0;

	zTweaks = zTweaks_;
	positiveZBump = positiveZBump_;
	negativeZBump = negativeZBump_;
	positiveCTweak = positiveCTweak_;
	negativeCTweak = negativeCTweak_;

	bTweaks = bTweaks_;
	positiveBoardCentralDW = positiveBoardCentralDW_;
	positiveBoardDiagDW = positiveBoardDiagDW_;
	positiveBoardSideDW = positiveBoardSideDW_;
	negativeBoardCentralDW = negativeBoardCentralDW_;
	negativeBoardDiagDW = negativeBoardDiagDW_;
	negativeBoardSideDW = negativeBoardSideDW_;
}

Eurist::~Eurist()
{
	clearArrays();
}

std::vector <EuristMove> Eurist::eval(Field& field)
{
	clear();
	init(field);

	Coord lastMove = field.getLastMove();
	std::vector <EuristMove> euristMoves;

	if (lastMove.y == -1 || field.adjudicatedFor(lastMove.y, lastMove.x) != Cell::Empty) {
		size_t totalPossibleMoves = 0;
		for (size_t by = 0; by < 3; by++) {
			for (size_t bx = 0; bx < 3; bx++) {
				totalPossibleMoves += count[by][bx];
			}
		}
		for (size_t by = 0; by < 3; by++) {
			for (size_t bx = 0; bx < 3; bx++) {
				eval(field, by, bx, euristMoves, size_t(float(lines) * k / totalPossibleMoves), field.getTurn());
			}
		}
		moves += totalPossibleMoves;

		if (debug) {
			std::cout << "Eurist: Total random non-unique moves made: " << moves << ".\n";
		}
	}
	else {
		eval(field, lastMove.y, lastMove.x, euristMoves, lines / count[lastMove.y][lastMove.x], field.getTurn());
		moves += count[lastMove.y][lastMove.x];

		if (debug) {
			std::cout << "Eurist: Total random non-unique moves made: " << moves << ".\n";
		}
	}

	sort(euristMoves.begin(), euristMoves.end(), euristMoveCmp);
	return euristMoves;
}

void Eurist::eval(Field& field, const size_t by, const size_t bx, std::vector<EuristMove>& euristMoves, size_t lines_, Cell side)
{
	// Make custom field
	Field field_;

	for (size_t i = 0; i < count[by][bx]; i++) {
		for (size_t j = 0; j < lines_; j++) {
			// Set field copy
			for (size_t iby = 0; iby < 3; iby++) {
				for (size_t ibx = 0; ibx < 3; ibx++) {
					for (size_t iy = 0; iy < 3; iy++) {
						for (size_t ix = 0; ix < 3; ix++) {
							field_.set(iby, ibx, iy, ix, field.get(iby, ibx, iy, ix));
						}
					}
					field_.setBoard(iby, ibx, field.getBoard(iby, ibx));
				}
			}
			field_.setTurn(field.getTurn());
			field_.setLastMove(field.getLastMove());
			field_.setLastBoard(field.getLastBoard());

			// Make possible moves copy
			size_t countAll_ = countAll;
			size_t** count_ = new size_t * [3];
			Coord*** possible_ = new Coord * *[3];
			for (size_t iby = 0; iby < 3; iby++) {
				count_[iby] = new size_t[3];
				possible_[iby] = new Coord * [3];
				for (size_t ibx = 0; ibx < 3; ibx++) {
					count_[iby][ibx] = count[iby][ibx];
					possible_[iby][ibx] = new Coord[9];
					for (size_t k = 0; k < count_[iby][ibx]; k++) {
						possible_[iby][ibx][k] = possible[iby][ibx][k];
					}
				}
			}

			// Make certain possible[by][bx][i] move
			field_.insert(by, bx, possible[by][bx][i].y, possible[by][bx][i].x);
			size_t b2y = by;
			size_t b2x = bx;
			size_t move = i;

			// Continue by playing random game 'til it's possible
			Cell winner = field_.adjudicate();
			while (winner == Cell::Empty) {
				moves++;
				if (field_.adjudicatedFor(b2y, b2x) != Cell::Empty) {
					countAll_ -= count_[b2y][b2x];
					count_[b2y][b2x] = 0;
				}
				else {
					std::swap(possible_[b2y][b2x][move], possible_[b2y][b2x][--count_[b2y][b2x]]);
					countAll_--;
				}
		
				b2y = field_.getLastMove().y;
				b2x = field_.getLastMove().x;

				// Case: the next move must be done anywhere but the specific field
				// Worth mentioning, this must work the same as: if (field_.nextMoveIsAnywhere()) condition
				if (!count_[b2y][b2x]) {
					
					// This is also where 'AnyMove' positional tweak comes into play
					if (zTweaks) {
						if (field_.getTurn() == side) {
							positionalMult[by][bx][i] += positiveZBump;
						}
						else {
							positionalMult[by][bx][i] -= negativeZBump;
						}
					}

					// Weights for certain boards
					if (bTweaks) {
						if (field_.adjudicatedFor(b2y, b2x) == side) {
							if (b2y == b2x) {
								if (b2y == 1) {
									ratios[by][bx][possible[by][bx][i].y][possible[by][bx][i].x].addRatio(positiveBoardCentralDW, 1);
								}
								else {
									ratios[by][bx][possible[by][bx][i].y][possible[by][bx][i].x].addRatio(positiveBoardDiagDW, 1);
								}
							}
							else if ((b2y == 0 && b2x == 2) || (b2y == 2 && b2x == 0)) {
								ratios[by][bx][possible[by][bx][i].y][possible[by][bx][i].x].addRatio(positiveBoardDiagDW, 1);
							}
							else {
								ratios[by][bx][possible[by][bx][i].y][possible[by][bx][i].x].addRatio(positiveBoardSideDW, 1);
							}
						}
						else if (field_.adjudicatedFor(b2y, b2x) == nextCell(side)) {
							if (b2y == b2x) {
								if (b2y == 1) {
									ratios[by][bx][possible[by][bx][i].y][possible[by][bx][i].x].addRatio(negativeBoardCentralDW, 1);
								}
								else {
									ratios[by][bx][possible[by][bx][i].y][possible[by][bx][i].x].addRatio(negativeBoardDiagDW, 1);
								}
							}
							else if ((b2y == 0 && b2x == 2) || (b2y == 2 && b2x == 0)) {
								ratios[by][bx][possible[by][bx][i].y][possible[by][bx][i].x].addRatio(negativeBoardDiagDW, 1);
							}
							else {
								ratios[by][bx][possible[by][bx][i].y][possible[by][bx][i].x].addRatio(negativeBoardSideDW, 1);
							}
						}
					}

					// Finally, make a move from all possible random moves
					move = rand() % countAll_;
					bool dropped = false;
					while (!dropped) {
						for (size_t cy = 0; cy < 3; cy++) {
							for (size_t cx = 0; cx < 3; cx++) {
								if (move < count_[cy][cx]) {
									b2y = cy;
									b2x = cx;
									dropped = true;
									break;
								}
								move -= count_[cy][cx];
							}
						}
					}
				}
				else {
					move = rand() % count_[b2y][b2x];
				}

				field_.insert(b2y, b2x, possible_[b2y][b2x][move].y, possible_[b2y][b2x][move].x);
				// while it isn't winning for someone or a dead draw
				winner = field_.adjudicate();
			}

			// Add the outcome to probability of making possible[by][bx][i] move
			if (winner == side) {
				ratios[by][bx][possible[by][bx][i].y][possible[by][bx][i].x].addResult(Result::Win);
			}
			else if (winner == nextCell(side)) {
				ratios[by][bx][possible[by][bx][i].y][possible[by][bx][i].x].addResult(Result::Loss);
			}
			else {
				ratios[by][bx][possible[by][bx][i].y][possible[by][bx][i].x].addResult(Result::Draw);
			}
		}
	}

	for (size_t i = 0; i < count[by][bx]; i++) {
		size_t y = possible[by][bx][i].y;
		size_t x = possible[by][bx][i].x;
		float chance = ratios[by][bx][y][x].getChance();

		if (zTweaks) {
			if (positiveCTweak) {
				for (size_t j = 0; j < positionalMult[by][bx][i]; j++) {
					chance += (1 - chance) * positiveCTweak;
				}
			}
			if (negativeCTweak) {
				for (size_t j = 0; j < -positionalMult[by][bx][i]; j++) {
					chance -= chance * negativeCTweak;
				}
			}
		}

		euristMoves.push_back(EuristMove(by, bx, y, x, chance, i));
	}
}

void Eurist::clear()
{
	countAll = 0;
	moves = 0;
	clearArrays();
}

void Eurist::clearArrays()
{
	if (ratios) {
		for (size_t by = 0; by < 3; by++) {
			for (size_t bx = 0; bx < 3; bx++) {
				for (size_t y = 0; y < 3; y++) {
					delete[] ratios[by][bx][y];
				}
				delete[] ratios[by][bx];
			}
			delete[] ratios[by];
		}
		delete[] ratios;
		ratios = nullptr;
	}
	if (count) {
		for (size_t by = 0; by < 3; by++) {
			delete[] count[by];
		}
		delete[] count;
		count = nullptr;
	}
	if (possible) {
		for (size_t by = 0; by < 3; by++) {
			for (size_t bx = 0; bx < 3; bx++) {
				delete[] possible[by][bx];
			}
			delete[] possible[by];
		}
		delete[] possible;
		possible = nullptr;
	}
	if (positionalMult) {
		for (size_t by = 0; by < 3; by++) {
			for (size_t bx = 0; bx < 3; bx++) {
				delete[] positionalMult[by][bx];
			}
			delete[] positionalMult[by];
		}
		delete[] positionalMult;
		positionalMult = nullptr;
	}
}

void Eurist::init(Field& field)
{
	ratios = new Ratio***[3];
	count = new size_t*[3];
	possible = new Coord**[3];
	positionalMult = new float**[3];
	for (size_t by = 0; by < 3; by++) {
		ratios[by] = new Ratio**[3];
		count[by] = new size_t[3];
		possible[by] = new Coord*[3];
		positionalMult[by] = new float*[3];
		for (size_t bx = 0; bx < 3; bx++) {
			ratios[by][bx] = new Ratio*[3];
			count[by][bx] = 0;
			possible[by][bx] = new Coord[9];
			positionalMult[by][bx] = new float[9];
			for (size_t y = 0; y < 3; y++) {
				ratios[by][bx][y] = new Ratio[3];
				for (size_t x = 0; x < 3; x++) {
					ratios[by][bx][y][x] = Ratio();
					if (field.get(by, bx, y, x) == Cell::Empty) {
						possible[by][bx][count[by][bx]] = Coord(y, x);
						positionalMult[by][bx][count[by][bx]] = 1;
						count[by][bx]++;
					}
				}
			}
			countAll += count[by][bx];
		}
	}
}

size_t Eurist::getMoves()
{
	return moves;
}