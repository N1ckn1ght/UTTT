#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "Cell.h"
#include "Eurist.h"
#include "EuristMove.h"
#include "Field.h"

using namespace std;

Eurist getEurist() {
	size_t lines;
	float k, pzb, nzb, pct, nct, pbcd, pbdd, pbsd, nbcd, nbdd, nbsd;
	bool debug, zTweaks, bTweaks;
	cout << "Input (unsigned int) lines, (float) k, (bool) debug, (bool) zTweaks, (float) positiveZBump, (float) negativeZBump, (float) positiveCTweak, (float) negativeCTweak, (bool) bTweaks, (float) positiveBoardCentralDW, (float) positiveBoardDiagDW, (float) positiveBoardSideDW, (float) negativeBoardCentralDW, (float) negativeBoardDiagDW, (float) negativeBoardSideDW:\n";
	cin >> lines >> k >> debug >> zTweaks >> pzb >> nzb >> pct >> nct >> bTweaks >> pbcd >> pbdd >> pbsd >> nbcd >> nbdd >> nbsd;
	return Eurist(lines, k, debug, zTweaks, pzb, nzb, pct, nct, bTweaks, pbcd, pbdd, pbsd, nbcd, nbdd, nbsd);
}

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

void botVsBot(Field& field, Eurist& eurist1, Eurist& eurist2, bool eurist1First = true)
{
	while (true) {
		if (field.nextMoveIsAnywhere()) {
			cout << field << "\n" << getSide(field.getTurn()) << " turn on ANY board!\n";
		}
		else {
			cout << field << "\n" << getSide(field.getTurn()) << " turn on (" << field.getLastMove().x + 1 << ", " << field.getLastMove().y + 1 << ") board.\n";
		}

		if (eurist1First) {
			printEuristAnalysis(field, eurist1, true);
		}

		else {
			printEuristAnalysis(field, eurist2, true);
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
		eurist1First = !eurist1First;
	}
}

int main(int argc, wchar_t* argv[]) {
	srand(time(0));
	Field field;

	//zTweaks + bTweaks, conf1
	// Eurist customEurist1(13500, 3.75, 1, 1, 0, 1, 0, 0.00001, 1, 0.625, 0.59375, 0.5625, 0.4375, 0.40625, 0.375);
	//zTweaks
	// Eurist customEurist2(13500, 3.75, 1, 1, 1, 1, 0, 0.001, 0);
	//Vanilla
	// Eurist customEurist3(13500, 3.75, 1);
	//bTweaks
	// Eurist customEurist4(13500, 3.75, 1, 0, 0, 0, 0, 0, 1, 0.625, 0.59375, 0.5625, 0.4375, 0.40625, 0.375);
	//zTweaks + bTweaks, conf0
	// Eurist customEurist5(13500, 3.75, 1, 1, 1, 1, 0, 0.001, 1, 0.625, 0.59375, 0.5625, 0.4375, 0.40625, 0.375);
	//zTweaks 0.002
	// Eurist customEurist6(13500, 3.75, 1, 1, 1, 1, 0, 0.002, 0);
	//zTweaks +fb
	// Eurist customEurist7(10000, 8, 1, 1, 1, 1, 0, 0.001, 0);
	//zTweaks low precision
	// Eurist customEurist8(1350, 3.75, 1, 1, 1, 1, 0, 0.001, 0);

	Eurist defaultEurist(21000, 4.2, 1, 1, 1, 1, 0, 0.001, 0);

	char input = '0';
	do {
		cout << "Please, select a gamemode\n\n";
		cout << "1 - Two players\n2 - Two players with Eurist analysis\n";
		cout << "3 - Play Vs Eurist Bot as CROSS\n";
		cout << "4 - Play Vs Eurist Bot as NULLS\n";
		cout << "5 - Play Vs Eurist Bot as CROSS with custom params\n";
		cout << "6 - Play Vs Eurist Bot as NULLS with custom params\n";
		cout << "7 - Watch Eurist Bot vs Eurist Bot game with different params!\n\n";
		cin >> input;
		cout << "\n";
	} while (input < '1' or input > '7');
	system("CLS");

	if (input == '1') {
		playerVsPlayer(field, defaultEurist, false);
	}
	else if (input == '2') {
		playerVsPlayer(field, defaultEurist, true);
	}
	else if (input == '3') {
		playerVsBot(field, defaultEurist, true);
	}
	else if (input == '4') {
		playerVsBot(field, defaultEurist, false);
	}
	else if (input == '5') {
		Eurist customEurist = getEurist();
		playerVsBot(field, customEurist, true);
	}
	else if (input == '6') {
		Eurist customEurist = getEurist();
		playerVsBot(field, customEurist, false);
	}
	else if (input == '7') {
		Eurist customEurist1 = getEurist();
		Eurist customEurist2 = getEurist();
		botVsBot(field, customEurist1, customEurist2, true);
	}

	cout << "\nInput any symbol to kill this app.\n";
	cin.get();
	cin.get();
}