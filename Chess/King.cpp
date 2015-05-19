#include "King.h"
#include "Rook.h"
#include "Board.h"

namespace Chess {
	King::King(const Position& position, bool white) : Piece(position, white) {
		_hasMoved = false;
	}

	void King::move(const Position& newPosition) {
		position = newPosition;
		_hasMoved = true;
	}

	bool King::hasMoved() const {
		return _hasMoved;
	}

	bool King::isChecked(const Board& board) const {
		// Check other pieces.
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				Piece* piece = board.getPiece(Position(x, y));

				if (piece != nullptr && isWhite() != piece->isWhite() && piece->notation() != 'k' && piece->notation() != 'K') {
					std::vector<Position> moves = piece->moves(board);
					for (Position move : moves) {
						if (move == position)
							return true;
					}
				}
			}
		}

		// Check opponent's king.
		for (int x = position.x - 1; x <= position.x + 1; x++) {
			for (int y = position.y - 1; y <= position.y + 1; y++) {
				if (Position(x, y).valid()) {
					Piece* piece = board.getPiece(Position(x, y));
					if (piece != nullptr && piece->isWhite() != isWhite() && (piece->notation() == 'k' || piece->notation() == 'K'))
						return true;
				}
			}
		}

		return false;
	}

	char King::notation() const {
		return isWhite() ? 'K' : 'k';
	}

	std::vector<Position> King::moves(const Board& board) const {
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

		// Check for valid castling
		if (!_hasMoved && !isChecked(board)) {
			Rook* leftRook = dynamic_cast<Rook *>(board.getPiece(Position(0, position.y)));
			Rook* rightRook = dynamic_cast<Rook *>(board.getPiece(Position(7, position.y)));
			bool leftCastling = true;
			bool rightCastling = true;
			King castlingKing = King(position,isWhite());

			for (int l = -1; l < 2; l += 2) {
				if (board.getPiece(Position(position.x + 1 * l, position.y)) == nullptr
					&& board.getPiece(Position(position.x + 2 * l, position.y)) == nullptr) {
					for (int k = 1; k < 3; k++) {
						Position tempPosition = position;
						tempPosition.x += k*l;
						castlingKing.position = tempPosition;
						if (l == -1) {
							if (board.getPiece(Position(position.x + 3 * l, position.y)) != nullptr || leftRook == nullptr || leftRook->hasMoved() || castlingKing.isChecked(board)) {
								leftCastling = false;
							}
						} else if (l == 1) {
							if (rightRook == nullptr || rightRook->hasMoved() || castlingKing.isChecked(board)) {
								rightCastling = false;
							}
						}
					}
				} else {
					if (l == 1) {
						rightCastling = false;
					} else if (l == -1) {
						leftCastling = false;
					}
				}
			}
			if (leftCastling)
				validPosition.push_back(Position(position.x - 2, position.y));

			if (rightCastling)
				validPosition.push_back(Position(position.x + 2, position.y));
		}

		return validPosition;
	}
}