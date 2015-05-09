#include "Queen.h"

namespace Chess {
	Queen::Queen(const Position& position, bool white) : Piece(position, white) {

	}

	char Queen::notation() const {
		return isWhite() ? 'Q' : 'q';
	}
}