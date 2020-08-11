////////////////////////////////////////////////////////////////////////////////////
////// Contributors: Kevin Boylan
////// Basic wall object which we create multiple instances of with Background.cpp
////// Also handles collisions between the Player and a wall
////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Player.h"

#include <SFML\Graphics.hpp>
using namespace sf;
#include <iostream>
using namespace std;



class Wall
{
public:
	Wall();
	Wall(sf::Vector2f position, float rotation);
	~Wall();

	void draw(sf::RenderWindow &window);
	void collisionDetection(sf::Vector2f position, Player &player);


	//std::vector<Direction> playerDirections;

	int playerDirections;

	bool rotated;

	Sprite getSprite() { return m_WallSprite; };
	Sprite player;

	Vector2f getPosition() { return m_WallPosition; };

	/*float getWallHeight() { return m_WallHeight; }
	float getWallWidth() { return m_WallWidth;  }*/
	
	
private:
	sf::Sprite m_WallSprite;
	sf::Texture m_WallTexture;

	IntRect m_WallSource;
	Vector2f m_WallPosition;

	float m_left;
	float m_right;
	float m_bottom;
	float m_top;

	float playerSpeed;


	bool leftDisabled;
	bool rightDisabled;
	bool upDisabled;
	bool downDisabled;
	

	void Load(Texture&); //Loads all external assets

	
};

