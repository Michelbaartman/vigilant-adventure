#include "Unit.h"



Unit::Unit()
{
}

Unit::Unit(int x, int y, std::string path)
{
	exists = true;
	texture.loadFromFile(path);
	sprite.setTexture(texture);
	name = "generic";
	this->move(x, y);
	mov = 5;
}

Unit::Unit(int x, int y, std::string path, std::string sName, int sMov)
{
	exists = true;
	texture.loadFromFile(path);
	sprite.setTexture(texture);
	name = sName;
	this->move(x, y);
	mov = sMov;
}

Unit::~Unit()
{
}


void Unit::draw(sf::RenderWindow & window) {
	window.draw(sprite);
}

std::string Unit::getName() {
	return name;
}

void Unit::move(int posX, int posY) {
	sprite.setPosition(posX * 32, (posY * 32) - 10);
	x = posX;
	y = posY;
}