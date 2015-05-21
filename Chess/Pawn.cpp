#include "Pawn.h"
#include "Board.h"

namespace Chess {
	Pawn::Pawn(const Position& position, bool white) : Piece(position, white) {
		_hasMoved = false;
	}

	void Pawn::move(const Position& newPosition) {
		//update to alter _hasMoved to disable any future double space moves
		_hasMoved = true;
		position = newPosition;
	}

	std::vector<Position> Pawn::moves(const Board& board) const {
		std::vector<Position> moves;

		int direction = 0;

		if (isWhite()) {
			direction = 1;
		} else {
			direction = -1;
		}

		for (int i = 1; i < 3; i++) {
			Position newPos = position;
			newPos.y += i*direction;

			Piece* temp = board.getPiece(newPos);
			//check if the default (1 space) move is possible
			if (temp == nullptr && (i!=2) && newPos.valid()) {
				moves.push_back(newPos);
			//Check so that we do not attempt to jump over pieces
			} else if (temp != nullptr){
				break;
			//Can we double-move
			} else if((i==2) && (!_hasMoved)) {
				moves.push_back(newPos);
			}
		}
		
		// Check case where pawn has the ability to eliminate opposing piece (incl. en passant)
		for (int j = -1; j < 2;j+=2) {
			Position newPos = position;
			newPos.y += direction;
			newPos.x += j;

			Piece* temp = board.getPiece(newPos);
			if (newPos.valid()) {
				if (temp != nullptr && temp->isWhite() != isWhite()) {
					moves.push_back(newPos);
				}
				//Is this position a valid 'en passant' position
				if (board.getEnPassantPossible() == newPos) {
					moves.push_back(newPos);
				}
			}
		}

		return moves;
	}

	char Pawn::notation() const {
		return isWhite() ? 'P' : 'p';
	}
}