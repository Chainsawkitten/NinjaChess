#include "main.h"

#include <iostream>

using namespace std;

int main() {
	Chess::Board board;

	printBoard(board);

	cin.get();

	return EXIT_SUCCESS;
}

void printBoard(const Chess::Board& board) {
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			Chess::Piece* piece = board.getPiece(Chess::Position(x, y));
			if (piece == nullptr) {
				cout << '.';
			} else {
				cout << piece->notation();
			}
		}
		cout << endl;
	}
}