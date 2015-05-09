#include "Pawn.h"

namespace Chess {
	Pawn::Pawn(const Position& position, bool white) : Piece(position, white) {

	}

	char Pawn::notation() const {
		return isWhite() ? 'P' : 'p';
	}
}