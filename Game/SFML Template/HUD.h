#pragma once
#include <SFML/Graphics.hpp>
class HUD
{
private:
	sf::Sprite cursorSprite;
	sf::Texture cursorTex;
	sf::Text text1;
	sf::Text text2;
	sf::Font font;

public:
	HUD();
	~HUD();

	void update();
	void cursorSetPos(sf::Vector2i pos);
	sf::Vector2i cursorGetPos();
	sf::Sprite getCursor();
	void draw(sf::RenderWindow & window);
	void setText1(std::string str);
	void setText2(std::string str);
};

