//Written by Thomas Butler
#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;
#include <iostream>
using namespace std;


class Weapon
{
public:
	Weapon();
	~Weapon();

	void draw(sf::RenderWindow &window);
	void Load(Texture&); //Loads all external assets
	bool rifleAlive = true;
	bool batAlive = true;
	sf::Sprite m_RifleSprite;
	sf::Sprite m_BatSprite;

	Sprite getRifleSprite() { return m_RifleSprite; };
	Vector2f getPosition() { return m_RiflePosition; };

	Sprite getBatSprite() { return m_BatSprite; };

private:
	//Assault Rifle
	sf::Texture m_RifleTexture;
	IntRect m_RifleSource;
	
	Vector2f m_RiflePosition;

	//Baseball bat
	sf::Texture m_BatTexture;
	IntRect m_BatSource;
	Vector2f m_BatPosition;


};

