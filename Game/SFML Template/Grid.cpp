#include "Grid.h"

Grid::Grid()
{
}

Grid::Grid(int posX, int posY) 
{
	tDefault.loadFromFile("sprites/W_Grid.png");
	tSelected.loadFromFile("sprites/W_GridSelected.png");
	this->setSelected(false);
	int offset = (tDefault.getSize().x - sprReso) / 2;
	sprite.setOrigin(offset, offset);
	sprite.setPosition(posX * sprReso, posY * sprReso);
}


Grid::~Grid()
{
}

void Grid::draw(sf::RenderWindow & window) {
	window.draw(sprite);
}

// switches sprite from grid to selected
void Grid::setSelected(bool state) {
	if (state) {
		sprite.setTexture(tSelected);
		sprite.setColor(sf::Color(255, 255, 255, 255));
	}
	else {
		sprite.setTexture(tDefault);
		sprite.setColor(sf::Color(255, 255, 255, 50));
	}
}