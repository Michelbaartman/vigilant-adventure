#include "HUD.h"

HUD::HUD()
{
	cursorTex.loadFromFile("sprites/UI_Selection.png");
	cursorSprite.setTexture(cursorTex);
	cursorSprite.setPosition(64, 64);

	font.loadFromFile("sprites/arial.ttf");
	text1.setFont(font);
	text1.setPosition(0, 10 * 32);
	text1.setString("empty");
	text1.setCharacterSize(10);
	text1.setFillColor(sf::Color::Black);

	text2.setFont(font);
	text2.setPosition(2 * 32, 10 * 32);
	text2.setString("empty");
	text2.setCharacterSize(10);
	text2.setFillColor(sf::Color::Black);
}


HUD::~HUD()
{
}

void HUD::update() {

}

void HUD::draw(sf::RenderWindow & window){
	window.draw(cursorSprite);
	window.draw(text1);
	window.draw(text2);
}

void HUD::cursorSetPos(sf::Vector2i pos) {
	cursorSprite.setPosition(pos.x, pos.y);
}

sf::Vector2i HUD::cursorGetPos() {
	sf::Vector2i pos(cursorSprite.getPosition().x, cursorSprite.getPosition().y);
	return pos;
}

sf::Sprite HUD::getCursor() {
	return cursorSprite;
}

void HUD::setText1(std::string str) {
	text1.setString(str);
}

void HUD::setText2(std::string str) {
	text2.setString(str);
}