#pragma once
#include <SFML/Graphics.hpp>

struct Textures {
	sf::Texture UI_Selection;
	sf::Texture UI_SelectionPinched;
	sf::Texture W_Grass;
	sf::Texture W_Grid;
	sf::Texture W_Trees;

	Textures();
	void setup();
};

Textures::Textures() {
	this->setup();
}
void Textures::setup() {
	UI_Selection.loadFromFile("sprites/UI_Selection.png");
	UI_SelectionPinched.loadFromFile("sprites/UI_SelectionPinched.png");
	W_Grass.loadFromFile("sprites/W_Grass.png");
	W_Grid.loadFromFile("sprites/W_Grid.png");
	W_Trees.loadFromFile("sprites/W_Trees.png");
}