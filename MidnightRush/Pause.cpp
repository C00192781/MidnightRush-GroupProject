// Written by Kevin Boylan

#include "Pause.h"

Pause::Pause(float base, float height)
{
	// loads in a font
	if (!myFont.loadFromFile("fonts/Shoguns Clan.ttf"))
	{
		// error
	}


	// used to add in background image for menu
	if (!myTexture.loadFromFile("Sprites Folder/PauseBackground.png"))
	{
		// error
	}

	mySprite.setTexture(myTexture);
	mySprite.setScale(1.9f, 1.9f);
	//mySprite.setPosition(pauseX, pauseY);

	pauseIndex = 0;

	pause[0].setFont(myFont);
	pause[0].setScale(2.0f, 2.0f);
	pause[0].setPosition(sf::Vector2f(base / 2.25, height / 5));
	pause[0].setColor(sf::Color::Black);
	pause[0].setString("RESUME");

	pause[1].setFont(myFont);
	pause[1].setScale(2.0f, 2.0f);
	pause[1].setPosition(sf::Vector2f(base / 2.25, height / 2.5));
	pause[1].setColor(sf::Color::White);
	pause[1].setString("RESTART");

	pause[2].setFont(myFont);
	pause[2].setScale(2.0f, 2.0f);
	pause[2].setPosition(sf::Vector2f(base / 2.25, height / 1.66));
	pause[2].setColor(sf::Color::White);
	pause[2].setString("OPTIONS");

	pause[3].setFont(myFont);
	pause[3].setScale(2.0f, 2.0f);
	pause[3].setPosition(sf::Vector2f(base / 2.25, height / 1.25));
	pause[3].setColor(sf::Color::White);
	pause[3].setString("QUIT");



}

Pause::~Pause()
{

}

// Used to iterate upwards through the PAUSE MENU. 
// Note: if you go up to the top of the menu, and then press the Up button, 
// the index will change to the button at the bottom of the PAUSE MENU.
void Pause::Up()
{
	// If you go up through the index past the top (below 0), the highlighted button will be the last one in the list 
	if (pauseIndex == 0)
	{
		pause[pauseIndex].setColor(sf::Color::White);
		pauseIndex = 3;
		pause[pauseIndex].setColor(sf::Color::Black);
	}

	else if (pauseIndex == 1)
	{
		pause[pauseIndex].setColor(sf::Color::White);
		pauseIndex = 0;
		pause[pauseIndex].setColor(sf::Color::Black);
	}

	else if (pauseIndex == 2)
	{
		pause[pauseIndex].setColor(sf::Color::White);
		pauseIndex = 1;
		pause[pauseIndex].setColor(sf::Color::Black);
	}

	else if (pauseIndex == 3)
	{
		pause[pauseIndex].setColor(sf::Color::White);
		pauseIndex = 2;
		pause[pauseIndex].setColor(sf::Color::Black);
	}
}

// Used to iterate downwards through the PAUSE MENU. 
// Note: if you go down to the bottom of the menu, and then press the down button, 
// the index will change to the button at the top of the PAUSE MENU.
void Pause::Down()
{
	// If you go down through the index past the bottom (exceeding 2), the highlighted button will be the first one in the list 
	if (pauseIndex == 0)
	{
		pause[pauseIndex].setColor(sf::Color::White);
		pauseIndex = 1;
		pause[pauseIndex].setColor(sf::Color::Black);
	}

	else if (pauseIndex == 1)
	{
		pause[pauseIndex].setColor(sf::Color::White);
		pauseIndex = 2;
		pause[pauseIndex].setColor(sf::Color::Black);
	}

	else if (pauseIndex == 2)
	{
		pause[pauseIndex].setColor(sf::Color::White);
		pauseIndex = 3;
		pause[pauseIndex].setColor(sf::Color::Black);
	}

	else if (pauseIndex == 3)
	{
		pause[pauseIndex].setColor(sf::Color::White);
		pauseIndex = 0;
		pause[pauseIndex].setColor(sf::Color::Black);
	}
}


// This is used to reset the index to 0 upon returning to the Options Menu
void Pause::Reset()
{
	pauseIndex = 0;
	pause[0].setColor(sf::Color::Black);
	pause[1].setColor(sf::Color::White);
	pause[2].setColor(sf::Color::White);
	pause[3].setColor(sf::Color::White);
}


void Pause::draw(sf::RenderWindow &window)
{
	// draws the background of the PAUSE MENU
	window.draw(mySprite);
	// draws the buttons
	for (int index = 0; index < MAX_NUMBER_OF_PAUSE_BUTTONS; index++)
	{
		window.draw(pause[index]);
	}
}