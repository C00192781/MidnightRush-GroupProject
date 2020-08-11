////////////////////////////////////////////////////////////////////////////////////
////// Contributors: Thomas Butler, Kevin Boylan
//////
////// Thomas Butler: Movement, Collision/Death Sprites, Rifle Sprites
////// Help from Kevin Boylan for these
//////
////// Kevin Boylan: Momentum, Shooting/Bullets, Bullet Collision Detection (with enemies)
////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "Bullet.h"
#include "Enemy.h"
#include "Direction.h"
#include "AudioManager.h"
//#include "Wall.h"
//#include "Background.h"

using namespace std;
using namespace sf;


class Player
{
public:
	Player();
	~Player();

	void draw(sf::RenderWindow &window);
	void Load(Texture&, Texture&); //Loads all external assets
	void Update();

	void Move();
	void Death();
	void Saving();

	void Rifle();
	void ResetMomentum();
	void SwingAnimation();

	

	void Shoot();
	void BulletCollisions(std::vector<shared_ptr<Enemy>> &enemyVector);
	
	
	bool alive = true;
	bool saving = false;
	bool rifle = false;
	bool swing = false;


	bool moving;
	// Sprite
	Sprite m_PlayerSprite;

	// returns the player's position
	Vector2f getPosition() { return m_PlayerPosition; };
	Vector2f setPlayer() { return Vector2f(100, 100); };

	// getter method for the standard player sprite (melee)
	Sprite getSprite() { return m_PlayerSprite; };
	// getter methods for the armed player sprite (for shooting)
	Sprite getRifleSprite() { return m_PlayerRifleSprite; };
	// getter methods for the hostage-holding player sprite (for shooting)
	Sprite getSavingSprite() { return m_SavingSprite; };
	

	float momentum; // used to increase player speed
	Direction presentDirection = Direction::Right;
	float timer = 0;

	


	int bulletDirection;

	Bullet bullet;
	// a vector of bullets
	std::vector <Bullet> bullets;


	bool alligned = false;


	float m_left;
	float m_right;
	float m_top;
	float m_bottom;

	float speed; // for how fast the player can move


	// used to give the enemy a specific amount of health
	int m_enemyHealth = 50;


private:
	//Sprite for when the player is walking around
	Texture m_PlayerTexture;
	IntRect m_PlayerSource;
	Vector2f m_PlayerPosition;
	//Sprite m_PlayerSprite;

	//Sprite for when the player is dead
	Texture m_DeathTexture;
	IntRect m_DeathSource;
	Sprite m_DeathSprite;

	//Sprite for when the player is carring the hostage
	Texture m_SavingTexture;
	IntRect m_SavingSource;
	Sprite m_SavingSprite;

	//Sprite for when the player is carring the hostage
	Texture m_PlayerRifleTexture;
	IntRect m_PlayerRifleSource;
	Sprite m_PlayerRifleSprite;

	//Sprite for when the player is carring the hostage
	Texture m_PlayerSwingTexture;
	IntRect m_PlayerSwingSource;
	Sprite m_PlayerSwingSprite;

	AudioManager m_audio;
	int count;
	int bulletTimer; // used to inforce a time between each bullet shot
	

	bool xP;
	bool yPush;

	// for positioning the bullet correctly, relative to the player upon firing
	int offSetX;
	int OffSetY;

	
};






