#include "Bullet.h"

Bullet::Bullet()
{
	if (!m_BulletTexture.loadFromFile("Sprites Folder/Bullet3.png"))
	{
		// error...
	}

	m_alive = false;
}

Bullet::~Bullet()
{

}

// Loads the bullet texture for the bullet sprite
void Bullet::Load(Texture&)
{
	m_BulletSprite.setTexture(m_BulletTexture);
}

void Bullet::Update()
{
	// if the bullet is alive
	if (m_alive == true)
	{
		// We set the movement of the bullets 
		// in relation to the assigned direction of the bullets 
		if (bulletDirection == 1)
		{
			m_BulletSprite.move(0, -50);
		}
		else if (bulletDirection == 2)
		{
			m_BulletSprite.move(0, 50);
		}
		else if (bulletDirection == 3)
		{
			m_BulletSprite.move(-50, 0);
		}
		else if (bulletDirection == 4)
		{
			m_BulletSprite.move(50, 0);
		}
	}
}

// method for drawing the bullets
void Bullet::draw(sf::RenderWindow &window)
{
	window.draw(m_BulletSprite);
}

