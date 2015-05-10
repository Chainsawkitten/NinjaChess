#include "Bishop.h"
#include "Board.h"

namespace Chess {
	Bishop::Bishop(const Position& position, bool white) : Piece(position, white) {
	}

	std::vector<Position> Bishop::validMoves(const Board& board) const {
		std::vector<Position> moves;

		for (int i = -1; i < 2; i += 2){
			for (int j = -1; j < 2; j += 2){
				for (int tempX = i, int tempY = j;true; tempY += i, tempX += j){
					Position newPos = position;
					newPos.x += tempX;
					newPos.y += tempY;

					Piece* temp = board.getPiece(newPos);
					if (temp == nullptr){
						moves.push_back(newPos);
					} else if (isWhite() == temp->isWhite() || !newPos.valid()){
						break;
					}
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