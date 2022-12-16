#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "Cell.h"
#include "Eurist.h"
#include "EuristMove.h"
#include "Field.h"

using namespace std;

string getSide(Cell side) {
	if (side == Cell::Cross) {
		return "CROSS";
	}
	if (side == Cell::Null) {
		return "NULLS";
	}
	return "\n\n[This is a bug. Please, report it to UTTT GitHub! Such a shame...]\n[Also consider Ctrl+A Ctrl+C Ctrl+V your console output!]\n\n";
}

//void firstMoveByPlayer(Field& field) {
//	cout << "You're playing as CROSS. Make first move anywhere!\n\n" << field;
//	size_t by, bx, y, x;
//	bool success = false;
//	do {
//		cout << "\nInput: {board X (0-2)} {board Y (0-2)} {X (0-2)} {Y (0-2)}, from left-top to right-bottom.\n\n";
//		cin >> bx >> by >> x >> y;
//		success = field.insert(by, bx, y, x);
//	} while (!success);
//}

void printEuristAnalysis(Field& field, size_t lines, float k) {
	Eurist eurist(lines, k, false);
	vector <EuristMove> moves = eurist.eval(field);
	size_t amount = min(moves.size(), size_t(9));
	cout << "\nTop " << amount << " Eurist moves:\n";
	for (size_t i = 0; i < amount; i++) {
		if (field.nextMoveIsAnywhere()) {
			cout << "(" << (moves[i].bx + 1) << ", " << (moves[i].by + 1) << ", " << (moves[i].x + 1) << ", " << (moves[i].y + 1) << ")\t with " << size_t(moves[i].chance * 100) << "% chance of winning.\n";
		}
		else {
			cout << "(" << (moves[i].x + 1) << ", " << (moves[i].y + 1) << ")\t with " << size_t(moves[i].chance * 100) << "% chance of winning.\n";
		}
	}
	cout << "\n";
}

//void euristMakeMove(Field& field, Eurist& eurist) {
//	vector <EuristMove> moves = eurist.eval(field);
//	size_t amount = min(moves.size(), size_t(9));
//	cout << "\nTop " << amount << " Eurist moves:\n";
//	for (size_t i = 0; i < amount; i++) {
//		cout << "(" << moves[i].bx << ", " << moves[i].by << ", " << moves[i].x << ", " << moves[i].y << ")\t with " << size_t(moves[i].chance * 100) << "% chance of winning.\n";
//	}
//	cout << "\n";
//	field.insert(moves[0].by, moves[0].bx, moves[0].y, moves[0].x);
//}

void playerVsPlayer(Field& field, bool analysisMode = false, size_t analysisLines = 0, size_t analysisK = 0) {
	size_t by, bx, y, x;
	bool success;

	while (true) {
		if (analysisMode) {
			printEuristAnalysis(field, analysisLines, analysisK);
		}

		success = false;
		if (field.nextMoveIsAnywhere()) {
			cout << field << "\n" << getSide(field.getTurn()) << " turn on ANY board!\n";
			do {
				cout << "Input: {board X (1-3)} {board Y (1-3)} {X (1-3)} {Y (1-3)}, from left-top to right-bottom.\n\n";
				cin >> bx >> by >> x >> y;
				success = field.insert(--by, --bx, --y, --x);
			} while (!success);
		}
		else {
			cout << field << "\n" << getSide(field.getTurn()) << " turn on (" << field.getLastMove().x + 1 << ", " << field.getLastMove().y + 1 << ") board.\n";
			do {
				cout << "Input: {X (1-3)} {Y (1-3)} from left-top.\n\n";
				cin >> x >> y;
				success = field.insert(field.getLastMove().y, field.getLastMove().x, --y, --x);
			} while (!success);
		}

		Cell winner = field.adjudicate();
		if (winner == Cell::Cross) {
			cout << field << "CROSS won this game. GG!\n";
			return;
		}
		if (winner == Cell::Null) {
			cout << field << "NULLS won this game. GG!\n";
			return;
		}
		if (winner == Cell::Any) {
			cout << field << "Round draw. Fantastic!!\n";
			return;
		}
	}
}

