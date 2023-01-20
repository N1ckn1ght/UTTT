#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Field.h"
#include "EdgeBot_v1_0.h"
#include "EdgeBot_v1_1.h"

using namespace std;

char getSide(Cell cell) {
	switch (cell) {
	case Cell::Cross:
		return 'X';
	case Cell::Null:
		return 'O';
	default:
		return '_';
	}
	return 0;
}

size_t getRandomTopMove(std::vector <EvalMove>& evals, double margin) {
	size_t count = 1;
	double topEval = evals[0].eval;
	for (size_t i = 1; i < evals.size(); i++) {
		if (std::abs(topEval - evals[i].eval) <= margin) {
			count++;
		}
		else {
			break;
		}
	}
	return rand() % count;
}

void playerVsPlayer(Field& field, bool analyze, bool reverts) {
	EdgeBot_v1_1 edgeBot;
	size_t by, bx, y, x;
	bool success;

	while (true) {
		if (analyze) {
			vector <EvalMove> evals = edgeBot.eval(field, 6);
			cout << "\nEdgeBot: here's my top " << min(evals.size(), (size_t)9) << " of possible moves:\n";
			for (size_t i = 0; i < min(evals.size(), (size_t)9); i++) {
				cout << (i + 1) << ". " << evals[i].move << ": " << evals[i].eval << "\n";
			}
		}

		success = false;
		if (field.getNextBoard().y == -1) {
			cout << field << getSide(field.getTurn()) << " turn on ANY board!\n";
		} 
		else {
			cout << field << getSide(field.getTurn()) << " turn on (" << (field.getNextBoard().x) + 1 << ", " << (field.getNextBoard().y) + 1 << ") board!\n";
		}
		do {
			cout << "Input: bx by x y\n\n";
			cin >> bx >> by >> x >> y;
			cout << "\n";

			if (bx == -1 && reverts) {
				field.revert();
				cout << "\n1 MOVE WAS CANCELLED.\nIt's " << getSide(field.getTurn()) << " to move now!\n" << field;
				continue;
			}

			success = field.isLegalMove(--by, --bx, --y, --x);
		} while (!success);

		field.move(by, bx, y, x);
		switch (field.getWinner()) {
		case Cell::Cross:
			cout << field << "CROSS won this game. GG!\n";
			return;
		case Cell::Null:
			cout << field << "NULLS won this game. GG!\n";
			return;
		case Cell::Any:
			cout << field << "Round draw. Incredible!\n";
			return;
		default:
			break;
		}
	}
}

void playerVsEdge(Field& field, size_t depth, double margin, bool pcross, bool analyze, bool reverts) {
	EdgeBot_v1_1 edgeBot;
	size_t by, bx, y, x;
	bool success;

	while (true) {
		success = false;
		if (field.getNextBoard().y == -1) {
			cout << field << getSide(field.getTurn()) << " turn on ANY board!\n";
		}
		else {
			cout << field << getSide(field.getTurn()) << " turn on (" << (field.getNextBoard().x) + 1 << ", " << (field.getNextBoard().y) + 1 << ") board!\n";
		}

		if (pcross) {
			do {
				cout << "Input: bx by x y\n\n";
				cin >> bx >> by >> x >> y;
				cout << "\n";
				
				if (bx == -1 && reverts) {
					field.revert();
					field.revert();
					cout << "\n2 MOVES WERE CANCELLED.\n" << field;
					continue;
				}

				success = field.isLegalMove(--by, --bx, --y, --x);
			} while (!success);
		}
		else {
			vector <EvalMove> evals = edgeBot.eval(field, depth);
			if (analyze) {
				cout << "\nEdgeBot: here's my top " << min(evals.size(), (size_t)9) << " of possible moves:\n";
				for (size_t i = 0; i < min(evals.size(), (size_t)9); i++) {
					cout << (i + 1) << ". " << evals[i].move << ": " << evals[i].eval << "\n";
				}
			}
			size_t m = getRandomTopMove(evals, margin);
			cout << "\nEdgeBot: I chose to make move on " << evals[m].move << ".\n\n";
			by = evals[m].move.by;
			bx = evals[m].move.bx;
			y = evals[m].move.y;
			x = evals[m].move.x;
		}
		
		field.move(by, bx, y, x);
		switch (field.getWinner()) {
		case Cell::Cross:
			cout << field << "CROSS won this game. GG!\n";
			return;
		case Cell::Null:
			cout << field << "NULLS won this game. GG!\n";
			return;
		case Cell::Any:
			cout << field << "Round draw. Incredible!\n";
			return;
		default:
			break;
		}

		pcross = !pcross;
	}
}

