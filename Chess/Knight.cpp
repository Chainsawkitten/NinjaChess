#include "Knight.h"

namespace Chess {
	Knight::Knight(const Position& position, bool white) : Piece(position, white) {

	}

	char Knight::notation() const {
		return isWhite() ? 'N' : 'n';
	}
}