//void playerVsBot(Field& field, Eurist& eurist, bool playerMovesFirst) {
//	size_t y, x;
//	bool success;
//
//	if (playerMovesFirst) {
//		firstMoveByPlayer(field);
//	}
//	else {
//		euristMakeMove(field, eurist);
//	}
//
//	while (true) {
//		if (playerMovesFirst) {
//			cout << field << "\nNULLS turn on " << field.getLastMove().x << ", " << field.getLastMove().y << " board!\n";
//			euristMakeMove(field, eurist);
//
//			if (field.adjudicate() == Cell::Null) {
//				cout << field << "Eurist won this game with NULLS. Such a divine intellect!\n";
//				return;
//			}
//			if (field.adjudicate() == Cell::Any) {
//				cout << field << "Round draw. Fantastic!\n";
//				return;
//			}
//
//			cout << field << "\nCROSS turn on " << field.getLastMove().x << ", " << field.getLastMove().y << " board!\n";
//			success = false;
//			do {
//				cout << "Input: {X (0-2)} {Y (0-2)} from left-top.\n\n";
//				cin >> x >> y;
//				success = field.insert(y, x);
//			} while (!success);
//
//			if (field.adjudicate() == Cell::Cross) {
//				cout << field << "Player won this game with CROSS. Thank you for playing!\n";
//				return;
//			}
//			if (field.adjudicate() == Cell::Any) {
//				cout << field << "Round draw. Fantastic!\n";
//				return;
//			}
//		}
//		else {
//			cout << field << "\nNULLS turn on " << field.getLastMove().x << ", " << field.getLastMove().y << " board!\n";
//			success = false;
//			do {
//				cout << "Input: {X (0-2)} {Y (0-2)} from left-top.\n\n";
//				cin >> x >> y;
//				success = field.insert(y, x);
//			} while (!success);
//
//			if (field.adjudicate() == Cell::Null) {
//				cout << field << "Player won this game with NULLS. Well done!\n";
//				return;
//			}
//			if (field.adjudicate() == Cell::Any) {
//				cout << field << "Round draw. Fantastic!\n";
//				return;
//			}
//
//			cout << field << "\nCROSS turn on " << field.getLastMove().x << ", " << field.getLastMove().y << " board!\n";
//			euristMakeMove(field, eurist);
//
//			if (field.adjudicate() == Cell::Cross) {
//				cout << field << "Eurist won this game with CROSS. No chances for humanity!\n";
//				return;
//			}
//			if (field.adjudicate() == Cell::Any) {
//				cout << field << "Round draw. Fantastic!\n";
//				return;
//			}
//		}
//	}
//}

int main(int argc, wchar_t* argv[]) {
	srand(time(0));
	Field field;
	Eurist eurist(27000, 2.5, true);

	char input = '0';
	do {
		cout << "Please, select a gamemode\n\n1 - Two players\n2 - Two players with Eurist analysis\n";
		cout << "3 - Play Vs Eurist Bot as CROSS\n4 - Play Vs Eurist Bot as NULLS\n";
		cout << "5 - Play Vs Eurist Bot as CROSS with custom params\n6 - Play Vs Eurist Bot as NULLS with custom params\n\n";
		cin >> input;
	} while (input < '1' or input > '6');
	system("CLS");

	if (input == '1') {
		playerVsPlayer(field, false);
	}
	else if (input == '2') {
		size_t lines;
		float k;
		bool debug;
		cout << "Input (unsigned int) lines, (Float) k:\n";
		cout << "This is basically a strength of the analysis.\n";
		cout << "Recommended params for now: 25000 4\n\n";
		cin >> lines >> k;

		playerVsPlayer(field, true, 25000, 4);
	}
	//else if (input == '3') {
	//	playerVsBot(field, eurist, true);
	//}
	//else if (input == '4') {
	//	playerVsBot(field, eurist, false);
	//}

	//else if (input == '5') {
	//	size_t lines;
	//	float k;
	//	bool debug;
	//	cout << "Input (unsigned int) lines, (Float) k, (bool) debug:\n\n";
	//	cin >> lines >> k >> debug;
	//	Eurist eurist(lines, k, debug);
	//	playerVsBot(field, eurist, true);
	//}
	//else if (input == '6') {
	//	size_t lines;
	//	float k;
	//	bool debug;
	//	cout << "Input (unsigned int) lines, (Float) k, (bool) debug:\n\n";
	//	cin >> lines >> k >> debug;
	//	Eurist eurist(lines, k, debug);
	//	playerVsBot(field, eurist, false);
	//}

	cout << "\nInput any symbol to kill this app.\n";
	cin.get();
	cin.get();
}