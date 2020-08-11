//Written by Thomas Butler

#pragma once

#include <SFML/Graphics.hpp> 

class WinnerScreen
{
public:
	WinnerScreen(float width, float height);
	~WinnerScreen();

	void draw(sf::RenderWindow &window);

private:
	sf::Texture m_winnerTexture;
	sf::Sprite m_winnerSprite;
};

