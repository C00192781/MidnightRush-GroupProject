///////////////////////////////////////////////
////// Contributors: Thomas Butler
//////
////// Class for loading in the Sound Menu
//////////////////////////////////////////////
#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;
#include <iostream>
using namespace std;

#define MAX_NUMBER_OF_SOUND_BUTTONS 3
#define ON_OFF_BUTTONS 2

class SoundScreen
{
public:
	int soundIndex = 0; // an index used to determine which button in the Sound MENU is selected
	int onOffIndex = 0;
	SoundScreen(float base, float height); // for Sound MENU window
	~SoundScreen();

	SoundScreen();

	// methods for traversing the Sound MENU
	void Up();
	void Down();
	void onOff();
	int useSoundButtons() { return soundIndex; }

	void Reset();
	void moveSound();

	void draw(sf::RenderWindow &window);
	void Load(Texture&); //Loads all external assets

	Sprite getSprite() { return m_soundAdjSprite; };

	//Sets the volume for the sound
	int soundValue = 50;
	int newSoundValue;

	//Used to turn the sound on and off 
	//(i.e if setSound == false there will be no sound)
	bool setSound = true;

private:
	sf::Text sound[MAX_NUMBER_OF_SOUND_BUTTONS];
	sf::Text noSound[ON_OFF_BUTTONS];
	sf::Font myFont;

	sf::Texture myTexture;
	sf::Sprite mySprite;

	//Indicates if sound is on or off
	sf::Texture m_tickTexture;
	sf::Sprite m_tickSprite;
	Vector2f m_tickPosition;

	//Adjust the volume accuratly
	sf::Texture m_soundBarTexture;
	sf::Sprite m_soundBarSprite;
	Vector2f m_soundBarPosition;

	sf::Texture m_soundAdjTexture;
	sf::Sprite m_soundAdjSprite;
	Vector2f m_soundAdjPosition;
};




