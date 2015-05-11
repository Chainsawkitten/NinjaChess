#ifndef PIECE_H
#define PIECE_H

#include "Position.h"
#include <vector>

namespace Chess {
	class Board;

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

			/// Did this piece (only applies to pawn) move two spaces last move?
			/**
			* @return Whether pawn's last move was two spaces or not
			*/
			bool lastMoveDouble() const;

			/// Get valid moves.
			/**
			 * @param board %Board.
			 * @return A list of all the valid moves.
			 */
			virtual std::vector<Position> validMoves(const Board& board) const;

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
			///Boolean for determining if 'En Passant' is valid move
			bool lastMoveWasDouble;
			bool white;


	};
}

#endif