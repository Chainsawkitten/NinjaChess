#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include "King.h"

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

			/// Move a piece from one position to another.
			/**
			 * @param oldPosition %Position where the piece is.
			 * @param newPosition %Position to move the piece to.
			 * @return Whether the move was successful
			 */
			bool move(const Position& oldPosition, const Position& newPosition);

		private:
			Piece* pieces[8][8];

			King* whiteKing;
			King* blackKing;

			int turn = 0;
	};
}

#endif