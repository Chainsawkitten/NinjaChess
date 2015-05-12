#include "Knight.h"
#include "Board.h"

namespace Chess {
	Knight::Knight(const Position& position, bool white) : Piece(position, white) {

	}

	std::vector<Position> Knight::legalMoves(const Board& board) const {
		std::vector<Position> moves, testMoves;
		testMoves.push_back(Position(position.x + 1, position.y + 2));
		testMoves.push_back(Position(position.x - 1, position.y + 2));
		testMoves.push_back(Position(position.x + 1, position.y - 2));
		testMoves.push_back(Position(position.x - 1, position.y - 2));

		testMoves.push_back(Position(position.x + 2, position.y + 1));
		testMoves.push_back(Position(position.x + 2, position.y - 1));
		testMoves.push_back(Position(position.x - 2, position.y + 1));
		testMoves.push_back(Position(position.x - 2, position.y - 1));
		for (auto move : testMoves) {
			if (move.valid() && ((board.getPiece(move) == nullptr) || (isWhite() != board.getPiece(move)->isWhite())))
				moves.push_back(move);
		}
		return moves;
	}

	char Knight::notation() const {
		return isWhite() ? 'N' : 'n';
	}
}