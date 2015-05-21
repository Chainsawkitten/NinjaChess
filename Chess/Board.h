#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include "King.h"
#include "Pawn.h"
#include <map>

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

			/// Check whether king will be checked after a move.
			/**
			 * @param oldPosition %Position where the piece is.
			 * @param newPosition %Position to move the piece to.
			 * @return Whether the king is in check after the move
			 */
			bool willLeaveKingChecked(const Position& oldPosition, const Position& newPosition);

			/// Gets the board's current state.
			/**
			 * @return The board's current state
			 */
			GameState getState() const;

			/// Checks if a pawn needs to promote.
			/**
			 * @return Whether a pawn needs to be promoted
			 */
			bool mustPromote();

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
			
			/// Get FEN notation string describing the board
			/**
			* @return FEN notated string
			*/
			std::string toFENString(bool addExtraData) const;

			/// Get enPassantPossible
			/**
			*	@return position of valid en passant move
			*/
			Position getEnPassantPossible()const;

		private:
			Piece* pieces[8][8];							//A representation of the board as a 8x8 array of pieces.
			bool needsToPromote = false;					
			int halfMovesSinceCapture = 0;					//Stores how many half-moves have been made since last capture.
			Position enPassantPossible = Position(-1,-1);	//Stores the location where en-passant is possible
			GameState state = GameState::WHITEPLAYS;		//The games state.
			void addBoardToMap();							//Adds board as a FEN-notated string to the previousBoards map.
			bool isThreeFoldRepitition();					//Checks for threefold repetition of a position.
			bool isFiftyMoveSincePawnOrCapture() const;		//Checks for fifty moves since capture or pawn move.
			void checkWin();
			bool sufficientMaterial() const;				// Checks if there's sufficient material for mate.
			std::map<std::string, int> previousBoards;		//Stores previous board in order to check for threefold repetition.
			int turn = 0;
	};
}

#endif