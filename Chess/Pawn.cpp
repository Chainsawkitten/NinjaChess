#include "Pawn.h"
#include "Board.h"

namespace Chess {
	Pawn::Pawn(const Position& position, bool white) : Piece(position, white) {

	}

	std::vector<Position> Pawn::validMoves(const Board& board) const {
		std::vector<Position> moves;

		int direction = 0;

		if (isWhite()){
			direction = 1;
		}
		else{
			direction = -1;
		}

		for (int i = 1; i < 3; i++){
			Position newPos = position;
			newPos.y += i*direction;

			Piece* temp = board.getPiece(newPos);
			if (temp == nullptr && (i!=2)){
				moves.push_back(newPos);
			}
			else if((i==2) && (!_hasMoved)){
				moves.push_back(newPos);
			}
		}
		//Check case where pawn has the ability to eliminate opposing piece
		for (int j = -1; j < 2;){
			Position newPos = position;
			newPos.y += direction;
			newPos.x += j;

			Piece* temp = board.getPiece(newPos);
			if (temp != nullptr && temp->isWhite() != isWhite()){
				moves.push_back(newPos);
			}
		}



		return moves;
	}

	char Pawn::notation() const {
		return isWhite() ? 'P' : 'p';
	}
}