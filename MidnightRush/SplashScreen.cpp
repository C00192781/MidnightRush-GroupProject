#include "SplashScreen.h"

#include <iostream>;
using namespace std;

SplashScreen::SplashScreen(float width, float height)
{
	if (!splashTexture.loadFromFile("Sprites Folder/Splash.png"))
	{
		// error...
		cout << "Error Loading texture" << endl;
	}
	splashSprite.setTexture(splashTexture);
	splashSprite.setOrigin(50, 0);
	splashSprite.setScale(1.05f, 1.0f);
}


SplashScreen::~SplashScreen()
{
}

void SplashScreen::draw(sf::RenderWindow &window)
{
	// draws the background of the PAUSE MENU
	window.draw(splashSprite);
}