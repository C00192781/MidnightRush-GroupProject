////////////////////////////////////////////////////////////////////////////////////////////////////
//////  Contributors: Thomas Butler, Kevin Boylan
//////  Thomas Butler: Base Code
//////  Kevin Boylan:  Art + Resizing
//////


#pragma once

#include <SFML/Graphics.hpp> 

class GameOverScreen
{
public:
	GameOverScreen(float width, float height);
	~GameOverScreen();

	void draw(sf::RenderWindow &window);

private:
	sf::Texture m_gameOverTexture;
	sf::Sprite m_gameOverSprite;
};
