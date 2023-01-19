#include "Field.h"
#include "EdgeBot.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

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

void playerVsPlayer(Field& field, bool analyze) {
	size_t by, bx, y, x;
	bool success;

	while (true) {
		if (analyze) {
			// todo
		}

		success = false;
		if (field.getNextBoard().y == -1) {
			cout << field << getSide(field.getTurn()) << " turn on ANY board!\n";
		} 
		else {
			cout << field << getSide(field.getTurn()) << " turn on (" << (field.getNextBoard().x) + 1 << " ," << (field.getNextBoard().y) + 1 << ") board!\n";
		}
		do {
			cout << "Input: bx by x y\n";
			cin >> bx >> by >> x >> y;
			cout << "\n";
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

void playerVsEdge(Field& field, size_t depth, bool pcross, bool analyze) {
	EdgeBot edgeBot;
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
			cout << "\nEdgeBot: I choose to make move on " << evals[0].move << ".\n";
			by = evals[0].move.by;
			bx = evals[0].move.bx;
			y = evals[0].move.y;
			x = evals[0].move.x;
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



int main(int argc, char* argv[]) {
	srand(time(0));
	Field field;
	size_t edgeBotHalfDepth = 6;

	size_t heuristHalfDepth = 6;

	char input  = '0';
	char input2 = '0';
	do {
		cout << "Select a gamemode!\n\n";
		cout << "1 - Play vs Bot\n";
		cout << "2 - Play as two\n\n";
		cin >> input;
		cout << "\n";
	} while (input < '1' || input > '2');
	switch (input) {
	case '1':
		do {
			cout << "Choose your enemy:\n\n";
			cout << "1 - EdgeBot (depth = " << edgeBotHalfDepth << ")\n\n";
			cin >> input;
			cout << "\n";
		} while (input < '1' || input > '1');
		do {
			cout << "Choose your side:\n\n";
			cout << "1 - CROSS\n";
			cout << "2 - NULLS\n\n";
			cin >> input2;
			cout << "\n";
		} while (input2 < '1' || input2 > '2');
		switch (input) {
		case '1':
			playerVsEdge(field, edgeBotHalfDepth, (input2 == '1'), true);
			break;
		default:
			break;
		}
		break;
	case '2':
		do {
			cout << "Choose game type:\n\n";
			cout << "1 - Two player game\n";
			cout << "2 - Analyze every move with bots\n\n";
			cin >> input;
			cout << "\n";
		} while (input < '1' || input > '2');
		switch (input) {
		case '1':
			playerVsPlayer(field, false);
			break;
		case '2':
			// nothing for now
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