void playerVsOldEdge(Field& field, size_t depth, double margin, bool pcross, bool analyze, bool reverts) {
	EdgeBot_v1_0 edgeBot;
	size_t by, bx, y, x;
	bool success;

	while (true) {
		success = false;
		if (field.getNextBoard().y == -1) {
			cout << field << getSide(field.getTurn()) << " turn on ANY board!\n";
		}
		else {
			cout << field << getSide(field.getTurn()) << " turn on (" << (field.getNextBoard().x) + 1 << ", " << (field.getNextBoard().y) + 1 << ") board!\n";
		}

		if (pcross) {
			do {
				cout << "Input: bx by x y\n\n";
				cin >> bx >> by >> x >> y;
				cout << "\n";

				if (bx == -1 && reverts) {
					field.revert();
					field.revert();
					cout << "\n2 MOVES WERE CANCELLED.\n" << field;
					continue;
				}

				success = field.isLegalMove(--by, --bx, --y, --x);
			} while (!success);
		}
		else {
			vector <EvalMove> evals = edgeBot.eval(field, depth);
			if (analyze) {
				cout << "\nEdgeBot: here's my top " << min(evals.size(), (size_t)9) << " of possible moves:\n";
				for (size_t i = 0; i < min(evals.size(), (size_t)9); i++) {
					cout << (i + 1) << ". " << evals[i].move << ": " << evals[i].eval << "\n";
				}
			}
			size_t m = getRandomTopMove(evals, margin);
			cout << "\nEdgeBot: I chose to make move on " << evals[m].move << ".\n\n";
			by = evals[m].move.by;
			bx = evals[m].move.bx;
			y = evals[m].move.y;
			x = evals[m].move.x;
		}

		field.move(by, bx, y, x);
		switch (field.getWinner()) {
		case Cell::Cross:
			cout << field << "CROSS won this game. GG!\n";
			return;
		case Cell::Null:
			cout << field << "NULLS won this game. GG!\n";
			return;
		case Cell::Any:
			cout << field << "Round draw. Incredible!\n";
			return;
		default:
			break;
		}

		pcross = !pcross;
	}
}

void edgeVsEdge(Field& field, size_t depth1, size_t depth2, double margin1, double margin2, bool firstFirst = true) {
	EdgeBot_v1_1 edgeBot;
	size_t by, bx, y, x;

	while (true) {
		if (field.getNextBoard().y == -1) {
			cout << field << getSide(field.getTurn()) << " turn on ANY board!\n";
		}
		else {
			cout << field << getSide(field.getTurn()) << " turn on (" << (field.getNextBoard().x) + 1 << ", " << (field.getNextBoard().y) + 1 << ") board!\n";
		}

		if (firstFirst) {
			vector <EvalMove> evals = edgeBot.eval(field, depth1);
			cout << "\nEdgeBot A: here's my top " << min(evals.size(), (size_t)9) << " of possible moves:\n";
			for (size_t i = 0; i < min(evals.size(), (size_t)9); i++) {
				cout << (i + 1) << ". " << evals[i].move << ": " << evals[i].eval << "\n";
			}
			size_t m = getRandomTopMove(evals, margin1);
			cout << "\nEdgeBot A: I chose to make move on " << evals[m].move << ".\n\n";
			by = evals[m].move.by;
			bx = evals[m].move.bx;
			y = evals[m].move.y;
			x = evals[m].move.x;
		}
		else {
			vector <EvalMove> evals = edgeBot.eval(field, depth2);
			cout << "\nEdgeBot B: here's my top " << min(evals.size(), (size_t)9) << " of possible moves:\n";
			for (size_t i = 0; i < min(evals.size(), (size_t)9); i++) {
				cout << (i + 1) << ". " << evals[i].move << ": " << evals[i].eval << "\n";
			}
			size_t m = getRandomTopMove(evals, margin2);
			cout << "\nEdgeBot B: I chose to make move on " << evals[m].move << ".\n\n";
			by = evals[m].move.by;
			bx = evals[m].move.bx;
			y = evals[m].move.y;
			x = evals[m].move.x;
		}

		field.move(by, bx, y, x);
		switch (field.getWinner()) {
		case Cell::Cross:
			cout << field << "CROSS won this game. GG!\n";
			return;
		case Cell::Null:
			cout << field << "NULLS won this game. GG!\n";
			return;
		case Cell::Any:
			cout << field << "Round draw. Incredible!\n";
			return;
		default:
			break;
		}

		firstFirst = !firstFirst;
	}
}

