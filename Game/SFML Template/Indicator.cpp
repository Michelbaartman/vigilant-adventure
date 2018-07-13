#include "Indicator.h"


Indicator::Indicator()
{
}

Indicator::Indicator(int x, int y)
{
	texture.loadFromFile("sprites/W_GridBlue.png");
	sprite.setTexture(texture);
	sprite.setPosition(x * 32, y * 32);
	sprite.setColor(sf::Color(255, 255, 255, 200));
}


Indicator::~Indicator()
{
}

void Indicator::draw(sf::RenderWindow & window) {
	if(alive) window.draw(sprite);
}

void Indicator::setAliveState(bool state) {
	alive = state;
}