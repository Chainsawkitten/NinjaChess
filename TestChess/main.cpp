#include "main.h"

#include <iostream>

using namespace std;

int main() {
	Chess::Board board;

	printBoard(board);

	cout << "Check valid moves for position:" << endl;
	int x, y;
	cin >> x >> y;
	Chess::Position position(x-1, y-1);
	if (position.valid()) {
		printValidMoves(board, position);
	} else {
		cout << "Position out of bounds." << endl;
	}

	cin.ignore();
	cin.get();

	return EXIT_SUCCESS;
}

void printBoard(const Chess::Board& board) {
	for (int y = 7; y >= 0; y--) {
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

void printValidMoves(const Chess::Board& board, const Chess::Position& position) {
	Chess::Piece* piece = board.getPiece(position);

	if (piece == nullptr) {
		cout << "No piece at that position." << endl;
	} else {
		std::vector<Chess::Position> moves = piece->validMoves(board);
		for (Chess::Position move : moves) {
			cout << "x: " << (move.x + 1) << ", y: " << (move.y + 1) << endl;
		}
	}
}