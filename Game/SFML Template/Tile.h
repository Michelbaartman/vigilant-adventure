#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Info.h"

class Tile
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2i pos;
	sf::RectangleShape hitbox;

public:
	Tile();
	Tile(int posX, int posY, std::string texturePath);
	~Tile();

	void draw(sf::RenderWindow & window);
};

