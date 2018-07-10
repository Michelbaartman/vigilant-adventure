#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(int id, int x, int y) : x(x), y(y) {
	if (id == 1) {
		unit = true; empty = false;
		texture.loadFromFile("sprites/U_Brother.png");
		sprite.setTexture(texture);
		sprite.setPosition(x, y);
		name = "BrotherUnit";
	}

	if (id == 2) {
		unit = true; empty = false;
		texture.loadFromFile("sprites/U_Sister.png");
		sprite.setTexture(texture);
		sprite.setPosition(x, y);
		name = "SisterUnit";
	}

	if (id == 0) {
		texture.loadFromFile("sprites/W_Grid.png");
		texture2.loadFromFile("sprites/W_GridSel.png");
		sprite.setTexture(texture);
		sprite.setColor(sf::Color(255, 255, 255, 10));
		sprite.setPosition(x, y);
	}
	if (id == -1) {
		texture.loadFromFile("sprites/Tile3.png");
		sprite.setTexture(texture);
		sprite.setOrigin(2, 2);
		sprite.setPosition(x, y);
	}
	if (id == -2) {
		texture.loadFromFile("sprites/Tile2.png");
		sprite.setTexture(texture);
		sprite.setOrigin(2, 2);
		sprite.setPosition(x, y);
	}
}


Tile::~Tile()
{
}

void Tile::draw(sf::RenderWindow & window) {
	window.draw(sprite);
}

bool Tile::getState() {
	return empty;
}

std::string Tile::getName() {
	return name;
}

void Tile::setSelect(bool b) {
	if (b) {
		sprite.setTexture(texture2); 
		sprite.setColor(sf::Color(255, 255, 255, 255));
	}
	else { 
		sprite.setTexture(texture); 
		sprite.setColor(sf::Color(255, 255, 255, 10)); }
}

void Tile::move(int posX, int posY) {
	sprite.setPosition(posX*32, posY*32);
	x = posX;
	y = posY;

}

int Tile::getX() { return x; }
int Tile::getY() { return y; }