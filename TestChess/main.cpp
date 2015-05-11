#include "main.h"

#include <iostream>

using namespace std;

int main() {
	Chess::Board board;

	printBoard(board);

	int choice;
	do {
		cout << "1. Move" << endl
			 << "2. Check valid moves" << endl;
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Move piece: ";
			int oldX, oldY;
			cin >> oldX >> oldY;
			cout << "Where: ";
			int newX, newY;
			cin >> newX >> newY;

			if (!board.move(Chess::Position(oldX - 1, oldY - 1), Chess::Position(newX - 1, newY - 1)))
				cout << "Invalid move." << endl;
			
			cout << endl;
			printBoard(board);

			break;
		case 2:
			cout << "Check valid moves for position: ";
			int x, y;
			cin >> x >> y;
			Chess::Position position(x - 1, y - 1);
			if (position.valid()) {
				printValidMoves(board, position);
			} else {
				cout << "Position out of bounds." << endl;
			}
			cout << endl;
			break;
		}
	} while (choice >= 1 && choice <= 2);

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