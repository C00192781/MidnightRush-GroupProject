/////////////////////////////////////////
////// Contributors: Kevin Boylan
//////
////// Class for loading in the Main Menu
////// Started: 25/10/2016
//////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <iostream>

#define MAX_NUMBER_OF_MENU_BUTTONS 3

class Menu
{
public:
	int buttonIndex = 0;  // used to determine which button in the MAIN MENU is selected
	Menu(float base, float height); // for MAIN MENU window
	~Menu();

	// methods for traversing the Main Menu
	void Up();
	void Down();
	int useMenuButtons() { return buttonIndex; }

	void Draw(sf::RenderWindow &window);

	sf::Clock myClock;
	float Ltimer = 0.0f;


private:
	sf::Text buttons[MAX_NUMBER_OF_MENU_BUTTONS];
	sf::Font myFont; // font for the MAIN MENU buttons

	sf::Texture myTexture;
	sf::Sprite mySprite;
};