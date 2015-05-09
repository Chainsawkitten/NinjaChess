#include "Piece.h"

namespace Chess {
	Piece::Piece(const Position& position, bool white) {
		this->position = position;
		this->white = white;
	}

	bool Piece::isWhite() const {
		return white;
	}
}