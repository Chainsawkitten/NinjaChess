#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"

namespace Chess {
	/// Chess board.
	class Board {
		public:
			/// Create new board.
			Board();

			/// Free allocated resources.
			~Board();

		private:
			Piece* pieces[8][8];
	};
}

#endif