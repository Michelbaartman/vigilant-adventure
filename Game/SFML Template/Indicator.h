#pragma once
#include <SFML\Graphics.hpp>
class Indicator
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	bool alive = false;

public:
	Indicator();
	Indicator(int x, int y);
	~Indicator();

	void draw(sf::RenderWindow & window);
	void setAliveState(bool state);
};

