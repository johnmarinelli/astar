#include "World.hpp"
#include <iostream>

#include <vector>
#include <map>

World::World(sf::RenderWindow& window) : mRenderTarget(&window)
{
}

void World::init()
{
	int arrayCoordX = 0, arrayCoordY = 0;
	for(int i = 0; i < WINDOW_HEIGHT; i += CELL_HEIGHT){
		for(int j = 0; j < WINDOW_WIDTH; j += CELL_WIDTH){
			mCells.push_back(new GridCell(j, i, CELL_WIDTH, CELL_HEIGHT, arrayCoordX, arrayCoordY));
			arrayCoordX++;
		}
		arrayCoordY++;
	}

	for(auto cell : mCells){
		cell->setNeighbors(mCells);
	}

	mBeginNode = mCells.at(15);
	mEndNode = mCells.at(19);
	mBeginNode->setColor(sf::Color::Green);
	mEndNode->setColor(sf::Color::Red);

	mCells.at(10)->setWalkable(false);
	mCells.at(17)->setWalkable(false);
	mCells.at(24)->setWalkable(false);
}

void World::update(float dTime)
{

}

void World::render()
{
	for(auto cell : mCells){
		mRenderTarget->draw(cell->getRect());
	}
}

World::~World()
{
}
