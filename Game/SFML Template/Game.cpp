#include "Game.h"

Game::Game(sf::RenderWindow &window) : window(window)
{
	sf::View map(sf::FloatRect(0, 0, screenX, screenY));
	map.setCenter(sf::Vector2f(tempGridX / 2 * sprReso, tempGridY /2 * sprReso));
	window.setView(map);
	setupGrid(tempGridX, tempGridY);
}

void Game::events() {
	// record player events/triggers

	//window/key events
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) window.close();
		if (event.type == sf::Event::MouseMoved) mouseMode = true;
		if (event.type == sf::Event::KeyPressed) mouseMode = false;
		if (event.type == sf::Event::MouseButtonReleased) {
			select(mousePos);
		}
	}

	// keyboard events for movement
	if (!mouseMode) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (mousePos.x > 0 && moveXCount >= moveWaitTimer) {
				mousePos.x--;
				moveXCount = 0;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (mousePos.x < gridSize.x && moveXCount >= moveWaitTimer) {
				mousePos.x++;
				moveXCount = 0;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (mousePos.y > 0 && moveYCount >= moveWaitTimer) {
				mousePos.y--;
				moveYCount = 0;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (mousePos.y < gridSize.y && moveYCount >= moveWaitTimer) {
				mousePos.y++;
				moveYCount = 0;
			}
		}
	}
	else {
		//mouse cursor temp
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		mousePos.x = window.mapPixelToCoords(pixelPos).x;
		mousePos.y = window.mapPixelToCoords(pixelPos).y;
		mousePos.x = (mousePos.x / sprReso);
		mousePos.y = (mousePos.y / sprReso);
		if (mousePos.x > gridSize.x) mousePos.x = gridSize.x;
		if (mousePos.y > gridSize.y) mousePos.y = gridSize.y;
		if (mousePos.x < 0) mousePos.x = 0;
		if (mousePos.y < 0) mousePos.y = 0;
	}

	// move timer to regulate speed at which keyboard cursor moves
	if (moveXCount < moveWaitTimer) {
		moveXCount++;
	}
	if (moveYCount < moveWaitTimer) {
		moveYCount++;
	}

	// escape key closes game
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		window.close();
	}
}

void Game::update() {
	// update game backend
	checkCol(mousePos.x, mousePos.y);

	hud.cursorSetPos(sf::Vector2i(mousePos.x * sprReso, mousePos.y * sprReso));
}

void Game::draw() {
	window.clear(sf::Color(79, 51, 68));

	// draw objects/graphics
	drawGrid();
	hud.draw(window);
	window.display();
}

void Game::setupGrid(int width, int height) {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			grid[x][y][1] = *new Tile(0, x * sprReso, y * sprReso);
			grid[x][y][2] = *new Tile(-2, x * sprReso, y * sprReso);
			indicator[x][y] = *new Tile(-3, x * sprReso, y * sprReso);
			if (rand() % 2) grid[x][y][3] = *new Tile(-1, x * sprReso, y * sprReso);
		}
	}

	units[3][3] = *new Unit(3, 3, "sprites/U_Brother.png", "Lawrence", 5);
	units[4][4] = *new Unit(4, 4, "sprites/U_Sister.png", "Mia", 3);
}

void Game::drawGrid() {
	for (int x = 0; x < tempGridX; x++) {
		for (int y = 0; y < tempGridY; y++) {
			grid[x][y][2].draw(window); // tile properties
		}
	}

	for (int x = 0; x < tempGridX; x++) {
		for (int y = 0; y < tempGridY; y++) {
			grid[x][y][3].draw(window); // tile properties
		}
	}

	for (int x = 0; x < tempGridX; x++) {
		for (int y = 0; y < tempGridY; y++) {
			grid[x][y][1].draw(window); // grid indicator
		}
	}

	for (int x = 0; x < tempGridX; x++) {
		for (int y = 0; y < tempGridY; y++) {
			indicator[x][y].draw(window); // grid indicator
		}
	}

	for (int x = 0; x < tempGridX; x++) {
		for (int y = 0; y < tempGridY; y++) {
			units[x][y].draw(window); // units
		}
	}
}

void Game::checkCol(int posX, int posY) {
	if (units[posX][posY].isUnit()) {
		hud.setText1("detected\n" + units[posX][posY].getName());
	}
	else {
		hud.setText1("empty");
	}
}

void Game::clearSel() {
	for (int x = 0; x < tempGridX; x++) {
		for (int y = 0; y < tempGridY; y++) {
			grid[x][y][1].setSelect(false); // grid indicator
		}
	}
}

void Game::select(sf::Vector2i mousePos) {
	clearSel();
	// does something if something is selected
	if (somethingSelected) {
		// checks whether your target is an unit, if not, moves current selected to spot
		if (!units[mousePos.x][mousePos.y].isUnit()) {
			moveUnit(mousePos);
		}
		hud.setText2("deselect");
		somethingSelected = false;
		deselectUnit();
	} else {
		selected = mousePos;
		hud.setText2(units[selected.x][selected.y].getName());
		grid[selected.x][selected.y][1].setSelect(true);
		// only selects something if target == unit
		if (units[selected.x][selected.y].isUnit()) {
			somethingSelected = true;
			selectUnit();
		}
	}
}

void Game::moveUnit(sf::Vector2i mousePos) {
	// grabs basic variables needed for calculation
	int unitX = units[selected.x][selected.y].getX();
	int unitY = units[selected.x][selected.y].getY();
	int mov = units[selected.x][selected.y].getMov();
	int targetX = mousePos.x;
	int targetY = mousePos.y;

	// checks whether movement is allowed
	if ((unitX - targetX) + (unitY - targetY) <= mov // upper left corner
		&& (unitX - targetX) + (unitY - targetY)*-1 <= mov // upper right corner
		&& (unitX - targetX) + (unitY - targetY) >= mov * -1 // lower left corner
		&& (unitX - targetX) + (unitY - targetY)*-1 >= mov * -1 ) { // lower right corner

		// moves unit
		units[mousePos.x][mousePos.y] = units[selected.x][selected.y];
		units[mousePos.x][mousePos.y].move(mousePos.x, mousePos.y);
		units[selected.x][selected.y] = Unit();
	}
}

void Game::selectUnit() {
	int mov = units[selected.x][selected.y].getMov(); // 5
	sf::Vector2i origin = selected; // 4, 4

	// sets indicators on, showing movement options
	for (int x = 0; x <= mov; x++) {
		setIndicatorRow(origin.x - mov + x, origin.x, origin.y + x);
		setIndicatorRow(origin.x - mov + x, origin.x, origin.y - x);
		setIndicatorRow(origin.x, origin.x + x, origin.y + mov - x);
		setIndicatorRow(origin.x, origin.x + x, origin.y - mov + x);
	}
}

void Game::setIndicatorRow(int begin, int end, int y) {
	// checks for out-of-bounds grids and limits it
	if (end >= tempGridX) { end = tempGridX - 1; }
	if (end < 0) { end = 0; }
	if (y < 0) { y = 0; }
	if (y >= tempGridY) { y = tempGridY - 1; }

	/*	turns certain indicators on. may have to swap transparency changes to just having a state
		so the game doesn't draw them */
	for (int x = begin; x <= end; x++) {
		indicator[x][y].setTrans(100);
	}
}

void Game::deselectUnit() {
	for (int x = 0; x < tempGridX; x++) {
		for (int y = 0; y < tempGridY; y++) {
			indicator[x][y].setTrans(0); // grid indicator
		}
	}
}