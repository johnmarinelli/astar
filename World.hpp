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
	
public:
	World(sf::RenderWindow& window);
	void init();

	void update(float dTime);
	void render();
	
	~World();
};

#endif
