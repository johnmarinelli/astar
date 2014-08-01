#include "World.hpp"
#include <iostream>
#include <algorithm>

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
		arrayCoordX = 0;
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
	CellVector openlist, closedlist;
	//add starting node to open list
	openlist.push_back(mBeginNode);
	
	//add walkable nodes to open list
	for(auto cell : mBeginNode->getNeighbors()){
		if(cell->getWalkable() && cell != mBeginNode){
			openlist.push_back(cell);
			cell->mParent = mBeginNode;
		}
	}
	
	//remove starting node from open list, add it to closed list
	openlist.erase(std::remove(openlist.begin(), openlist.end(), mBeginNode), openlist.end());
	closedlist.push_back(mBeginNode);

	for(auto cell : openlist){
		int gval = 10, hval = 0, fval = 0;
		cell->mGValue = 10;

		if(mBeginNode->isDiagonalNeighbor(cell)){
			gval = 14;
			cell->mGValue = gval;
		}
		
		hval = getManhattanDistance(cell->getArrayCoords().x, mEndNode->getArrayCoords().x, cell->getArrayCoords().y, mEndNode->getArrayCoords().y) * 10;
		cell->mHValue = hval;

		fval = hval + gval;
		cell->mFValue = fval;
	} 
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
