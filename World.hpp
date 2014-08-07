#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Utilities.hpp"
#include "GridCell.hpp"

class World
{
private:
	sf::RenderWindow* mRenderTarget;

	typedef std::vector<GridCell*> CellVector;
	CellVector mCells;

	GridCell* mBeginNode;
	GridCell* mEndNode;	

	void doAStar();
	GridCell* getGridCellAtPosition(int x, int y);

public:
	World(sf::RenderWindow& window);
	void init();

	void handleEvents(sf::Event event);
	void update(float dTime);
	void render();
	
	~World();
};

#endif
