//Written by Thomas Butler

#pragma once

#include <SFML/Graphics.hpp> 

class LicenceScreen
{
public:
	LicenceScreen(float width, float height);
	~LicenceScreen();

	void draw(sf::RenderWindow &window);

private:
	sf::Texture m_licenceTexture;
	sf::Sprite m_licenceSprite;
};

