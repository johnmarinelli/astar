#include "Game.hpp"

Game::Game(sf::RenderWindow& window) : mWorld(window)
{
}

void Game::init()
{
	mIsRunning = true;
	mWorld.init();
}

void Game::update(float dTime)
{
	mWorld.update(dTime);
}

void Game::render()
{
	mWorld.render();
}

bool Game::isRunning() const
{
	return mIsRunning;
}

Game::~Game()
{
}
