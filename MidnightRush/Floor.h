////////////////////////////////////////////////////////////////////////////////////
////// Contributors: Kevin Boylan
////////////////////////////////////////////////////////////////////////////////////
#pragma once


#include <SFML\Graphics.hpp>
using namespace sf;
#include <iostream>
using namespace std;

class Floor
{
public:
	Floor();
	Floor(sf::Vector2f position, int floorType);
	~Floor();

	void draw(sf::RenderWindow &window);
	void Load(Texture&); //Loads all external assets


	Sprite getSprite() { return m_FloorSprite; };
	Vector2f getPosition() { return m_FloorPosition; };

	float getFloorHeight() { return m_FloorHeight; }
	float getFloorWidth() { return m_FloorWidth; }


private:
	sf::Sprite m_FloorSprite;
	sf::Texture m_FloorTexture;

	IntRect m_FloorSource;
	Vector2f m_FloorPosition;

	float m_FloorHeight;
	float m_FloorWidth;
};
