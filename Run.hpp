#ifndef RUN_HPP
#define RUN_HPP

#include "Game.hpp"

const int FRAMERATE = 5;
const int FPS = 1 / FRAMERATE;

int Run(Game& game, sf::RenderWindow& window)
{
	sf::Clock clock;
	sf::Time time = clock.getElapsedTime();

	while(game.isRunning())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			game.handleEvents(event);
		}	
		time = clock.getElapsedTime();

		game.update(time.asMilliseconds());

		window.clear(sf::Color::White);
		game.render();
		window.display();

		if(time.asMilliseconds() < FPS){
			sf::sleep(sf::milliseconds(FPS - time.asMilliseconds()));
		}

		clock.restart();
	}

	return 0;
}

#endif
