#ifndef POSITION_H
#define POSITION_H

namespace Chess {
	/// A position on the board.
	struct Position {
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
	};
}

#endif POSITION_H