void edgeVsOldEdge(Field& field, size_t depth10, size_t depth11, double margin10, double margin11, bool oldFirst) {
	EdgeBot_v1_0 edgeBot0;
	EdgeBot_v1_1 edgeBot1;
	size_t by, bx, y, x;

	while (true) {
		if (field.getNextBoard().y == -1) {
			cout << field << getSide(field.getTurn()) << " turn on ANY board!\n";
		}
		else {
			cout << field << getSide(field.getTurn()) << " turn on (" << (field.getNextBoard().x) + 1 << ", " << (field.getNextBoard().y) + 1 << ") board!\n";
		}

		if (oldFirst) {
			vector <EvalMove> evals = edgeBot0.eval(field, depth10);
			cout << "\nEdgeBot v1.0: here's my top " << min(evals.size(), (size_t)9) << " of possible moves:\n";
			for (size_t i = 0; i < min(evals.size(), (size_t)9); i++) {
				cout << (i + 1) << ". " << evals[i].move << ": " << evals[i].eval << "\n";
			}
			size_t m = getRandomTopMove(evals, margin10);
			cout << "\nEdgeBot v1.0: I chose to make move on " << evals[m].move << ".\n\n";
			by = evals[m].move.by;
			bx = evals[m].move.bx;
			y = evals[m].move.y;
			x = evals[m].move.x;
		}
		else {
			vector <EvalMove> evals = edgeBot1.eval(field, depth11);
			cout << "\nEdgeBot v1.1: here's my top " << min(evals.size(), (size_t)9) << " of possible moves:\n";
			for (size_t i = 0; i < min(evals.size(), (size_t)9); i++) {
				cout << (i + 1) << ". " << evals[i].move << ": " << evals[i].eval << "\n";
			}
			size_t m = getRandomTopMove(evals, margin11);
			cout << "\nEdgeBot v1.1: I chose to make move on " << evals[m].move << ".\n\n";
			by = evals[m].move.by;
			bx = evals[m].move.bx;
			y = evals[m].move.y;
			x = evals[m].move.x;
		}

		field.move(by, bx, y, x);
		switch (field.getWinner()) {
		case Cell::Cross:
			cout << field << "CROSS won this game. GG!\n";
			return;
		case Cell::Null:
			cout << field << "NULLS won this game. GG!\n";
			return;
		case Cell::Any:
			cout << field << "Round draw. Incredible!\n";
			return;
		default:
			break;
		}

		oldFirst = !oldFirst;
	}
}

