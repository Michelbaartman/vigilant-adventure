#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Info.h"

class Unit
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	int x, y;
	bool exists = false;
	bool initialized = false;
	bool moved = false;

	sf::Vector2i pos;
	std::string name;
	int mov;

public:
	Unit();
	~Unit();
	Unit(int x, int y, std::string path);
	Unit(int x, int y,
		std::string path,
		std::string sName,
		int sMov);

	void draw(sf::RenderWindow & window);
	void move(int x, int y);
	std::string getName();

	int getX() { return x; }
	int getY() { return y; }
	int getMov() { return mov; }
	bool isUnit() { return exists; }
};

