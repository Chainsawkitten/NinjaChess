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

	bool Piece::isLegal(Board& board, const Position& newPosition) const {
		std::vector<Position> moves = legalMoves(board);
		for (const Position move : moves) {
			if (newPosition == move)
				return true;
		}

		return false;
	}

	std::vector<Position> Piece::legalMoves(Board& board) const {
		std::vector<Position> potentialMoves = moves(board);
		std::vector<Position> legalMoves;

		// Remove moves that leave the king in check.
		for (Position move : potentialMoves) {
			if (!board.willLeaveKingChecked(position, move))
				legalMoves.push_back(move);
		}

		return legalMoves;
	}

	std::vector<Position> Piece::moves(const Board& board) const {
		std::vector<Position> moves;

		return moves;
	}

	Position Piece::getPosition() const {
		return position;
	}
}