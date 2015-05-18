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

			/// Move the piece to another position.
			/**
			 * @param newPosition %Position to move the piece to.
			 */
			virtual void move(const Position& newPosition);

			/// Get whether a move is legal.
			/**
			 * @param board %Board.
			 * @param newPosition %Position to move to.
			 * @return Whether it's a legal move
			 */
			bool isLegal(const Board& board, const Position& newPosition) const;

			/// Get legal moves.
			/**
			 * Makes sure the move won't leave the king in check.
			 * @param board %Board.
			 * @return A list of all the legal moves.
			 */
			std::vector<Position> legalMoves(const Board& board) const;

			/// Get possible moves.
			/**
			 * Gets moves without checking if it'll leave the king in check.
			 * @param board %Board.
			 * @return A lost of all potential moves.
			 */
			virtual std::vector<Position> moves(const Board& board) const;

			/// Get the notation of the piece.
			/**
			 * @return FEN-notation of the piece.
			 * @see http://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
			 */
			virtual char notation() const = 0;

			Position getPosition() const;

		protected:
			/// Position on the board.
			Position position;

		private:
			bool white;


	};
}

#endif