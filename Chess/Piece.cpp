#include "Piece.h"

#include "Board.h"

namespace Chess {
	Piece::Piece(const Position& position, bool white) {
		this->position = position;
		this->white = white;
		lastMoveWasDouble = false;
	}

	bool Piece::isWhite() const {
		return white;
	}

	std::vector<Position> Piece::validMoves(const Board& board) const {
		std::vector<Position> moves;

		return moves;
	}
	bool Piece::lastMoveDouble() const{
		return lastMoveWasDouble;
	}
}