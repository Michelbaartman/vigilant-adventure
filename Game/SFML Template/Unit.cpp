#include "Unit.h"


Unit::Unit()
{
	name = "empty";
	x = -1;
	y = -1;
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
	initialized = true;
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
	x = posX;
	y = posY;
	sprite.setPosition(x * sprReso, (y * sprReso) - 10); // 10 = offset for sprite drawing, so that it's a little bit above square
}