int main(int argc, char* argv[]) {
	srand(time(0));
	Field field;

	size_t edgeBotHalfDepth = 6;
	size_t edgeBotHalfDepthEasier = 4;
	double margin100 = 0.51;
	double margin101 = 0.01;
	double margin110 = 0.11;
	double margin111 = 1.01;

	char input  = '0';
	char input2 = '0';
	do {
		cout << "Select a gamemode!\n\n";
		cout << "1 - Play vs bot\n";
		cout << "2 - Play as two\n";
		cout << "3 - Watch bot game\n\n";
		cin >> input;
		cout << "\n";
	} while (input < '1' || input > '3');
	switch (input) {
	case '1':
		do {
			cout << "Choose your enemy:\n\n";
			cout << "1 - EdgeBot v1.1 (depth = " << edgeBotHalfDepth / 2 << ", margin = " << margin110 << ")\n";
			cout << "2 - EdgeBot v1.1 (depth = " << edgeBotHalfDepth / 2 << ", margin = " << margin111 << ")\n";
			cout << "3 - EdgeBot v1.1 (depth = " << edgeBotHalfDepthEasier / 2 << ", margin = " << margin110 << ")\n";
			cout << "4 - EdgeBot v1.1 (depth = " << edgeBotHalfDepthEasier / 2 << ", margin = " << margin111 << ")\n";
			cout << "5 - EdgeBot v1.0 (depth = " << edgeBotHalfDepth / 2 << ", margin = " << margin100 << ")\n\n";
			cin >> input;
			cout << "\n";
		} while (input < '1' || input > '4');
		do {
			cout << "Choose your side:\n\n";
			cout << "1 - CROSS\n";
			cout << "2 - NULLS\n\n";
			cin >> input2;
			cout << "\n";
		} while (input2 < '1' || input2 > '2');
		switch (input) {
		case '1':
			playerVsEdge(field, edgeBotHalfDepth, margin110, (input2 == '1'), true, true);
			break;
		case '2':
			playerVsEdge(field, edgeBotHalfDepth, margin111, (input2 == '1'), true, true);
			break;
		case '3':
			playerVsEdge(field, edgeBotHalfDepthEasier, margin110, (input2 == '1'), true, true);
			break;
		case '4':
			playerVsEdge(field, edgeBotHalfDepthEasier, margin111, (input2 == '1'), true, true);
			break;
		case '5':
			playerVsOldEdge(field, edgeBotHalfDepth, margin100, (input2 == '1'), true, true);
			break;
		default:
			break;
		}
		break;
	case '2':
		do {
			cout << "Choose game type:\n\n";
			cout << "1 - Two player game\n";
			cout << "2 - Analyze every move with EdgeBot v1.1 (depth = " << edgeBotHalfDepth / 2 << ")\n\n";
			cin >> input;
			cout << "\n";
		} while (input < '1' || input > '2');
		switch (input) {
		case '1':
			playerVsPlayer(field, false, true);
			break;
		case '2':
			playerVsPlayer(field, true, true);
			break;
		default:
			break;
		}
		break;
	case '3':
		do {
			cout << "Choose a matchup:\n\n";
			cout << "1 - EdgeBot v1.1 (depth = " << edgeBotHalfDepth / 2 << ", margin = " << margin110 << ") vs EdgeBot v1.0 (depth = " << edgeBotHalfDepth / 2 << ", margin = " << margin100 << ")\n";
			cout << "2 - EdgeBot v1.0 (depth = " << edgeBotHalfDepth / 2 << ", margin = " << margin100 << ") vs EdgeBot v1.1 (depth = " << edgeBotHalfDepth / 2 << ", margin = " << margin110 << ")\n";
			cout << "3 - EdgeBot v1.1 (depth = " << edgeBotHalfDepth / 2 << ", margin = " << margin110 << ") vs EdgeBot v1.1 (depth = " << edgeBotHalfDepth / 2 << ", margin = " << margin110 << ")\n";
			cout << "4 - EdgeBot v1.1 (depth = " << edgeBotHalfDepthEasier / 2 << ", margin = " << margin110 << ") vs EdgeBot v1.0 (depth = " << edgeBotHalfDepth / 2 << ", margin = " << margin101 << ")\n";
			cout << "5 - EdgeBot v1.0 (depth = " << edgeBotHalfDepth / 2 << ", margin = " << margin101 << ") vs EdgeBot v1.1 (depth = " << edgeBotHalfDepthEasier / 2 << ", margin = " << margin110 << ")\n\n";
			cin >> input;
			cout << "\n";
		} while (input < '1' || input > '5');
		switch (input) {
		case '1':
			edgeVsOldEdge(field, edgeBotHalfDepth, edgeBotHalfDepth, margin100, margin110, false);
			break;
		case '2':
			edgeVsOldEdge(field, edgeBotHalfDepth, edgeBotHalfDepth, margin100, margin110, true);
			break;
		case '3':
			edgeVsEdge(field, edgeBotHalfDepth, edgeBotHalfDepth, margin110, margin110);
			break;
		case '4':
			edgeVsOldEdge(field, edgeBotHalfDepth, edgeBotHalfDepthEasier, margin101, margin110, false);
			break;
		case '5':
			edgeVsOldEdge(field, edgeBotHalfDepth, edgeBotHalfDepthEasier, margin101, margin110, true);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	cout << "Press ENTER to kill this app.\n";
	cin.get();
	cin.get();
	return 0;
}