#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ninja Chess");
	window.setVerticalSyncEnabled(true);
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return EXIT_SUCCESS;
}