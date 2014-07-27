#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include "World.hpp"

class Game
{
private:
	World mWorld;
	bool mIsRunning;

public:
	Game(sf::RenderWindow& window);

	void init();

	void update(float dTime);
	void render();

	bool isRunning() const;

	~Game();
};

#endif
