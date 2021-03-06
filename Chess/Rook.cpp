#include "Rook.h"

#include "Board.h"

namespace Chess {
	Rook::Rook(const Position& position, bool white) : Piece(position, white) {
		_hasMoved = false;
	}

	void Rook::move(const Position& newPosition) {
		position = newPosition;
		_hasMoved = true;
	}

	bool Rook::hasMoved()const{
		return _hasMoved;
	}

	char Rook::notation() const {
		return isWhite() ? 'R' : 'r';
	}

	std::vector<Position> Rook::moves(const Board& board) const {
		std::vector<Position> moves;
		//Check the four directions that a rook can move in.
		for (int i = 0; i < 4; i++) {
			int num = i % 2 == 0 ? position.x : position.y;
			int way = 1 + (-2 * (i < 2));

			for (int j = num + way; j >= 0 && j <= 7; j += way) {
				Position newPos = position;
				if (i % 2 == 0) {
					newPos.x = j;
				} else {
					newPos.y = j;
				}

				Piece* other = board.getPiece(newPos);
				if (other == nullptr) {
					moves.push_back(newPos);
				} else if (other->isWhite() == isWhite()) {
					break;
				} else {
					moves.push_back(newPos);
					break;
				}
			}
		}

		return moves;
	}
}