#include "Bishop.h"
#include "Board.h"

namespace Chess {
	Bishop::Bishop(const Position& position, bool white) : Piece(position, white) {
	}

	std::vector<Position> Bishop::moves(const Board& board) const {
		std::vector<Position> moves;

		//Nested for loop for all 4 direction in which the Bishop can move
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
					//if position is empty and valid, push it
					if (temp == nullptr && newPos.valid()) {
						moves.push_back(newPos);
					}
					//if we encounter the edge of the board or an allied piece, go to next iteration.
					else if (!newPos.valid() || isWhite() == temp->isWhite()) {
						break;
					}
					//if we encounter an enemy, push the position
					else{
						moves.push_back(newPos);
						break;
					}
				}
			}
		}

		return moves;
	}

	char Bishop::notation() const {
		return isWhite() ? 'B' : 'b';
	}
}