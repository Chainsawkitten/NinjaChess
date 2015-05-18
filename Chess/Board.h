#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include "King.h"
#include "Pawn.h"

namespace Chess {
	/// Game states.
	enum class GameState { WHITEPLAYS, BLACKPLAYS, WHITEWIN, BLACKWIN, DRAW };

	/// Types a pawn can be promoted to.
	enum class PromoteTypes { ROOK, KNIGHT, BISHOP, QUEEN };

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

			/// Gets the board's current state.
			/**
			 * @return The board's current state
			 */
			GameState getState() const;

			/// Checks if a pawn needs to promote.
			/**
			 * @return Whether a pawn needs to be promoted
			 */
			bool signalPromote();

			/// Promotes a piece
			/**
			 * @return void
			 */
			void promotePawn(Piece* pawn, PromoteTypes type);

			/// Get the king of a certain color.
			/**
			 * @param white Whether to get the white or black king.
			 * @return The king of the specified color
			 */
			King* getKing(bool white) const;

		private:
			Pawn* lastMovedPawn = nullptr;
			Piece* pieces[8][8];
			bool needsToPromote = false;
			King* whiteKing;
			King* blackKing;
			GameState state = GameState::WHITEPLAYS;

			int turn = 0;
	};
}

#endif