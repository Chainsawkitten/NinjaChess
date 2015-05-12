#ifndef MAIN_H
#define MAIN_H

#include <SFML/Graphics.hpp>

/// Main function.
int main();

/// Draw checkerboard.
/**
 * @param window %Window to draw on.
 */
void drawBoard(sf::RenderWindow& window);

#endif