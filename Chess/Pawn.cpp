#include "Pawn.h"
#include "Board.h"

namespace Chess {
	Pawn::Pawn(const Position& position, bool white) : Piece(position, white) {
		_hasMoved = false;
		lastMoveWasDouble = false;
	}

	std::vector<Position> Pawn::legalMoves(const Board& board) const {
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
			if (temp == nullptr && (i!=2) && newPos.valid()) {
				moves.push_back(newPos);
			} else if (temp != nullptr){
				break;
			} else if((i==2) && (!_hasMoved)) {
				moves.push_back(newPos);
			}
		}
		//Check case where pawn has the ability to eliminate opposing piece (incl. en passant)
		for (int j = -1; j < 2;j+=2) {
			Position enPassantPawn = position;
			Position newPos = position;

			enPassantPawn.x += j;
			newPos.y += direction;
			newPos.x += j;

			Piece* temp = board.getPiece(newPos);
			if (newPos.valid()) {
				if (temp != nullptr && temp->isWhite() != isWhite()) {
					moves.push_back(newPos);
				}
			}
			if (enPassantPawn.valid()) {
				Pawn* tempEnPassant = dynamic_cast<Pawn *>(board.getPiece(enPassantPawn));
				if (tempEnPassant != nullptr && tempEnPassant->lastMoveWasDouble && ((enPassantPawn.y == 4 && isWhite()) || (enPassantPawn.y == 3 && !isWhite()))) {
					enPassantPawn.y += direction;
					moves.push_back(enPassantPawn);
				}
			}
		}

		return moves;
	}

	char Pawn::notation() const {
		return isWhite() ? 'P' : 'p';
	}
}