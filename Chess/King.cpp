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

	std::vector<Position> King::legalMoves(const Board& board) const{
		std::vector<Position> validPosition;
		Position oldPos = position;
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
		//Check for valid castling
		if (!_hasMoved && !isChecked(board)){
			Rook* leftRook = dynamic_cast<Rook *>(board.getPiece(Position(0, position.y)));
			Rook* rightRook = dynamic_cast<Rook *>(board.getPiece(Position(7, position.y)));
			bool leftCastling = true;
			bool rightCastling = true;
			Board tempBoard = board;

			for (int l = -1; l < 2; l += 2){
				if (board.getPiece(Position(oldPos.x + 1*l, oldPos.y)) == nullptr
					&& board.getPiece(Position(oldPos.x + 2*l, oldPos.y)) == nullptr){
					for (int k = 1; k < 3; k++){
						Position tempPosition = Position(oldPos.x + k*l, oldPos.y);
						//position = tempPosition; problem med const
						//isChecked kallar på legalMoves, legalMoves kallar på isChecked == evighet.
						if (board.getPiece(Position(oldPos.x + 3 * l, oldPos.y)) != nullptr || leftRook->hasMoved() || (l == -1 && isChecked(board))){
							leftCastling = false;
						}
						if (rightRook->hasMoved() || (l == 1 && isChecked(board))){
							rightCastling = false;
						}
					}
				}
				else{
					if (l == 1){
						rightCastling = false;
					}
					else if (l == -1){
						leftCastling = false;
					}
				}
			}
			//position = oldPos;
			if (leftCastling){
				validPosition.push_back(Position(position.x - 2, position.y));
			}
			if (rightCastling){
				validPosition.push_back(Position(position.x + 2, position.y));
			}
		}

		return validPosition;
	}
}