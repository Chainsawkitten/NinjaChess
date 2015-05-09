#ifndef PIECE_H
#define PIECE_H

#include "Position.h"

namespace Chess {
	/// A piece on the board.
	class Piece {
		public:
			/// Create new piece.
			/**
			 * @param position Position on the board.
			 * @param white Whether the piece belongs to the white player.
			 */
			Piece(const Position& position, bool white);

			/// Whether the piece belongs to the white player.
			/**
			 * @return Whether the piece belongs to the white player
			 */
			bool isWhite() const;

			/// Get the notation of the piece.
			/**
			 * @return FEN-notation of the piece.
			 * @see http://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
			 */
			virtual char notation() const = 0;

		protected:
			/// Position on the board.
			Position position;

		private:
			bool white;

	};
}

#endif