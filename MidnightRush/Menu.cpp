#include "Menu.h"

Menu::Menu(float base, float height)
{
	// loads in a font
	if (!myFont.loadFromFile("fonts/Shoguns Clan.ttf"))
	{
		// error
	}

	// used to add in background image for menu
	if (!myTexture.loadFromFile("Sprites Folder/backgroundImage.png"))
	{
		// error
	}

	mySprite.setTexture(myTexture);
	mySprite.setScale(1.9f, 1.9f); // sets the scale to match to screen

								   // setting up an index for the buttons in the menu
	buttonIndex = 0;

	// sets up the appropriate variables for the Play Game Button
	buttons[0].setFont(myFont);
	buttons[0].setScale(2.0f, 2.0f);
	buttons[0].setPosition(sf::Vector2f(base / 2.25, height / 3));
	buttons[0].setColor(sf::Color::White);
	buttons[0].setString("PLAY GAME");

	// sets up the appropriate variables for the Options Button
	buttons[1].setFont(myFont);
	buttons[1].setScale(2.0f, 2.0f);
	buttons[1].setPosition(sf::Vector2f(base / 2.25, height / 2));
	buttons[1].setColor(sf::Color::Yellow);
	buttons[1].setString("OPTIONS");

	// sets up the appropriate variables for the Quit Game Button
	buttons[2].setFont(myFont);
	buttons[2].setScale(2.0f, 2.0f);
	buttons[2].setPosition(sf::Vector2f(base / 2.25, height / 1.5));
	buttons[2].setColor(sf::Color::Yellow);
	buttons[2].setString("QUIT");
}

Menu::~Menu()
{

}

// Used to iterate upwards through the MAIN MENU. 
// Note: if you go up to the top of the menu, and then press the Up button, 
// the index will change to the button at the bottom of the MAIN MENU.
void Menu::Up()
{
	Ltimer += myClock.getElapsedTime().asSeconds();
	if (buttonIndex == 0)
	{
		if (Ltimer == 200)
		{
			buttons[buttonIndex].setColor(sf::Color::Yellow);
		}
		buttons[buttonIndex].setColor(sf::Color::Yellow);
		buttonIndex = 2;
		buttons[buttonIndex].setColor(sf::Color::White);
	}
	else if (buttonIndex == 1)
	{
		buttons[buttonIndex].setColor(sf::Color::Yellow);
		buttonIndex = 0;
		buttons[buttonIndex].setColor(sf::Color::White);
	}
	else if (buttonIndex == 2)
	{
		buttons[buttonIndex].setColor(sf::Color::Yellow);
		buttonIndex = 1;
		buttons[buttonIndex].setColor(sf::Color::White);
	}
}

// Used to iterate downwards through the MAIN MENU.
// Note: if you go down to the bottom of the menu, and then press the Down button, 
//the index will adjust to the button at the top of the menu.
void Menu::Down()
{
	if (buttonIndex == 0)
	{
		buttons[buttonIndex].setColor(sf::Color::Yellow);
		buttonIndex = 1;
		buttons[buttonIndex].setColor(sf::Color::White);
	}
	else if (buttonIndex == 1)
	{
		buttons[buttonIndex].setColor(sf::Color::Yellow);
		buttonIndex = 2;
		buttons[buttonIndex].setColor(sf::Color::White);
	}
	else if (buttonIndex == 2)
	{
		buttons[buttonIndex].setColor(sf::Color::Yellow);
		buttonIndex = 0;
		buttons[buttonIndex].setColor(sf::Color::White);
	}
}

// method for drawing the MAIN MENU
void Menu::Draw(sf::RenderWindow &window)
{
	// draws the background of the MAIN MENU
	window.draw(mySprite);
	// draws the buttons
	for (int index = 0; index < MAX_NUMBER_OF_MENU_BUTTONS; index++)
	{
		window.draw(buttons[index]);
	}
}