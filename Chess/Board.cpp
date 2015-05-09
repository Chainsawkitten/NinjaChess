#include "Board.h"

namespace Chess {
	Board::Board() {
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				pieces[x][y] = nullptr;
			}
		}
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