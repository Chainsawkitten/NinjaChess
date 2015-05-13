#include "King.h"

#include "Board.h"

namespace Chess {
	King::King(const Position& position, bool white) : Piece(position, white) {

	}

	void King::move(const Position& newPosition) {
		position = newPosition;
		_hasMoved = true;
	}

	char King::notation() const {
		return isWhite() ? 'K' : 'k';
	}

	std::vector<Position> King::legalMoves(const Board& board) const {
		std::vector<Position> validPosition;
		Position tempPosition;

		for (int i = 0; i < 3; i++) {
			tempPosition.x = this->position.x - 1 + i;
			for (int j = 0; j < 3; j++) {
				tempPosition.y = this->position.y - 1 + j;
				if (tempPosition.valid() && 
					( ( board.getPiece(tempPosition) == nullptr ) || (board.getPiece(tempPosition)->isWhite() != this->isWhite()) ) )
					validPosition.push_back(tempPosition);
			}
		}

		return validPosition;
	}
}