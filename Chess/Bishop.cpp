#include "Bishop.h"

namespace Chess {
	Bishop::Bishop(const Position& position, bool white) : Piece(position, white) {

	}

	char Bishop::notation() const {
		return isWhite() ? 'B' : 'b';
	}
}