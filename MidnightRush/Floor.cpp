#include "Floor.h"

Floor::Floor()
{

}

Floor::Floor(sf::Vector2f position, int floorType)
{
	m_FloorPosition = position;
	m_FloorSource = IntRect(0, 0, 140, 140);
	m_FloorSprite.setTextureRect(m_FloorSource);
	m_FloorSprite.setPosition(m_FloorPosition);

	if (floorType == 0)
	{
		if (!m_FloorTexture.loadFromFile("Sprites Folder/Floor.png"))
		{
			// error...
		}
	}

	if (floorType == 1)
	{
		if (!m_FloorTexture.loadFromFile("Sprites Folder/HallFloor.png"))
		{
			// error...
		}
	}

	if (floorType == 2)
	{

		if (!m_FloorTexture.loadFromFile("Sprites Folder/Purple.png"))
		{
			// error...
		}
	}
};



Floor::~Floor()
{

}

void Floor::Load(Texture& _WallTexture)
{
	m_FloorSprite.setTexture(m_FloorTexture);
}

void Floor::draw(RenderWindow& _window)
{
	Load(m_FloorTexture);
	_window.draw(m_FloorSprite);
}