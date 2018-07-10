#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Unit
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	std::string name;
	int x, y;
	bool exists = false;
	int mov;

public:
	Unit();
	~Unit();
	Unit(int x, int y, std::string path);
	Unit(int x, int y,
		std::string path,
		int sMov);

	void draw(sf::RenderWindow & window);
	void move(int x, int y);
	std::string getName();

	int getX() { return x; }
	int getY() { return y; }
	bool isUnit() { return exists; }
};

