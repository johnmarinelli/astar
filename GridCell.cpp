#include "GridCell.hpp"
#include "Utilities.hpp"
#include <cmath>

GridCell::GridCell(int x, int y, int width, int height, int arrayCoordX, int arrayCoordY, sf::Color color, bool isWalkable) : mRect(sf::Vector2f(width, height)), mArrayCoords(arrayCoordX, arrayCoordY), mColor(color), mIsWalkable(isWalkable), mParent(NULL)
{
	mRect.setPosition(x, y);
	mRect.setFillColor(color);
}

void GridCell::setColor(sf::Color color)
{
	mColor = color;
	mRect.setFillColor(mColor);
}

const sf::RectangleShape GridCell::getRect()
{
	return mRect;
}

const sf::Vector2f GridCell::getPosition() const
{
	return mRect.getPosition();
}

const bool GridCell::getWalkable() const
{
	return mIsWalkable;
}

void GridCell::setWalkable(bool walkable)
{
	mIsWalkable = walkable;
	setColor(walkable ? sf::Color::Black : sf::Color::Blue);
}

void GridCell::fillNeighbors(std::vector<GridCell*>& cells, int beginX, int endX, int beginY, int endY)
{
	int width = std::ceil((float)WINDOW_WIDTH / (float)CELL_WIDTH), i = 0, j = 0; 

	for(i = beginY; i <= endY; i++){
		for(j = beginX; j <= endX; j++){
			mNeighbors.push_back(cells.at(j+i*width));
		}
		j = beginX;
	}
}

void GridCell::setNeighbors(std::vector<GridCell*>& cells)
{
	int width = std::ceil((float)WINDOW_WIDTH / (float)CELL_WIDTH);
	int height = std::ceil((float)WINDOW_HEIGHT / (float)CELL_HEIGHT);

	int beginX = 0, beginY = 0, endX = 0, endY = 0;

	if(mArrayCoords.x != 0 && mArrayCoords.y != 0 && mArrayCoords.x != width-1 && mArrayCoords.y != height-1){
		//inside
		beginX = mArrayCoords.x - 1;
		beginY = mArrayCoords.y - 1;
		endX = mArrayCoords.x + 1;
		endY = mArrayCoords.y + 1;
	}
	else if(mArrayCoords.x == 0){
		if(mArrayCoords.y == 0){
			//top left
			beginX = mArrayCoords.x;
			beginY = mArrayCoords.y;
			endX = mArrayCoords.x + 1;
			endY = mArrayCoords.y + 1;
		}
		else if(mArrayCoords.y == height-1){
			//bottom left
			beginX = mArrayCoords.x;	
			beginY = mArrayCoords.y-1;
			endX = beginX + 1;
			endY = mArrayCoords.y;
		}
		else{
			//left side
			beginX = mArrayCoords.x;
			beginY = mArrayCoords.y - 1;
			endX = mArrayCoords.x + 1;
			endY = mArrayCoords.y + 1;
		}
	}
	else if(mArrayCoords.x == width-1){
		if(mArrayCoords.y == 0){
			//top right
			beginX = mArrayCoords.x - 1;
			beginY = mArrayCoords.y;
			endX = mArrayCoords.x;
			endY = mArrayCoords.y + 1;
		}
		else if(mArrayCoords.y == height-1){
			//bottom right
			beginX = mArrayCoords.x - 1;
			beginY = mArrayCoords.y - 1;
			endX = mArrayCoords.x;
			endY = mArrayCoords.y;
		}
		else{
			//right side
			beginX = mArrayCoords.x - 1;
			beginY = mArrayCoords.y - 1;
			endX = mArrayCoords.x;
			endY = mArrayCoords.y + 1;
		}
	}
	//checking endY != 0 because then it would have been set earlier already
	else if(mArrayCoords.y == 0 && mArrayCoords.x > 0 && mArrayCoords.x < width-1){
		//top side
		beginX = mArrayCoords.x - 1;
		beginY = mArrayCoords.y;
		endX = mArrayCoords.x + 1;
		endY = mArrayCoords.y + 1;
	}
	else if(mArrayCoords.y == height-1 && mArrayCoords.x > 0 && mArrayCoords.x < width-1){
		//bottom side
		beginX = mArrayCoords.x - 1;
		beginY = mArrayCoords.y - 1;
		endX = mArrayCoords.x + 1;
		endY = mArrayCoords.y;
	}

	fillNeighbors(cells, beginX, endX, beginY, endY);
}

std::vector<GridCell*>& GridCell::getNeighbors()
{
	return mNeighbors;
}

GridCell::~GridCell()
{
}


