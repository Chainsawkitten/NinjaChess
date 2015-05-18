#include "GUI.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"

#include <ctype.h>


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
		if (showPromoteWindow == false){
			updateGame();
		}
		else{
			updatePromote();
		}
	}

	void GUI::updateGame(){
		Event event;
		while (window->pollEvent(event)) {
			if (event.type == Event::Closed)
				window->close();
		}

		bool pressed = Mouse::isButtonPressed(Mouse::Left);
		if (pressed && !mousePressed) {
			Vector2i mousePos = Mouse::getPosition(*window);
			Position tempPos(mousePos.x * 8 / width, mousePos.y * 8 / height);
			tempPos.y = 7 - tempPos.y;
			if (tempPos.valid()) {
				Piece* tempPiece = board.getPiece(tempPos);
				if (selected) {
					Piece* selectedPiece = board.getPiece(selection);
					if (selectedPiece->isLegal(board, tempPos)) {
						board.move(selection, tempPos);
						lastMovedPiece = selectedPiece;
						selected = false;
					} else if (tempPiece != nullptr) {
						if (tempPiece->isWhite() && (board.getState() == GameState::BLACKPLAYS))
							return;
						else if (!tempPiece->isWhite() && (board.getState() == GameState::WHITEPLAYS))
							return;
						selection = tempPos;
						selected = true;
						highlights = tempPiece->legalMoves(board);
					}
				} else if (tempPiece != nullptr) {
					if (tempPiece->isWhite() && (board.getState() == GameState::BLACKPLAYS))
						return;
					else if (!tempPiece->isWhite() && (board.getState() == GameState::WHITEPLAYS))
						return;
					selection = tempPos;
					selected = true;
					highlights = tempPiece->legalMoves(board);
				}
			}
		}

		if (board.signalPromote())
			showPromoteWindow = true;

		mousePressed = pressed;
	}

	void GUI::updatePromote() {
		Event event;
		while (window->pollEvent(event)) {
			if (event.type == Event::Closed)
				window->close();
		}

		bool pressed = Mouse::isButtonPressed(Mouse::Left);
		if (pressed && !mousePressed){
			Vector2i mousePos = Mouse::getPosition(*window);
			Position tempPosition = lastMovedPiece->getPosition();
			bool tempIsWhite = lastMovedPiece->isWhite();
			if ((mousePos.x < width / 2.f) && (mousePos.y < height / 2.f)){
				text.setCharacterSize(height / 8);
				board.promotePawn(lastMovedPiece, PromoteTypes::QUEEN);
				showPromoteWindow = false;
			} else if ((mousePos.x > width / 2.f) && (mousePos.y < height / 2.f)){
				text.setCharacterSize(height / 8);
				board.promotePawn(lastMovedPiece, PromoteTypes::ROOK);
				showPromoteWindow = false;
			} else if ((mousePos.x < width / 2.f) && (mousePos.y > height / 2.f)){
				text.setCharacterSize(height / 8);
				board.promotePawn(lastMovedPiece, PromoteTypes::BISHOP);
				showPromoteWindow = false;
			} else if ((mousePos.x > width / 2.f) && (mousePos.y > height / 2.f)){
				text.setCharacterSize(height / 8);
				board.promotePawn(lastMovedPiece, PromoteTypes::KNIGHT);
				showPromoteWindow = false;
			}
		}
		mousePressed = pressed;
	}

	void GUI::render() {
		window->clear();
		if (!showPromoteWindow) {
			drawBoard();
			drawPieces();
		} else {
			drawPromote();
		}
		window->display();
	}

	void GUI::drawPromote() {
		Color brightSquare(224, 217, 190);
		Color darkSquare(152, 145, 135);
		RectangleShape square(Vector2f(width / 2.f, width / 2.f));
		for (int x = 0; x < 2; x++) {
			for (int y = 0; y < 2; y++) {
				square.setPosition(x * width / 2.f, y * height / 2.f);

				if ((x + y) % 2 == 0)
					square.setFillColor(brightSquare);
				else
					square.setFillColor(darkSquare);

				window->draw(square);
			}
		}

		text.setCharacterSize(height / 2);
		char promoteNotation[4] = { 'q', 'r', 'b', 'n' };
		for (int x = 0; x < 2; x++) {
			for (int y = 0; y < 2; y++) {
				text.setPosition(Vector2f(x * width / 2.f, (y - 0.2f) * width / 2.f));
				char notation = promoteNotation[y * 2 + x];
				if (lastMovedPiece->isWhite())
					notation = toupper(notation);
				text.setString(notationMap[notation]);
				window->draw(text);
			}
		}
	}

	void GUI::drawBoard() {
		Color brightSquare(224, 217, 190);
		Color darkSquare(152, 145, 135);

		RectangleShape square(Vector2f(width / 8.f, height / 8.f));
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				square.setPosition(x * width / 8.f, y * height / 8.f);

				if (selected && selection == Position(x, 7 - y))
					square.setFillColor(Color::Yellow);
				else if (selected && highlighted(Position(x, 7 - y)))
					square.setFillColor(Color::Green);
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

	bool GUI::highlighted(const Position& position) {
		for (Position move : highlights) {
			if (move == position)
				return true;
		}

		return false;
	}
}