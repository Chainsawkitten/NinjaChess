#include "main.h"

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400

using namespace sf;

int main() {
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ninja Chess");
	window.setVerticalSyncEnabled(true);

	Font font;
	font.loadFromFile("Resources/stchess.ttf");

	Text text;
	text.setFont(font);
	text.setCharacterSize(WINDOW_HEIGHT / 8.f);
	text.setColor(Color::Black);

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		
		drawBoard(window);

		text.setString("ABCDEFabcdef");
		window.draw(text);

		window.display();
	}

	return EXIT_SUCCESS;
}

void drawBoard(RenderWindow& window) {
	Color brightSquare(224, 217, 190);
	Color darkSquare(152, 145, 135);

	RectangleShape square(Vector2f(WINDOW_WIDTH / 8.f, WINDOW_HEIGHT / 8.f));
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			square.setPosition(x * WINDOW_WIDTH / 8.f, y * WINDOW_HEIGHT / 8.f);

			if ((x + y) % 2 == 0)
				square.setFillColor(brightSquare);
			else
				square.setFillColor(darkSquare);

			window.draw(square);
		}
	}
}