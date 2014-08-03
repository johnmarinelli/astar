#include "World.hpp"
#include <iostream>
#include <algorithm>

#include <vector>
#include <map>

bool isInList(const GridCell* cell, const std::vector<GridCell*>& list)
{
	return std::find(list.begin(), list.end(), cell) != list.end();
}

/*
* This function requires the beginning cell, the destination cell, and the cell being inspected
* Sets "cell"s hval, fval, and gval
* returns "cell"s gval
*/
int getGValue(GridCell* const start, GridCell* const end, GridCell* cell)
{
	int gval = 10, hval = 0, fval = 0;
	cell->mGValue = 10;

	if(start->isDiagonalNeighbor(cell)){
		gval = 14;
		cell->mGValue = gval;
	}
		
	hval = getManhattanDistance(cell->getArrayCoords().x, cell->getArrayCoords().y, end->getArrayCoords().x, end->getArrayCoords().y) * 10;
	cell->mHValue = hval;

	fval = hval + gval;
	cell->mFValue = fval;

	return gval;
}

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

	//calculate g, h, and f values for each cell
	for(auto cell : openlist){
/*		int gval = 10, hval = 0, fval = 0;
		cell->mGValue = 10;

		if(mBeginNode->isDiagonalNeighbor(cell)){
			gval = 14;
			cell->mGValue = gval;
		}
		
		hval = getManhattanDistance(cell->getArrayCoords().x, cell->getArrayCoords().y, mEndNode->getArrayCoords().x, mEndNode->getArrayCoords().y) * 10;
		cell->mHValue = hval;

		fval = hval + gval;
		cell->mFValue = fval;
*/
		getGValue(mBeginNode, mEndNode, cell);
	}

	GridCell* lowest_fval_cell = openlist.front();
	int placeholder_fval = lowest_fval_cell->mFValue;

	//drop lowest f value cell
	for(auto cell : openlist){
		int fval = cell->mFValue;

		if(fval < placeholder_fval){
			placeholder_fval = fval;
			lowest_fval_cell = cell;
		}
	}

	//remove lowest fval cell from openlist & put in closed list
	openlist.erase(std::remove(openlist.begin(), openlist.end(), lowest_fval_cell));
	closedlist.push_back(lowest_fval_cell);

	//add walkable nodes to open list
	for(auto cell : lowest_fval_cell->getNeighbors()){
		if(cell->getWalkable() && cell != lowest_fval_cell && !isInList(cell, closedlist)){
			//check if the cell is in open list already
			if(isInList(cell, openlist)){
				int new_g_val = cell->mGValue + lowest_fval_cell->mGValue;
				if(new_g_val < lowest_fval_cell->mGValue){
					cell->mParent = lowest_fval_cell;
					getGValue(lowest_fval_cell, mEndNode, cell);
				}
			}
			else{
				openlist.push_back(cell);
				cell->mParent = lowest_fval_cell;
			}
		}
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
