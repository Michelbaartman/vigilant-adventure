#pragma once
#include "HUD.h"
#include "Tile.h"
#include <SFML/Graphics.hpp>
#include "Unit.h"
#include <iostream>

#define screenX 960
#define screenY 540
#define sprReso 32
#define tempGridX 20
#define tempGridY 10
#define moveWaitTimer 25

class Game
{
private:
	Tile grid[tempGridX][tempGridY][5];
	Unit units[tempGridX][tempGridY];

	sf::Vector2i gridSize = sf::Vector2i(tempGridX-1, tempGridY-1);
	HUD hud;
	sf::RenderWindow & window;
	sf::Vector2i mousePos = sf::Vector2i(0, 0);
	int moveXCount = 0;
	int moveYCount = 0;
	bool mouseMode = false;
	bool somethingSelected = false;
	sf::Vector2i selected = sf::Vector2i(-1, -1);

public:
	Game(sf::RenderWindow &window);
	void events();
	void update();
	void draw();
	void setupGrid(int width, int height);
	void drawGrid();
	void checkCol(int posX, int posY);
	void select(sf::Vector2i mousePos);
	void clearSel();
	void move(Unit t, int x, int y);
};

