#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(int posX, int posY, std::string texturePath) {
	if (debug) {
		hitbox.setSize(sf::Vector2f(sprReso - 2, sprReso - 2));
		hitbox.setOrigin(-1, -1);
		hitbox.setPosition(posX * sprReso, posY * sprReso);
		hitbox.setOutlineColor(sf::Color::Red);
		hitbox.setOutlineThickness(1);
		hitbox.setFillColor(sf::Color::Transparent);
	}

	texture.loadFromFile(texturePath);
	sprite.setTexture(texture);
	int offset = (texture.getSize().x - sprReso) / 2;
	sprite.setOrigin(offset, offset);
	sprite.setPosition(posX * sprReso, posY * sprReso);
}


Tile::~Tile()
{
}

void Tile::draw(sf::RenderWindow & window) {
	window.draw(sprite);
	if (debug) window.draw(hitbox);
}