////////////////////////////////////////////////////////////////////////////////////////////////////
//////  Contributors: Kevin Boylan
//////
//////	PAUSE MENU which will have certain options and will suspend the PLAY gamestate
//////	Activated by pressing Escape Key
//////  Return by pressing Escape Key again or navigating down to and pressing on the Return button
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "SFML/Graphics.hpp"

// Notes: #Pragma once, makes sure something is only included once

#define MAX_NUMBER_OF_PAUSE_BUTTONS 4

class Pause
{
public:
	int pauseIndex = 0; // an index used to determine which button in the PAUSE MENU is selected
	Pause(float base, float height); // for PAUSE MENU window
	~Pause();

	// methods for traversing the PAUSE MENU
	void Up();
	void Down();
	void Reset();
	int usePauseButtons() { return pauseIndex; }
	void draw(sf::RenderWindow &window);

	float pauseX;
	float pauseY;

private:
	sf::Text pause[MAX_NUMBER_OF_PAUSE_BUTTONS];
	sf::Font myFont; // font for PAUSE MENU buttons

	sf::Texture myTexture;
	sf::Sprite mySprite;
};
