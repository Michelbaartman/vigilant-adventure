#include "Indicator.h"


Indicator::Indicator()
{
}

Indicator::Indicator(int x, int y)
{
	texture.loadFromFile("sprites/W_GridBlue.png");
	sprite.setTexture(texture);
	sprite.setPosition(x * 32, y * 32);
}


Indicator::~Indicator()
{
}

void Indicator::draw(sf::RenderWindow & window) {
	window.draw(sprite);
}
