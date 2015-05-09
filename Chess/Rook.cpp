#include "Rook.h"

namespace Chess {
	Rook::Rook(const Position& position, bool white) : Piece(position, white) {

	}

	char Rook::notation() const {
		return isWhite() ? 'R' : 'r';
	}
}