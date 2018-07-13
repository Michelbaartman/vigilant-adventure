#pragma once
#include "HUD.h"
#include "Tile.h"
#include "Indicator.h"
#include "Grid.h"
#include <SFML/Graphics.hpp>
#include "Unit.h"
#include <iostream>

#include "Info.h"

class Game
{
private:
	sf::RenderWindow & window;
	HUD hud;
	sf::Vector2i gridSize;
	sf::View map;

	Tile background[gridLimit][gridLimit];
	Tile bgModifier[gridLimit][gridLimit];
	Grid grid[gridLimit][gridLimit];
	Unit units[gridLimit][gridLimit];
	Indicator indicators[gridLimit][gridLimit];

	sf::Vector2i mousePos = sf::Vector2i(0, 0);
	bool somethingSelected = false;
	sf::Vector2i selected = sf::Vector2i(-1, -1);

public:
	Game(sf::RenderWindow &window);
	void events();
	void update();
	void draw();

	void setupGrid(int gridSizeX, int gridSizeY);
	void drawGrid();

	std::string checkTile(sf::Vector2i pos);
	void select(sf::Vector2i mousePos);
	void deselect();

	void moveUnit(sf::Vector2i target);
	void setIndicators(sf::Vector2i origin, int mov);
	void setIndicators();
};

