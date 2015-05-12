#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <Board.h>

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
			void drawBoard();
			void drawPieces();

			int width, height;
			Chess::Board& board;

			sf::RenderWindow* window;
			sf::Font font;
			sf::Text text;
	};
}

#endif