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
* Requires the beginning cell, the destination cell, and the cell being inspected
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

/*
* Requires open list
* returns cell with lowest fval
*/
GridCell* getLowestFValCell(const std::vector<GridCell*>& list)
{
	//placeholders
	GridCell* lowest_fval_cell = list.front();
	int placeholder_fval = lowest_fval_cell->mFValue;

	//go in reverse order 
	for(auto itr = list.rbegin(); itr != list.rend(); ++itr){
		auto cell = *itr;
		int fval = cell->mFValue;

		if(fval < placeholder_fval){
			placeholder_fval = fval;
			lowest_fval_cell = cell;
		}
	}

	return lowest_fval_cell;
}

/*
* Requires cell to move, the beginning list, and destination list
*/
void switchLists(GridCell* cell, std::vector<GridCell*>& original_list, std::vector<GridCell*>& destination_list)
{
	//remove starting node from original list, add it to destination
	original_list.erase(std::remove(original_list.begin(), original_list.end(), cell), original_list.end());
	destination_list.push_back(cell);
}

int populateOpenList(GridCell* parent, GridCell* destination, std::vector<GridCell*>& open_list, std::vector<GridCell*>& closed_list)
{
	for(auto cell : parent->getNeighbors()){
		if(cell->getWalkable() && cell != parent && !isInList(cell, closed_list)){
			//check if cell is in open list already
			if(isInList(cell, open_list)){
				//wut?????? if x + y > x??
				int new_gval = cell->mGValue + parent->mGValue;
				if(new_gval < parent->mGValue){
					cell->mParent = parent;
					getGValue(parent, destination, cell);
				}
			}
			else{
				open_list.push_back(cell);
				getGValue(parent, destination, cell);
				cell->mParent = parent;
			}
		}
	}
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
	populateOpenList(mBeginNode, mEndNode, openlist, closedlist);
	
	//remove starting node from open list, add it to closed list
	switchLists(mBeginNode, openlist, closedlist);

	//calculate g, h, and f values for each cell
	for(auto cell : openlist){
		getGValue(mBeginNode, mEndNode, cell);
	}

	//get lowest fval cell
	GridCell* lowest_fval_cell = getLowestFValCell(openlist);

	//remove lowest fval cell from openlist & put in closed list
	switchLists(lowest_fval_cell, openlist, closedlist);

	//add walkable nodes next to lowest_fval_cell to open list
	populateOpenList(lowest_fval_cell, mEndNode, openlist, closedlist);

	//get lowest fval cell
	lowest_fval_cell = getLowestFValCell(openlist);

	switchLists(lowest_fval_cell, openlist, closedlist);

	populateOpenList(lowest_fval_cell, mEndNode, openlist, closedlist);
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
