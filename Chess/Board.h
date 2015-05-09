#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"

namespace Chess {
	/// Chess board.
	class Board {
		public:
			/// Create new board.
			Board();

			/// Free allocated resources.
			~Board();

			/// Get the piece at a certain position.
			/**
			 * @param position Position to get piece at.
			 * @return The piece or nullptr.
			 */
			Piece* getPiece(const Position& position) const;

		private:
			Piece* pieces[8][8];
	};
}

#endif