#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include "King.h"

namespace Chess {
	enum class GameState{WHITEPLAYS, BLACKPLAYS, WHITEWIN, BLACKWIN, DRAW};
	enum class PromoteTypes{ROOK, KNIGHT, BISHOP, QUEEN};
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

			/// Returns the boards current state
			/**
			* @return Returns the boards current state
			*/
			GameState getState() const;

			/// Checks if a pawn needs to promote
			/**
			* @return Returns true if a pawn needs to be promoted
			*/
			bool signalPromote();

			/// Promotes a piece
			/**
			* @return void
			*/
			void promotePawn(Piece* pawn, PromoteTypes type);

			/// Get king
			/**
			* @param white or black king
			* @return king
			*/
			King* getKing(bool isWhite)const;
		private:
			Piece* pieces[8][8];
			bool needsToPromote = false;
			King* whiteKing;
			King* blackKing;
			GameState state = GameState::WHITEPLAYS;

			int turn = 0;
	};
}

#endif