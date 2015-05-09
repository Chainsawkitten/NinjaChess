#include "Position.h"

namespace Chess {
	Position::Position() : Position(0, 0) {

	}

	Position::Position(int x, int y) {
		this->x = x;
		this->y = y;
	}
}