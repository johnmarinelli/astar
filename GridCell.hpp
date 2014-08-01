#ifndef GRIDCELL_HPP
#define GRIDCELL_HPP

#include <vector>
#include <SFML/Graphics.hpp>

enum Position 
{
	NW_CORNER, NE_CORNER, SW_CORNER, SE_CORNER,
	TOPSIDE,
	BOTTOMSIDE,
	LEFTSIDE,
	RIGHTSIDE,	
	MIDDLE,	
};

enum Neighbors 
{
	NW, N, NE,
	W, SELF, E,
	SW, S, SE,
};

class GridCell
{
private:
	Position mPosition;

	sf::RectangleShape mRect;
	sf::Color mColor;

	bool mIsWalkable;

	std::vector<GridCell*> mNeighbors;
	sf::Vector2f mArrayCoords;
	
	void fillNeighbors(std::vector<GridCell*>& cells, int beginX, int endX, int beginY, int endY);

public:
	int mGValue, mHValue, mFValue;

	GridCell(int x, int y, int width, int height, int arrayCoordX, int arrayCoordY, sf::Color color=sf::Color::Black, bool isWalkable=true);

	void setColor(sf::Color color);

	const sf::Vector2f getArrayCoords();

	const sf::RectangleShape getRect();
	const sf::Vector2f getPosition() const;

	const bool getWalkable() const;
	void setWalkable(bool walkable);

	void setNeighbors(std::vector<GridCell*>& cells);
	std::vector<GridCell*>& getNeighbors();

	bool isDiagonalNeighbor(GridCell* const neighbor);

	GridCell* mParent;

	~GridCell();
};

#endif
