////////////////////////////////////////////////////////////////////////////////////
////// Contributors: Kevin Boylan
//////
////////////////////////////////////////////////////////////////////////////////////

#pragma once



#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Player.h"

static class Score
{
public:

	Score();
	Score(float base, float height);
	~Score();
	void AddScore(int newScoreValue);
	void UpdateScore();
	void MulitiplierReset();
	void Reset(int reset);

	void Update(int playerX, int playerY);

	void draw(sf::RenderWindow &window);

	int score;
	int increase = 0;
	int multiplier;
	int bonus = 0;

	sf::Text scoreText;
	sf::Text mulitplierText;
	Player player;


private:

	std::clock_t start;
	double duration;
	
	
	sf::Font myFont; 

	sf::Clock clock;

	sf::Time elapsedTime;


	
	bool clockStart;

	bool clockRestart;

	sf::Font font;
	sf::String scoreString;
};