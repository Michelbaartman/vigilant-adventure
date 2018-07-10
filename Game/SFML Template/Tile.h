#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Tile
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Texture texture2;
	std::string name;
	bool empty = true;
	bool unit = false;
	int x, y;

public:
	Tile();
	Tile(int id, int x, int y);
	~Tile();

	void draw(sf::RenderWindow & window);
	void update();
	void setSelect(bool b);
	bool getState();
	std::string getName();
};

