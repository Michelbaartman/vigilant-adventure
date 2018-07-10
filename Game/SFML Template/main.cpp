#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

int main() {
	std::cout << "hello world, creating window\n";
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "game");
	
	Game game(window);
	//window.setMouseCursorVisible(false);

	while (window.isOpen())
	{
		game.events();
		game.update();
		game.draw();
	}
}