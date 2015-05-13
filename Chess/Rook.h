#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

namespace Chess {
	/// Rook.
	class Rook : public Piece {
	public:
		/// Create rook.
		/**
		* @param position Position on the board.
		* @param white Whether the piece belongs to the white player.
		*/
		Rook(const Position& position, bool white);

		/// Move the piece to another position.
		/**
		* @param newPosition %Position to move the piece to.
		*/
		void move(const Position& newPosition);

		/// Get the notation of the piece.
		/**
		* @return FEN-notation of the piece.
		* @see http://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
		*/
		char notation() const;

		/// Get legal moves.
		/**
		* @param board %Board.
		* @return A list of all the legal moves.
		*/
		std::vector<Position> legalMoves(const Board& board) const;
	private:
		bool _hasMoved;
	};
}

#endif