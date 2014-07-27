#include "GridCell.hpp"

GridCell::GridCell(int x, int y, int width, int height, sf::Color color = sf::Color::White) : mRect(sf::Vector2f(width, height)), mColor(color)
{
	mRect.setPosition(x, y);
	mRect.setFillColor(color);
}

const sf::RectangleShape GridCell::getRect()
{
	return mRect;
}

GridCell::~GridCell()
{
}


