#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
class ButtonSelect
{
	bool selected = false;
	sf::Sprite spriteImage;
	std::string name;
	sf::RectangleShape button;
	sf::Text textName; 
	sf::Texture texture;
	
public:
	ButtonSelect();
	void drawTo(sf::RenderWindow& window);
	void setPosition(sf::Vector2f pos);
	void setTexture(sf::Texture texturee);
	void setName(std::string namee);
	void setButtonColor(sf::Color color);
	void setFont(sf::Font& font);
	bool isMouseOver(float mousePosX, float mousePosY);

};

