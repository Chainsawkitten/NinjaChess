#include "main.h"

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400

using namespace sf;

int main() {
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ninja Chess");
	window.setVerticalSyncEnabled(true);

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		
		drawBoard(window);

		window.display();
	}

	return EXIT_SUCCESS;
}

void drawBoard(RenderWindow& window) {
	RectangleShape square(Vector2f(WINDOW_WIDTH / 8.f, WINDOW_HEIGHT / 8.f));
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			square.setPosition(x * WINDOW_WIDTH / 8.f, y * WINDOW_HEIGHT / 8.f);

			if ((x + y) % 2 == 0)
				square.setFillColor(Color::Green);
			else
				square.setFillColor(Color::Red);

			window.draw(square);
		}
	}
}