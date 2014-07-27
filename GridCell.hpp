#ifndef GRIDCELL_HPP
#define GRIDCELL_HPP

#include <SFML/Graphics.hpp>

class GridCell
{
private:
	sf::RectangleShape mRect;
	sf::Color mColor;

public:
	GridCell(int x, int y, int width, int height, sf::Color color);

	const sf::RectangleShape getRect();

	~GridCell();
};

#endif
