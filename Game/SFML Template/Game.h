#pragma once
#include "HUD.h"
#include "Tile.h"
#include <SFML/Graphics.hpp>
#include <iostream>

#define screenX 960
#define screenY 540
#define sprReso 32
#define tempGridX 20
#define tempGridY 10
#define moveWaitTimer tempGridX*tempGridY

class Game
{
private:
	Tile grid[tempGridX][tempGridY][5];
	// [x][y][id]
	// [id], 0 = units, 1 = grid indicator
	sf::Vector2i gridSize = sf::Vector2i(tempGridX-1, tempGridY-1);
	HUD hud;
	sf::RenderWindow & window;
	sf::Vector2i mousePos = sf::Vector2i(0, 0);
	int moveXCount = 0;
	int moveYCount = 0;
	bool mouseMode = false;
	Tile & selected = grid[0][0][0];

public:
	Game(sf::RenderWindow &window);
	void events();
	void update();
	void draw();
	void setupGrid(int width, int height);
	void drawGrid();
	void checkCol(int posX, int posY);
	void clearSel();
};

