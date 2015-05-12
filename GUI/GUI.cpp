#include "GUI.h"

using namespace sf;
using namespace Chess;

namespace GUI {
	GUI::GUI(int width, int height, Board& board) : board(board) {
		this->width = width;
		this->height = height;

		window = new RenderWindow(VideoMode(width, height), "Ninja Chess");
		window->setVerticalSyncEnabled(true);

		font.loadFromFile("Resources/stchess.ttf");

		text.setFont(font);
		text.setCharacterSize(height / 8);
		text.setColor(Color::Black);

		notationMap['P'] = "A";
		notationMap['p'] = "a";
		notationMap['R'] = "D";
		notationMap['r'] = "d";
		notationMap['N'] = "B";
		notationMap['n'] = "b";
		notationMap['B'] = "C";
		notationMap['b'] = "c";
		notationMap['Q'] = "E";
		notationMap['q'] = "e";
		notationMap['K'] = "F";
		notationMap['k'] = "f";
	}

	GUI::~GUI() {
		delete window;
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

		bool pressed = Mouse::isButtonPressed(Mouse::Left);
		if (pressed && !mousePressed) {
			Vector2i mousePos = Mouse::getPosition(*window);
			Position tempPos(mousePos.x * 8 / width, mousePos.y * 8 / height);
			if (tempPos.valid()) {
				if (board.getPiece(tempPos) != nullptr) {
					selection = tempPos;
					selected = true;
				}
			}
		}

		mousePressed = pressed;
	}

	void GUI::render() {
		window->clear();

		drawBoard();
		drawPieces();

		window->display();
	}

	void GUI::drawBoard() {
		Color brightSquare(224, 217, 190);
		Color darkSquare(152, 145, 135);

		RectangleShape square(Vector2f(width / 8.f, height / 8.f));
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				square.setPosition(x * width / 8.f, y * height / 8.f);

				if (selected && selection == Position(x, y))
					square.setFillColor(Color::Yellow);
				else if ((x + y) % 2 == 0)
					square.setFillColor(brightSquare);
				else
					square.setFillColor(darkSquare);

				window->draw(square);
			}
		}
	}

	void GUI::drawPieces() {
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				Piece* piece = board.getPiece(Position(x, 7-y));
				if (piece != nullptr) {
					text.setPosition(Vector2f(x * width / 8.f, (y - 0.2f) * width / 8.f));
					text.setString(notationMap[piece->notation()]);
					window->draw(text);
				}
			}
		}
	}
}