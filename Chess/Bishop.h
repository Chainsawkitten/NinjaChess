#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

namespace Chess {
	/// Bishop.
	class Bishop : public Piece {
	public:
		/// Create bishop.
		/**
		 * @param position Position on the board.
		 * @param white Whether the piece belongs to the white player.
		 */
		Bishop(const Position& position, bool white);

		/// Get possible moves.
		/**
		* Gets moves without checking if it'll leave the king in check.
		* @param board %Board.
		* @return A lost of all potential moves.
		*/
		std::vector<Position> moves(const Board& board) const;

		/// Get the notation of the piece.
		/**
		 * @return FEN-notation of the piece.
		 * @see http://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
		 */
		char notation() const;
	};
}

#endif