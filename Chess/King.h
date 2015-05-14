#ifndef KING_H
#define KING_H

#include "Piece.h"

namespace Chess {
	class Board;

	/// King.
	class King : public Piece {
		public:
			/// Create king.
			/**
			* @param position Position on the board.
			* @param white Whether the piece belongs to the white player.
			*/
			King(const Position& position, bool white);
			
			///Check if piece has moved
			/**
			* @return whether piece has moved or not
			*/
			bool hasMoved()const;

			/// Test if king is checked
			/**
			* @param board %Board
			* @return whether king is checked or not
			*/
			bool isChecked(const Board& board) const;

			/// Move the piece to another position.
			/**
			* @param newPosition %Position to move the piece to.
			*/
			void move(const Position& newPosition);

			/// Tests if castling results in passing or landing on a check
			/**
			* @param right or left rook selection for castling
			*/
			bool castlingTest(bool right) const;

			/// Get legal moves.
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
	};
}

#endif