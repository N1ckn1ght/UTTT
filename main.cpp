#include "Field.h"
#include <cstdlib>
#include <ctime>

using namespace std;

char getSide(Cell cell) {
	switch (cell) {
		case Cell::Cross:
			return 'X';
			break;
		case Cell::Null:
			return 'O';
			break;
		default:
			break;
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

int main(int argc, char* argv[]) {
	srand(time(0));
	Field field;

	char input = '0';
	do {
		cout << "Select a gamemode!\n\n";
		cout << "1 - Play vs Bot\n";
		cout << "2 - Play as two\n\n";
		cin >> input;
		cout << "\n";
	} while (input < '1' || input > '2');
	switch (input) {
		case '1':
			// nothing for now
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