#include "GUI.h"

using namespace sf;

namespace GUI {
	GUI::GUI(int width, int height, Chess::Board& board) : board(board) {
		this->width = width;
		this->height = height;

		window = new RenderWindow(VideoMode(width, height), "Ninja Chess");
		window->setVerticalSyncEnabled(true);

		font.loadFromFile("Resources/stchess.ttf");

		text.setFont(font);
		text.setCharacterSize(height / 8);
		text.setColor(Color::Black);
	}

	bool GUI::isOpen() const {
		return window->isOpen();
	}

	void GUI::update() {
		Event event;
		while (window->pollEvent(event)) {
			if (event.type == Event::Closed)
				window->close();
		}
	}

	void GUI::render() {
		window->clear();

		drawBoard();

		text.setString("ABCDEFabcdef");
		window->draw(text);

		window->display();
	}

	void GUI::drawBoard() {
		Color brightSquare(224, 217, 190);
		Color darkSquare(152, 145, 135);

		RectangleShape square(Vector2f(width / 8.f, height / 8.f));
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				square.setPosition(x * width / 8.f, y * height / 8.f);

				if ((x + y) % 2 == 0)
					square.setFillColor(brightSquare);
				else
					square.setFillColor(darkSquare);

				window->draw(square);
			}
		}
	}
}