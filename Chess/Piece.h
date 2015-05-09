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
			bool isWhite() const;

		protected:
			/// Position on the board.
			Position position;

		private:
			bool white;

	};
}

#endif