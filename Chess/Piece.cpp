#include "Piece.h"

#include "Board.h"

namespace Chess {
	Piece::Piece(const Position& position, bool white) {
		this->position = position;
		this->white = white;
	}

	bool Piece::isWhite() const {
		return white;
	}

	void Piece::move(const Position& newPosition) {
		position = newPosition;
	}

	bool Piece::isLegal(const Board& board, const Position& newPosition) const {
		std::vector<Position> moves = legalMoves(board);
		for (const Position move : moves) {
			if (newPosition == move)
				return true;
		}

		return false;
	}

	std::vector<Position> Piece::legalMoves(const Board& board) const {
		std::vector<Position> potentialMoves = moves(board);

		// TODO: Remove moves that leave the king in check.

		return potentialMoves;
	}

	std::vector<Position> Piece::moves(const Board& board) const {
		std::vector<Position> moves;

		return moves;
	}

	Position Piece::getPosition() const {
		return position;
	}
}