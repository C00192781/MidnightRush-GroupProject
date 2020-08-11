//Written by Thomas Butler

#pragma once

#include <SFML/Graphics.hpp> 

class LoadScreen
{
public:
	LoadScreen(float width, float height);
	~LoadScreen();

	void draw(sf::RenderWindow &window);
	void ChangePercent();
	float m_size = 0.125f;

private:
	sf::Sprite m_BackgroundSprite;
	sf::Sprite m_BarSprite;
	sf::Sprite m_LoadPage;
	sf::Texture m_BackgroundTexture;
	sf::Texture m_BarTexture;
	sf::Texture m_LoadPageTexture;
};