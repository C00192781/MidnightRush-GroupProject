#include "Weapon.h"

Weapon::Weapon()
{
	m_RifleSource = IntRect(0, 0, 150, 45);
	m_RifleSprite.setTextureRect(m_RifleSource);
	m_RifleSprite.setPosition(2400, 2000);

	if (!m_RifleTexture.loadFromFile("Sprites Folder/Assault_Sprite.png"))
	{
		// error...
	}


	m_BatSource = IntRect(0, 0, 41, 105);
	m_BatSprite.setTextureRect(m_BatSource);
	m_BatSprite.setPosition(200, 700);

	if (!m_BatTexture.loadFromFile("Sprites Folder/Bat_Sprite.png"))
	{
		// error...
	}
}


Weapon::~Weapon()
{
}

void Weapon::Load(Texture& _hostageTexture)
{
	if (rifleAlive == true)
	{
		m_RifleSprite.setTexture(m_RifleTexture);
	}
	if (batAlive == true)
	{
		m_BatSprite.setTexture(m_BatTexture);
	}
}

void Weapon::draw(RenderWindow& _window)
{
	if (rifleAlive == true)
	{
		_window.draw(m_RifleSprite);
	}
	if (batAlive == true)
	{
		_window.draw(m_BatSprite);
	}

}

