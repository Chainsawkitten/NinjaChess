#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <Board.h>
#include <Piece.h>
#include <map>

namespace GUI {
	class GUI {
		public:
			/// Create %GUI.
			/**
			 * @param width Width of the %GUI.
			 * @param height Height of the %GUI.
			 * @param board Chess board.
			 */
			GUI(int width, int height, Chess::Board& board);

			/// Free allocated resources.
			~GUI();

			/// Get whether the %GUI window is still open.
			/**
			 * @return Whether the %GUI window is still open.
			 */
			bool isOpen() const;

			/// Update.
			void update();
			/// Render the %GUI.
			void render();

			private:
				void drawBoard();											//Draws the board
				void drawPieces();											//Draws the pieces on top of the board.
				void drawPromote();											//Draws the promote window
				void updatePromote();										//Updates the promote window
				void updateGame();											//Updates the game
				void drawMessage();											//Draws a message (win, lose, draw)
				void updateMessage();										//Updates the message (Does nothing right now)
				bool highlighted(const Chess::Position& position);			//Returns wheter a position is highlighted

				int width, height;
				Chess::Board& board;

				Chess::Piece* lastMovedPiece = nullptr;

				std::map<char, const char*> notationMap;					//Map that contains FEN-notation to font alphabet

				sf::RenderWindow* window;
				bool showPromoteWindow = false;
				sf::Font chessFont;
				sf::Font messageFont;
				sf::Text chessText;
				sf::Text messageText;

				Chess::Position selection;
				bool selected;
				bool mousePressed;

				std::vector<Chess::Position> highlights;					//Contains all the positions that are highlighted
			};
}

#endif