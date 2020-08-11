///////////////////////////////////////////////
////// Contributors: Kevin Boylan
//////
////// Class for loading in the Options Menu
//////////////////////////////////////////////
#include "SFML/Graphics.hpp"

// Notes: #Pragma once, makes sure something is only included once
#define MAX_NUMBER_OF_OPTIONS_BUTTONS 3

class Options
{
public:
	int optionsIndex = 0; // an index used to determine which button in the OPTIONS MENU is selected
	Options(float base, float height); // for OPTIONS MENU window
	~Options();

	// methods for traversing the OPTIONS MENU
	void Up();
	void Down();
	int useOptionButtons() { return optionsIndex; }
	void Reset();

	void draw(sf::RenderWindow &window);

	// This is a boolean for what game state the Options Game State will return to ...
	// after you press the RETURN button.
	// This is after you've entered from it within,  either ...
	// the PAUSE MENU or the MAIN MENU.
	// true - makes the present game state Main
	// false - makes the present game state Options
	bool optionsReturn;

private:
	sf::Text options[MAX_NUMBER_OF_OPTIONS_BUTTONS];
	sf::Font myFont; // font for OPTIONS MENU buttons

	sf::Texture myTexture;
	sf::Sprite mySprite;
};
