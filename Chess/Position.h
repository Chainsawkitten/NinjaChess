#ifndef POSITION_H
#define POSITION_H

namespace Chess {
	/// A position on the board.
	class Position {
		public:
			/// X-position.
			int x;
			/// Y-position.
			int y;

			/// Create new position at 0, 0.
			Position();

			/// Create new position.
			/**
			 * @param x X-position (letters).
			 * @param y Y-position (numbers).
			 */
			Position(int x, int y);

			/// Check if position is within bounds.
			/**
			 * @return Whether the position is within the bounds of the board
			 */
			bool valid() const;
	};

	/// Overloaded == for Position.
	bool operator==(const Position& lhs, const Position& rhs);

	/// Overloaded != for Position.
	bool operator!=(const Position& lhs, const Position& rhs);
}

#endif POSITION_H