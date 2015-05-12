#include "GUI.h"
#include <Board.h>

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400

using namespace sf;

int main() {
	Chess::Board board;
	GUI::GUI gui(WINDOW_WIDTH, WINDOW_HEIGHT, board);

	while (gui.isOpen()) {
		gui.update();
		gui.render();
	}

	return EXIT_SUCCESS;
}