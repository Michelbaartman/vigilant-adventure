#include "Game.h"

Game::Game(sf::RenderWindow &window) : window(window)
{
	map = sf::View(sf::FloatRect(0, 0, screenX, screenY));
	setupGrid(tempGridX, tempGridY);
	map.setCenter(sf::Vector2f(tempGridX / 2 * sprReso, tempGridY /2 * sprReso));
	window.setView(map);
}

// game controls, window events, input to game
void Game::events() {
	//mouse cursor movement
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	mousePos.x = window.mapPixelToCoords(pixelPos).x;
	mousePos.y = window.mapPixelToCoords(pixelPos).y;
	mousePos.x = (mousePos.x / sprReso);
	mousePos.y = (mousePos.y / sprReso);
	if (mousePos.x > gridSize.x - 1) mousePos.x = gridSize.x - 1;
	if (mousePos.y > gridSize.y - 1) mousePos.y = gridSize.y - 1;
	if (mousePos.x < 0) mousePos.x = 0;
	if (mousePos.y < 0) mousePos.y = 0;


	// keystroke events keyboard
	/* Keyboard ASWD controls the camera right now, not sure what to do with it yet.
		Original intent is to be able to switch between keyboard and mouse mode */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		map.setCenter(map.getCenter() - sf::Vector2f(1, 0));
		window.setView(map);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		map.setCenter(map.getCenter() - sf::Vector2f(-1, 0));
		window.setView(map);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		map.setCenter(map.getCenter() - sf::Vector2f(0, 1));
		window.setView(map);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		map.setCenter(map.getCenter() - sf::Vector2f(0, -1));
		window.setView(map);
	}

	// keystroke events misc
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) window.close();
		if (event.type == sf::Event::MouseButtonReleased) {
			select(mousePos);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
	}

}

// game update, updates the objects within the game post-input
void Game::update() {
	hud.setText1(checkTile(mousePos));
	hud.cursorSetPos(sf::Vector2i(mousePos.x * sprReso, mousePos.y * sprReso)); //snaps cursor to spot
}

// game draw, draws graphics in window
void Game::draw() {
	window.clear(sf::Color(79, 51, 68));

	// draw objects/graphics
	drawGrid();
	hud.draw(window);

	window.display();
}

// Sets up/initializes the grid/playing field
void Game::setupGrid(int gridSizeX, int gridSizeY) {
	// set seed for temp random generation
	/* in the future, random generation = based on predefined tilesets attached to one another */
	int seed = time(NULL);
	srand(seed);

	// set prerequisites for grid creation
	gridSize.x = gridSizeX;
	gridSize.y = gridSizeY;

	// setup bground layer
	for (int x = 0; x < gridSize.x; x++) {
		for (int y = 0; y < gridSize.y; y++) {
			background[x][y] = *new Tile(x, y, "sprites/Tile2.png");
		}
	}

	// setup bgmod layer
	for (int x = 0; x < gridSize.x; x++) {
		for (int y = 0; y < gridSize.y; y++) {
			if (rand() % 2) {
				bgModifier[x][y] = *new Tile(x, y, "sprites/Tile3.png");
			}
		}
	}

	// setup grid layer
	for (int x = 0; x < gridSize.x; x++) {
		for (int y = 0; y < gridSize.y; y++) {
			grid[x][y] = *new Grid(x, y);
		}
	}

	// setup indicators layer
	for (int x = 0; x < gridSize.x; x++) {
		for (int y = 0; y < gridSize.y; y++) {
			indicators[x][y] = *new Indicator(x, y);
			//indicators[x][y].setAliveState(true);
		}
	}

	// sets up test units
	units[3][3] = *new Unit(3, 3, "sprites/U_Brother.png", "Lawrence", 5);
	units[4][4] = *new Unit(4, 4, "sprites/U_Sister.png", "Mia", 3);
}

