#include "King.h"

#include "Board.h"

namespace Chess {
	King::King(const Position& position, bool white) : Piece(position, white) {

	}

	void King::move(const Position& newPosition) {
		position = newPosition;
		_hasMoved = true;
	}

	bool King::hasMoved()const{
		return _hasMoved;
	}

	bool King::isChecked(const Board& board) const {

		for (int i = 0; i < 8; i++){
			for (int j = 0; j < 8; j++){
				Position tempPos;
				tempPos.x = i;
				tempPos.y = j;
				Piece *tempPiece = board.getPiece(tempPos);

				if (tempPiece != nullptr && (isWhite()!=tempPiece->isWhite())){
					std::vector<Chess::Position> moves = tempPiece->legalMoves(board);
					for (Chess::Position move : moves){
						if (move == position){
							return true;
						}
					}
				}
			}
		} 
		return false;
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