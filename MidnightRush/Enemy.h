//////////////////////////////////////////////////////////////
//////// Contributors: Thomas Butler, Kevin Boylan
////////
//////// Thomas Butler: Sprites (Standard+Death), Attack Animation
//////// Kevin Boylan:  Movement/AI, Health 
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

#include "EnemyAI.h"

#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;
#include <iostream>
using namespace std;

#include "EnemyPaths.h"
#include "Direction.h"


class Enemy
{
public:
	Enemy();
	Enemy(sf::Vector2f position, int path, int levelCount);
	~Enemy();

	//EnemyAI m_enemyAI;
	sf::Vector2f enemyPosition;
	void draw(sf::RenderWindow &window);
	
	void Update();
	void Death();
	void Attack();

	bool alive = true;
	Sprite getSprite() { return m_EnemySprite; };
	Vector2f getPosition() { return m_EnemyPosition; };

	bool getEnemyAlive() { return alive; }
	void setEnemyAlive(bool set) { alive = set; }
	bool enemySwing = false;

	//int direction = 2; //Facing Right
	Direction enemyDirection = Direction::Left;
	int count;
	float timer = 0;
	float test = 0;

	static std::shared_ptr<std::vector<sf::Vector2f>>getEnemyPath(int mapCount, int path);

	std::shared_ptr<std::vector<sf::Vector2f>> m_wayPoints;

	sf::Vector2f update(sf::Vector2f enemyPos);

	float m_EnemyHealth;
	bool enemyLife;

	int shootDeathTimer;

private:
	// Enemy walking around
	sf::Texture m_EnemyTexture;
	IntRect m_EnemySource;
	sf::Sprite m_EnemySprite;
	Vector2f m_EnemyPosition;

	//Sprite for when the enemy is dead
	Texture m_EnemyDeathTexture;
	IntRect m_EnemyDeathSource;
	Sprite m_EnemyDeathSprite;

	//Sprite for when the enemy is attacking 
	Texture m_EnemySwingTexture;
	IntRect m_EnemySwingSource;
	Sprite m_EnemySwingSprite;

	bool right = false;
	bool left = false;
	bool up = false;
	bool down = false;

	int index;
	bool xPath;
	bool yPath;
	float m_speed;



	


	void Load(Texture&); //Loads all external assets
};

