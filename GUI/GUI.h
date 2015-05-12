#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>

namespace GUI {
	class GUI {
		public:
			/// Create %GUI.
			/**
			 * @param width Width of the %GUI.
			 * @param height Height of the %GUI.
			 */
			GUI(int width, int height);

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

			int width, height;

			sf::RenderWindow* window;
			sf::Font font;
			sf::Text text;
	};
}

#endif