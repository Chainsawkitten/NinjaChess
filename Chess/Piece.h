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
			 */
			Piece(const Position& position);

		protected:
			Position position;
	};
}

#endif