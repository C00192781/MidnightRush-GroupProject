//Written by Thomas Butler

#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;
#include <iostream>
using namespace std;

class LevelState
{
public:
	LevelState();
	~LevelState();

	bool levelComplete = false;
	bool getLevelComplete();
	void setLevelComplete(bool complete);
	void draw(sf::RenderWindow &window);
	void Load(Texture&); //Loads all external assets
	void logoMove();
	int count = 0;

	Sprite getlevelGoalSprite() { return m_levelGoalSprite; };
	Sprite m_levelCompleteSprite;


	Sprite m_levelGoalSprite;

	

private:

	//Sprite to move to next level
	Texture m_levelGoalTexture;
	IntRect m_levelGoalSource;
	

	//Sprite to move to next level
	Texture m_levelCompleteTexture;
	IntRect m_levelCompleteSource;
	
};

