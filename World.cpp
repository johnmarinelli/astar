#include "World.hpp"
#include <iostream>

World::World(sf::RenderWindow& window) : mRenderTarget(&window)
{
}

void World::init()
{
	for(int i = 0; i < WINDOW_HEIGHT; i += CELL_HEIGHT){
		for(int j = 0; j < WINDOW_WIDTH; j += CELL_WIDTH){
//			sf::Color random_color(3,  4, (i*j) % 5, 1);
			sf::Color random_color(sf::Color::Black);
			mCells.push_back(new GridCell(j, i, CELL_WIDTH, CELL_HEIGHT, random_color));
		}
	}
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
