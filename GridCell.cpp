#include "GridCell.hpp"
#include "Utilities.hpp"
#include <cmath>

GridCell::GridCell(int x, int y, int width, int height, int arrayCoordX, int arrayCoordY, sf::Color color, bool isWalkable) : mRect(sf::Vector2f(width, height)), mArrayCoords(arrayCoordX, arrayCoordY), mColor(color), mIsWalkable(isWalkable), mGValue(0), mHValue(0), mFValue(0), mParent(NULL)
{
	mRect.setPosition(x, y);
	mRect.setFillColor(color);
}

void GridCell::setColor(sf::Color color)
{
	mColor = color;
	mRect.setFillColor(mColor);
}

const sf::Vector2f GridCell::getArrayCoords()
{
	return mArrayCoords;
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
	
		mPosition = Position::MIDDLE;
	}
	else if(mArrayCoords.x == 0){
		if(mArrayCoords.y == 0){
			//top left
			beginX = mArrayCoords.x;
			beginY = mArrayCoords.y;
			endX = mArrayCoords.x + 1;
			endY = mArrayCoords.y + 1;
			
			mPosition = Position::NW_CORNER;
		}
		else if(mArrayCoords.y == height-1){
			//bottom left
			beginX = mArrayCoords.x;	
			beginY = mArrayCoords.y-1;
			endX = beginX + 1;
			endY = mArrayCoords.y;

			mPosition = Position::SW_CORNER;
		}
		else{
			//left side
			beginX = mArrayCoords.x;
			beginY = mArrayCoords.y - 1;
			endX = mArrayCoords.x + 1;
			endY = mArrayCoords.y + 1;
	
			mPosition = Position::LEFTSIDE;
		}
	}
	else if(mArrayCoords.x == width-1){
		if(mArrayCoords.y == 0){
			//top right
			beginX = mArrayCoords.x - 1;
			beginY = mArrayCoords.y;
			endX = mArrayCoords.x;
			endY = mArrayCoords.y + 1;

			mPosition = Position::NE_CORNER;
		}
		else if(mArrayCoords.y == height-1){
			//bottom right
			beginX = mArrayCoords.x - 1;
			beginY = mArrayCoords.y - 1;
			endX = mArrayCoords.x;
			endY = mArrayCoords.y;

			mPosition = Position::SE_CORNER;
		}
		else{
			//right side
			beginX = mArrayCoords.x - 1;
			beginY = mArrayCoords.y - 1;
			endX = mArrayCoords.x;
			endY = mArrayCoords.y + 1;

			mPosition = Position::RIGHTSIDE;
		}
	}
	//checking endY != 0 because then it would have been set earlier already
	else if(mArrayCoords.y == 0 && mArrayCoords.x > 0 && mArrayCoords.x < width-1){
		//top side
		beginX = mArrayCoords.x - 1;
		beginY = mArrayCoords.y;
		endX = mArrayCoords.x + 1;
		endY = mArrayCoords.y + 1;
		
		mPosition = Position::TOPSIDE;
	}
	else if(mArrayCoords.y == height-1 && mArrayCoords.x > 0 && mArrayCoords.x < width-1){
		//bottom side
		beginX = mArrayCoords.x - 1;
		beginY = mArrayCoords.y - 1;
		endX = mArrayCoords.x + 1;
		endY = mArrayCoords.y;

		mPosition = Position::BOTTOMSIDE;
	}

	fillNeighbors(cells, beginX, endX, beginY, endY);
}

std::vector<GridCell*>& GridCell::getNeighbors()
{
	return mNeighbors;
}

bool GridCell::isDiagonalNeighbor(GridCell* const neighbor)
{
	bool isDiagonal = false;

	typedef std::numeric_limits<std::vector<GridCell*>::size_type> Invalid;
	const std::vector<GridCell*>::const_iterator pos = std::find(mNeighbors.begin(), mNeighbors.end(), neighbor);

	std::vector<GridCell*>::size_type index = Invalid::max();

	if(pos != mNeighbors.end()){
		index = pos - mNeighbors.begin();
	}

	switch(mPosition)
	{
		case Position::NW_CORNER: 
			if(index == 3){
				isDiagonal = true;	
			}
			break;
		case Position::NE_CORNER:
			if(index == 2){
				isDiagonal = true;
			}
			break;
		case Position::SW_CORNER:
			if(index == 1){
				isDiagonal = true;
			}
			break;
		case Position::SE_CORNER:
			if(index == 0){
				isDiagonal = true;
			}
			break;
		case Position::TOPSIDE:
			if(index == 3 || index == 5){
				isDiagonal = true;
			}
			break;
		case Position::BOTTOMSIDE:
			if(index == 0 || index == 2){
				isDiagonal = true;
			}
			break;
		case Position::LEFTSIDE:
			if(index == 1 || index == 5){
				isDiagonal = true;
			}
			break;
		case Position::RIGHTSIDE:
			if(index == 0 || index == 4){
				isDiagonal = true;
			}
			break;
		case Position::MIDDLE:
			if(index == 0 || index == 2 || index == 6 || index == 8){
				isDiagonal = true;	
			}
			break;
		default: isDiagonal = false; break;
	}

	return isDiagonal;
}

GridCell::~GridCell()
{
}


