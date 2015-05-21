#include "Queen.h"
#include "Board.h"

namespace Chess {
	Queen::Queen(const Position& position, bool white) : Piece(position, white) {

	}

	std::vector<Position> Queen::moves(const Board& board) const {
		std::vector<Position> moves;

		//Check diagonal moves
		for (int i = -1; i < 2; i += 2) {
			for (int j = -1; j < 2; j += 2) {
				int tempX = i;
				int tempY = j;
				while (true) {
					Position newPos = position;
					newPos.x += tempX;
					newPos.y += tempY;
					tempX += i;
					tempY += j;

					Piece* temp = board.getPiece(newPos);
					if (temp == nullptr && newPos.valid()) {
						moves.push_back(newPos);
					}
					else if (!newPos.valid() || isWhite() == temp->isWhite()) {
						break;
					}
					else{
						moves.push_back(newPos);
						break;
					}
				}
			}
		}

		//Check vertical and horizontal moves
		for (int i = 0; i < 4; i++) {
			int num = i % 2 == 0 ? position.x : position.y;
			int way = 1 + (-2 * (i < 2));

			for (int j = num + way; j >= 0 && j <= 7; j += way) {
				Position newPos = position;
				if (i % 2 == 0) {
					newPos.x = j;
				}
				else {
					newPos.y = j;
				}

				Piece* other = board.getPiece(newPos);
				if (other == nullptr) {
					moves.push_back(newPos);
				}
				else if (other->isWhite() == isWhite()) {
					break;
				}
				else {
					moves.push_back(newPos);
					break;
				}
			}
		}
		return moves;
	}

	char Queen::notation() const {
		return isWhite() ? 'Q' : 'q';
	}
}