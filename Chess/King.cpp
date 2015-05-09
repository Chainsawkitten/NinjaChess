#include "King.h"

namespace Chess {
	King::King(const Position& position, bool white) : Piece(position, white) {

	}

	char King::notation() const {
		return isWhite() ? 'K' : 'k';
	}
}