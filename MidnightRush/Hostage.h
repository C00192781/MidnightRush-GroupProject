////////////////////////////////////////////////////////////////////////////////////
////// Contributors: Thomas Bulter, Kevin Boylan
//////
////// Thomas Butler: Hostage Object
////// Kevin Boylan:  Drop Hostage

#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;
#include <iostream>
using namespace std;

#include "Player.h"

class Hostage
{
public:
	Hostage(sf::Vector2f position);
	~Hostage();

	void draw(sf::RenderWindow &window);
	void Load(Texture&); //Loads all external assets
	
	void Update(Player &player);
	void DropHostage(Player &player);

	bool alive = true;
	Sprite getSprite() { return m_HostageSprite; };
	Vector2f getPosition() { return m_HostagePosition; };
	sf::Sprite m_HostageSprite;

private:
	sf::Texture m_HostageTexture;
	IntRect m_HostageSource;
	//sf::Sprite m_HostageSprite;
	Vector2f m_HostagePosition;
};

