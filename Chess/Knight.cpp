#include "Knight.h"
#include "Board.h"

namespace Chess {
	Knight::Knight(const Position& position, bool white) : Piece(position, white) {

	}

	std::vector<Position> Knight::moves(const Board& board) const {
		std::vector<Position> moves, testMoves;
		for (int i = -1; i < 2; i += 2){
			for (int j = -2; j < 3; j += 4){
				testMoves.push_back(Position(position.x + i, position.y + j));
				testMoves.push_back(Position(position.x + j, position.y + i));
			}
		}
		for (auto move : testMoves) {
			//if the position is not occupied by allied piece, it is legal
			if (move.valid() && ((board.getPiece(move) == nullptr) || (isWhite() != board.getPiece(move)->isWhite())))
				moves.push_back(move);
		}
		return moves;
	}

	char Knight::notation() const {
		return isWhite() ? 'N' : 'n';
	}
}