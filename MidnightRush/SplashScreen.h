////////////////////////////////////////////////////////////////////////////////////////////////////
//////  Contributors: Thomas Butler, Kevin Boylan
//////  Thomas Butler: Code Framework
//////  Kevin Boylan:  Art
//////
//////  A SPLASH SCREEN that loads up before the MAIN MENU.
//////  Tells the player the name of the game.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SFML/Graphics.hpp> 

class SplashScreen
{
public:
	SplashScreen(float width, float height);
	~SplashScreen();

	void draw(sf::RenderWindow &window);

private:
	sf::Texture splashTexture;
	sf::Sprite splashSprite;
};
