//Written by Thomas Butler

#pragma once

#include <SFML/Graphics.hpp> 

class HelpScreen
{
public:
	HelpScreen(float width, float height);
	~HelpScreen();

	void draw(sf::RenderWindow &window);

private:
	sf::Texture m_helpTexture;
	sf::Sprite m_helpSprite;
};
