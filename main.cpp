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

void printEuristAnalysis(Field& field, Eurist& eurist, bool makeMove = false) {
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
	if (makeMove) {
		if (moves[0].chance == 1) {
			cout << "Eurist: Thank you for game, my human friend.\nEurist: Last move: (" << (moves[0].bx + 1) << ", " << (moves[0].by + 1) << ", " << (moves[0].x + 1) << ", " << (moves[0].y + 1) << ")\n\n";
		}
		else if (moves[0].chance > 0.7) {
			cout << "Eurist: My victory is ineviatble now.\nEurist: Best move: (" << (moves[0].bx + 1) << ", " << (moves[0].by + 1) << ", " << (moves[0].x + 1) << ", " << (moves[0].y + 1) << ")\n\n";
		}
		else if (moves[0].chance > 0.6) {
			cout << "Eurist: I REALLY like my chances!\nEurist: I think I need to move on (" << (moves[0].bx + 1) << ", " << (moves[0].by + 1) << ", " << (moves[0].x + 1) << ", " << (moves[0].y + 1) << ")\n\n";
		}
		else if (moves[0].chance > 0.55) {
			cout << "Eurist: I am in kinda better position I suppose...!\nEurist: Move on (" << (moves[0].bx + 1) << ", " << (moves[0].by + 1) << ", " << (moves[0].x + 1) << ", " << (moves[0].y + 1) << ")\n\n";
		}
		else if (moves[0].chance > 0.45) {
			cout << "Eurist: We are probably equal rn.\nEurist: My next move: (" << (moves[0].bx + 1) << ", " << (moves[0].by + 1) << ", " << (moves[0].x + 1) << ", " << (moves[0].y + 1) << ")\n\n";
		}
		else if (moves[0].chance > 0.40) {
			cout << "Eurist: It's alright, I still can draw this! Maybe...\nEurist: I should move on (" << (moves[0].bx + 1) << ", " << (moves[0].by + 1) << ", " << (moves[0].x + 1) << ", " << (moves[0].y + 1) << ")\n\n";
		}
		else if (moves[0].chance > 0.30) {
			cout << "Eurist: I really dislike my chances now, seems like the battle is almost over.\nEurist: Move: (" << (moves[0].bx + 1) << ", " << (moves[0].by + 1) << ", " << (moves[0].x + 1) << ", " << (moves[0].y + 1) << ")\n\n";
		}
		else {
			cout << "Eurist: Do you accept surrenderers?\nEurist: My move...: (" << (moves[0].bx + 1) << ", " << (moves[0].by + 1) << ", " << (moves[0].x + 1) << ", " << (moves[0].y + 1) << ")\n\n";
		}

		field.insert(moves[0].by, moves[0].bx, moves[0].y, moves[0].x);
	}
}

void playerVsPlayer(Field& field, Eurist& analysis, bool analysisMode = false) {
	size_t by, bx, y, x;
	bool success;

	while (true) {
		if (analysisMode) {
			printEuristAnalysis(field, analysis);
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

void playerVsBot(Field& field, Eurist& eurist, bool playerMovesFirst) {
	size_t by, bx, y, x;
	bool success;

	while (true) {
		success = false;

		if (field.nextMoveIsAnywhere()) {
			cout << field << "\n" << getSide(field.getTurn()) << " turn on ANY board!\n";
		}
		else {
			cout << field << "\n" << getSide(field.getTurn()) << " turn on (" << field.getLastMove().x + 1 << ", " << field.getLastMove().y + 1 << ") board.\n";
		}

		if (playerMovesFirst) {
			if (field.nextMoveIsAnywhere()) {
				do {
					cout << "Input: {board X (1-3)} {board Y (1-3)} {X (1-3)} {Y (1-3)}, from left-top to right-bottom.\n\n";
					cin >> bx >> by >> x >> y;
					success = field.insert(--by, --bx, --y, --x);
				} while (!success);
			}
			else {
				do {
					cout << "Input: {X (1-3)} {Y (1-3)} from left-top.\n\n";
					cin >> x >> y;
					success = field.insert(field.getLastMove().y, field.getLastMove().x, --y, --x);
				} while (!success);
			}
		}

		else {
			printEuristAnalysis(field, eurist, true);
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
		playerMovesFirst = !playerMovesFirst;
	}
}

int main(int argc, wchar_t* argv[]) {
	srand(time(0));
	Field field;
	Eurist defaultEurist(18000, 4, 1, 1);

	char input = '0';
	do {
		cout << "Please, select a gamemode\n\n1 - Two players\n2 - Two players with Eurist analysis\n";
		cout << "3 - Play Vs Eurist Bot as CROSS\n4 - Play Vs Eurist Bot as NULLS\n";
		cout << "5 - Play Vs Eurist Bot as CROSS with custom params\n6 - Play Vs Eurist Bot as NULLS with custom params\n\n";
		cin >> input;
	} while (input < '1' or input > '6');
	system("CLS");

	if (input == '1') {
		playerVsPlayer(field, defaultEurist, false);
	}
	else if (input == '2') {
		size_t lines;
		float k;
		bool debug, tweak;
		cout << "Input (unsigned int) lines, (float) k, (float) k2, (bool) debug, (bool) tweak:\n";
		cout << "This is basically the strength of the analysis.\n";
		cout << "Recommended params for now: 18000 4 0 1\n\n";
		cin >> lines >> k >> debug >> tweak;
		Eurist customEurist(lines, k, debug, tweak);
		playerVsPlayer(field, customEurist, true);
	}
	else if (input == '3') {
		playerVsBot(field, defaultEurist, true);
	}
	else if (input == '4') {
		playerVsBot(field, defaultEurist, false);
	}
	else if (input == '5') {
		size_t lines;
		float k;
		bool debug, tweak;
		cout << "Input (unsigned int) lines, (float) k, (float) k2, (bool) debug, (bool) tweak:\n";
		cout << "This is basically the strength of the analysis.\n";
		cout << "Recommended params for now: 18000 4 0 1\n\n";
		cin >> lines >> k >> debug >> tweak;
		Eurist customEurist(lines, k, debug, tweak);
		playerVsBot(field, customEurist, true);
	}
	else if (input == '6') {
		size_t lines;
		float k;
		bool debug, tweak;
		cout << "Input (unsigned int) lines, (float) k, (float) k2, (bool) debug, (bool) tweak:\n";
		cout << "This is basically the strength of the analysis.\n";
		cout << "Recommended params for now: 18000 4 0 1\n\n";
		cin >> lines >> k >> debug >> tweak;
		Eurist customEurist(lines, k, debug, tweak);
		playerVsBot(field, customEurist, false);
	}

	cout << "\nInput any symbol to kill this app.\n";
	cin.get();
	cin.get();
}