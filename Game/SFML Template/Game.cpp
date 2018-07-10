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
				std::cout << mousePos.x << "|" << mousePos.y << "\n";
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (mousePos.x < gridSize.x && moveXCount >= moveWaitTimer) {
				mousePos.x++;
				moveXCount = 0;
				std::cout << mousePos.x << "|" << mousePos.y << "\n";
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (mousePos.y > 0 && moveYCount >= moveWaitTimer) {
				mousePos.y--;
				moveYCount = 0;
				std::cout << mousePos.x << "|" << mousePos.y << "\n";
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (mousePos.y < gridSize.y && moveYCount >= moveWaitTimer) {
				mousePos.y++;
				moveYCount = 0;
				std::cout << mousePos.x << "|" << mousePos.y << "\n";
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
			if (rand() % 2) grid[x][y][3] = *new Tile(-1, x * sprReso, y * sprReso);
		}
	}

	units[3][3] = *new Unit(3, 3, "sprites/U_Brother.png", 5);
	units[4][4] = *new Unit(4, 4, "sprites/U_Sister.png", 3);
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
			units[x][y].draw(window); // units
		}
	}
}

void Game::checkCol(int posX, int posY) {
	if (grid[posX][posY][0].getState() == false) {
		hud.setText1("detected\n" + grid[posX][posY][0].getName());
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
	if (somethingSelected) {
		if (!units[mousePos.x][mousePos.y].isUnit()) {
			units[mousePos.x][mousePos.y] = units[selected.x][selected.y];
			units[mousePos.x][mousePos.y].move(mousePos.x, mousePos.y);
			units[selected.x][selected.y] = Unit();
		}
		hud.setText2("deselect");
		somethingSelected = false;
	} else {
		selected = mousePos;
		std::cout << mousePos.x << "|" << mousePos.y << "\n";
		hud.setText2(units[selected.x][selected.y].getName());
		grid[selected.x][selected.y][1].setSelect(true);
		if (units[selected.x][selected.y].isUnit()) {
			somethingSelected = true;
		}
	}
	std::cout << units[selected.x][selected.y].getName()
		<< "[" << units[selected.x][selected.y].getX() 
		<< "," << units[selected.x][selected.y].getY() << "]\n";
}

void Game::move(Unit u, int x, int y) {
	u.move(x, y);
	//grid[oldPos.x][oldPos.y][0] = *new Tile();
	//grid[x][y][0].move(x, y);
	hud.setText2("deselect");
	somethingSelected = false;
}