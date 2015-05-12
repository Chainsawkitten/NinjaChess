#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

namespace Chess {
	/// Pawn.
	class Pawn : public Piece {
		public:
			/// Create pawn.
			/**
			* @param position Position on the board.
			* @param white Whether the piece belongs to the white player.
			*/
			Pawn(const Position& position, bool white);

			/// Get valid moves.
			/**
			* @param board %Board.
			* @return A list of all the legal moves.
			*/
			std::vector<Position> legalMoves(const Board& board) const;

			/// Get the notation of the piece.
			/**
			* @return FEN-notation of the piece.
			* @see http://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
			*/
			char notation() const;
	private:
		bool _hasMoved;
		bool lastMoveWasDouble;

	};
}

#endif