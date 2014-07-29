#ifndef GRIDCELL_HPP
#define GRIDCELL_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class GridCell
{
private:
	sf::RectangleShape mRect;
	sf::Color mColor;

	bool mIsWalkable;

	std::vector<GridCell*> mNeighbors;
	sf::Vector2f mArrayCoords;
	
	void fillNeighbors(std::vector<GridCell*>& cells, int beginX, int endX, int beginY, int endY);

public:
	GridCell(int x, int y, int width, int height, int arrayCoordX, int arrayCoordY, sf::Color color=sf::Color::Black, bool isWalkable=true);

	void setColor(sf::Color color);

	const sf::RectangleShape getRect();
	const sf::Vector2f getPosition() const;

	const bool getWalkable() const;
	void setWalkable(bool walkable);

	void setNeighbors(std::vector<GridCell*>& cells);
	std::vector<GridCell*>& getNeighbors();

	GridCell* mParent;

	~GridCell();
};

#endif
