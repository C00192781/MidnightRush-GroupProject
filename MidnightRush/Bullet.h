////////////////////////////////////////////////////////////////////////////////////
////// Contributors: Kevin Boylan
//////
////// Used to create individual instances of Bullets (in the Player Class)
///////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>

using namespace sf;

class Bullet
{
public:
	Bullet();
	~Bullet();

	void draw(sf::RenderWindow &window);
	void Load(Texture&); //Loads all external assets
	void Update();

	// getter methods
	Sprite getBulletSprite() { return m_BulletSprite; };
	Texture getBulletTexture() { return m_BulletTexture; };
	Vector2f getBulletPosition() { return m_BulletPosition; };
	bool getBulletAlive() { return m_alive; }
	int getDirection() { return bulletDirection; }

	// setter methods
	void setBulletPosition(Vector2f set) { m_BulletSprite.setPosition(set); }
	void setBulletAlive(bool set) { m_alive = set; }
	void setBulletDirection(int set) { bulletDirection = set; }
	void setBulletRotation(int set)
	{
		bulletRotation = set;
		m_BulletSprite.rotate(bulletRotation);
	}

private:
	// may implement the following 2 variables later
	Vector2f m_velocity;
	Vector2f m_BulletVelocity;

	Vector2f m_BulletPosition;

	sf::Sprite m_BulletSprite;
	sf::Texture m_BulletTexture;

	IntRect m_BulletSource;

	bool m_alive;
	int bulletDirection = 1;
	float bulletRotation;
};