// draws everything in the game world in layers for proper presentation
void Game::drawGrid() {
	// draws the ground layer of the world
	for (int x = 0; x < gridSize.x; x++) {
		for (int y = 0; y < gridSize.y; y++) {
			background[x][y].draw(window);
		}
	}

	// draws the ground layer modifiers of the world
	for (int x = 0; x < gridSize.x; x++) {
		for (int y = 0; y < gridSize.y; y++) {
			bgModifier[x][y].draw(window);
		}
	}

	// draws the rectangles to show the grid
	for (int x = 0; x < gridSize.x; x++) {
		for (int y = 0; y < gridSize.y; y++) {
			grid[x][y].draw(window);
		}
	}

	// draws indicators
	for (int x = 0; x < gridSize.x; x++) {
		for (int y = 0; y < gridSize.y; y++) {
			indicators[x][y].draw(window);
		}
	}

	// draws units
	for (int x = 0; x < gridSize.x; x++) {
		for (int y = 0; y < gridSize.y; y++) {
			units[x][y].draw(window);
		}
	}
}

// checks the given position for data
std::string Game::checkTile(sf::Vector2i pos) {
	return units[pos.x][pos.y].getName();
}

// deselects all grid tiles
void Game::deselect() {
	for (int x = 0; x < gridSize.x; x++) {
		for (int y = 0; y < gridSize.y; y++) {
			grid[x][y].setSelected(false);
		}
	}
}

//select tile on grid at the given pos
void Game::select(sf::Vector2i pos) {
	deselect();
	if (somethingSelected) {
		moveUnit(pos);
		somethingSelected = false;
		hud.setText2("");
		setIndicators();
	}
	else {
		selected = pos;
		grid[selected.x][selected.y].setSelected(true);
		if (units[selected.x][selected.y].isUnit()) {
			hud.setText2(units[selected.x][selected.y].getName());
			somethingSelected = true;
			setIndicators(selected, units[selected.x][selected.y].getMov());
		}
		else {
			hud.setText2("");
		}
	}
}

// moves unit to given target
void Game::moveUnit(sf::Vector2i target) {
	// checks whether movement is allowed
	int mov = units[selected.x][selected.y].getMov();
	if ((selected.x - target.x) + (selected.y - target.y) <= mov // upper left corner
		&& (selected.x - target.x) + (selected.y - target.y)*-1 <= mov // upper right corner
		&& (selected.x - target.x) + (selected.y - target.y) >= mov * -1 // lower left corner
		&& (selected.x - target.x) + (selected.y - target.y)*-1 >= mov * -1  // lower right corner
		&& selected != target // blocks from placing unit ontop of itself
		&& units[target.x][target.y].isUnit() == false ) // blocks from placing ontop of other units
	{
		// moves unit
		units[mousePos.x][mousePos.y] = units[selected.x][selected.y];
		units[mousePos.x][mousePos.y].move(mousePos.x, mousePos.y);
		units[selected.x][selected.y] = Unit();
	}
}

// sets indicators on, showing movement options
void Game::setIndicators(sf::Vector2i origin, int mov) {
	for (int x = origin.x - mov; x <= origin.x + mov; x++) {
		for (int y = origin.y - mov; y <= origin.y + mov; y++) {
			if ((origin.x - x) + (origin.y - y) <= mov // upper left corner
				&& (origin.x - x) + (origin.y - y)*-1 <= mov // upper right corner
				&& (origin.x - x) + (origin.y - y) >= mov * -1 // lower left corner
				&& (origin.x - x) + (origin.y - y)*-1 >= mov * -1 ) // lower right corner
			{
				indicators[x][y].setAliveState(true);
			}
		}
	}
}

// sets all indicators off
void Game::setIndicators() {
	for (int x = 0; x < gridSize.x; x++) {
		for (int y = 0; y < gridSize.y; y++) {
			indicators[x][y].setAliveState(false);
		}
	}
}
