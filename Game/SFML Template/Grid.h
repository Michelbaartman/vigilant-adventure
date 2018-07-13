#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Info.h"

class Grid
{
private:
	sf::Sprite sprite;
	sf::Texture tDefault;
	sf::Texture tSelected;
	sf::Vector2i pos;
	bool selected = false;

public:
	Grid();
	Grid(int posX, int posY);
	~Grid();

	void draw(sf::RenderWindow & window);
	void setSelected(bool state);
};
