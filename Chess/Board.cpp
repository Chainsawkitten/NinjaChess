#include "Board.h"
#include "Pawn.h"
#include "Rook.h"

namespace Chess {
	Board::Board() {
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				pieces[x][y] = nullptr;
			}
		}

		// Black pawns
		for (int x = 0; x < 8; x++) {
			pieces[x][1] = new Pawn(Position(x, 1), false);
		}

		// White pawns
		for (int x = 0; x < 8; x++) {
			pieces[x][6] = new Pawn(Position(x, 6), true);
		}

		// Rooks
		pieces[0][0] = new Rook(Position(0, 0), false);
		pieces[7][0] = new Rook(Position(7, 0), false);
		pieces[0][7] = new Rook(Position(0, 7), true);
		pieces[7][7] = new Rook(Position(7, 7), true);
	}

	Board::~Board() {
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				if (pieces[x][y] != nullptr)
					delete pieces[x][y];
			}
		}
	}

	Piece* Board::getPiece(const Position& position) const {
		return pieces[position.x][position.y];
	}
}