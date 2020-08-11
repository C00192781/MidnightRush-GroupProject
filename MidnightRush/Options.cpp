// Written by Kevin Boylan

#include "Options.h"

Options::Options(float base, float height)
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




	optionsIndex = 0;

	options[0].setFont(myFont);
	options[0].setScale(2.0f, 2.0f);
	options[0].setPosition(sf::Vector2f(base / 2.25, height / 3));
	options[0].setColor(sf::Color::Black);
	options[0].setString("SOUND");

	options[1].setFont(myFont);
	options[1].setScale(2.0f, 2.0f);
	options[1].setPosition(sf::Vector2f(base / 2.25, height / 2));
	options[1].setColor(sf::Color::White);
	options[1].setString("HELP");

	options[2].setFont(myFont);
	options[2].setScale(2.0f, 2.0f);
	options[2].setPosition(sf::Vector2f(base / 2.25, height / 1.5));
	options[2].setColor(sf::Color::White);
	options[2].setString("RETURN");


}

Options::~Options()
{

}

// Used to iterate upwards through the OPTIONS MENU. 
// Note: if you go up to the top of the menu, and then press the Up button, 
// the index will change to the button at the bottom of the OPTIONS MENU.
void Options::Up()
{
	// If you go up through the index past the top (below 0), the highlighted button will be the last one in the list 
	if (optionsIndex == 0)
	{
		options[optionsIndex].setColor(sf::Color::White);
		optionsIndex = 2;
		options[optionsIndex].setColor(sf::Color::Black);
	}

	else if (optionsIndex == 1)
	{
		options[optionsIndex].setColor(sf::Color::White);
		optionsIndex = 0;
		options[optionsIndex].setColor(sf::Color::Black);
	}

	else if (optionsIndex == 2)
	{
		options[optionsIndex].setColor(sf::Color::White);
		optionsIndex = 1;
		options[optionsIndex].setColor(sf::Color::Black);
	}


}

// Used to iterate downwards through the OPTIONS MENU. 
// Note: if you go up to the bottom of the menu, and then press the Down button, 
// the index will change to the button at the top of the OPTIONS MENU.
void Options::Down()
{
	// If you go down through the index past the bottom (exceeding 2), the highlighted button will be the first one in the list 
	if (optionsIndex == 0)
	{
		options[optionsIndex].setColor(sf::Color::White);
		optionsIndex = 1;
		options[optionsIndex].setColor(sf::Color::Black);
	}

	else if (optionsIndex == 1)
	{
		options[optionsIndex].setColor(sf::Color::White);
		optionsIndex = 2;
		options[optionsIndex].setColor(sf::Color::Black);
	}

	else if (optionsIndex == 2)
	{
		options[optionsIndex].setColor(sf::Color::White);
		optionsIndex = 0;
		options[optionsIndex].setColor(sf::Color::Black);
	}

}

// This is used to reset the index to 0 upon returning to the Options Menu
void Options::Reset()
{
	optionsIndex = 0;
	options[0].setColor(sf::Color::Black);
	options[1].setColor(sf::Color::White);
	options[2].setColor(sf::Color::White);
}

// method for drawing the OPTIONS MENU
void Options::draw(sf::RenderWindow &window)
{
	// draws the background of the MAIN MENU
	window.draw(mySprite);
	// draws the buttons
	for (int index = 0; index < MAX_NUMBER_OF_OPTIONS_BUTTONS; index++)
	{
		window.draw(options[index]);
	}
}