#include "Position.h"

namespace Chess {
	Position::Position() : Position(0, 0) {

	}

	Position::Position(int x, int y) {
		this->x = x;
		this->y = y;
	}

	bool Position::valid() const {
		return (x >= 0 && x <= 7 && y >= 0 && y <= 7);
	}
}