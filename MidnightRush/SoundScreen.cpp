// Written by Thomas Butler

#include "SoundScreen.h"

SoundScreen::SoundScreen(float base, float height)
{
	// loads in a font
	if (!myFont.loadFromFile("fonts/Shoguns Clan.ttf"))
	{
		// error
	}

	// Draws a tick to clearly show if the sound is on or off
	m_tickSprite.setPosition(1400, 300);
	if (!m_tickTexture.loadFromFile("Sprites Folder/tick.png"))
	{
		// error...
	}

	// The line the sound can vary between
	m_soundBarSprite.setPosition(1200, 600);
	if (!m_soundBarTexture.loadFromFile("Sprites Folder/soundBar.png"))
	{
		// error...
	}

	// The circle the shows how loud the volume is
	m_soundAdjSprite.setPosition(1400, 575);
	if (!m_soundAdjTexture.loadFromFile("Sprites Folder/soundAdj.png"))
	{
		// error...
	}

	// used to add in background image for menu
	if (!myTexture.loadFromFile("Sprites Folder/SoundBackground.png"))
	{
		// error
	}

	mySprite.setTexture(myTexture);
	mySprite.setScale(1.9f, 1.9f);

	soundIndex = 0;

	sound[0].setFont(myFont);
	sound[0].setScale(2.0f, 2.0f);
	sound[0].setPosition(sf::Vector2f(base / 3, height / 3));
	sound[0].setColor(sf::Color::Black);
	sound[0].setString("SOUND On/Off");

	sound[1].setFont(myFont);
	sound[1].setScale(2.0f, 2.0f);
	sound[1].setPosition(sf::Vector2f(base / 3, height / 2));
	sound[1].setColor(sf::Color::White);
	sound[1].setString("Adjust Volume");

	sound[2].setFont(myFont);
	sound[2].setScale(2.0f, 2.0f);
	sound[2].setPosition(sf::Vector2f(base / 2.25, height / 1.5));
	sound[2].setColor(sf::Color::White);
	sound[2].setString("Return");

	////////////////////////////////////////////
	onOffIndex = 0;

	noSound[0].setFont(myFont);
	noSound[0].setScale(2.0f, 2.0f);
	noSound[0].setPosition(sf::Vector2f(base / 1.5, height / 3));
	noSound[0].setColor(sf::Color::Black);
	noSound[0].setString("On");

	noSound[1].setFont(myFont);
	noSound[1].setScale(2.0f, 2.0f);
	noSound[1].setPosition(sf::Vector2f(base / 1.25, height / 3));
	noSound[1].setColor(sf::Color::White);
	noSound[1].setString("Off");

	newSoundValue = 50;

}

SoundScreen::~SoundScreen()
{

}
SoundScreen::SoundScreen(){}

void SoundScreen::Load(Texture& tickTexture)
{
	m_tickSprite.setTexture(m_tickTexture);
	m_soundBarSprite.setTexture(m_soundBarTexture);
	m_soundAdjSprite.setTexture(m_soundAdjTexture);
}

// Used to iterate upwards through the SOUND MENU. 
// Note: if you go up to the top of the menu, and then press the Up button, 
// the index will change to the button at the bottom of the SOUND MENU.
void SoundScreen::Up()
{
	// If you go up through the index past the top (below 0), the highlighted button will be the last one in the list 
	if (soundIndex == 0)
	{
		sound[soundIndex].setColor(sf::Color::White);
		soundIndex = 2;
		sound[soundIndex].setColor(sf::Color::Black);
	}

	else if (soundIndex == 1)
	{
		sound[soundIndex].setColor(sf::Color::White);
		soundIndex = 0;
		sound[soundIndex].setColor(sf::Color::Black);
	}

	else if (soundIndex == 2)
	{
		sound[soundIndex].setColor(sf::Color::White);
		soundIndex = 1;
		sound[soundIndex].setColor(sf::Color::Black);
	}

}

// Used to iterate downwards through the SOUND MENU. 
// Note: if you go up to the bottom of the menu, and then press the Down button, 
// the index will change to the button at the top of the SOUND MENU.
void SoundScreen::Down()
{
	// If you go down through the index past the bottom (exceeding 2), the highlighted button will be the first one in the list 
	if (soundIndex == 0)
	{
		sound[soundIndex].setColor(sf::Color::White);
		soundIndex = 1;
		sound[soundIndex].setColor(sf::Color::Black);
	}

	else if (soundIndex == 1)
	{
		sound[soundIndex].setColor(sf::Color::White);
		soundIndex = 2;
		sound[soundIndex].setColor(sf::Color::Black);
	}

	else if (soundIndex == 2)
	{
		sound[soundIndex].setColor(sf::Color::White);
		soundIndex = 0;
		sound[soundIndex].setColor(sf::Color::Black);
	}

}

void SoundScreen::onOff()
{
	// If you go down through the index past the bottom (exceeding 2), the highlighted button will be the first one in the list 
	if (onOffIndex == 0)
	{
		noSound[onOffIndex].setColor(sf::Color::White);
		onOffIndex = 1;
		noSound[onOffIndex].setColor(sf::Color::Black);
		setSound = false;
		m_tickSprite.setPosition(1700, 300);
	}

	else if (onOffIndex == 1)
	{
		noSound[onOffIndex].setColor(sf::Color::White);
		onOffIndex = 0;
		noSound[onOffIndex].setColor(sf::Color::Black);
		setSound = true;
		m_tickSprite.setPosition(1400, 300);
	}

	if (setSound == true)
	{
		soundValue = newSoundValue;
	}
	else if (setSound == false)
	{
		soundValue = 0;
	}
}

void SoundScreen::moveSound()
{
	if (setSound == true)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			m_soundAdjSprite.move(5, 0);
			soundValue++;
			newSoundValue = soundValue;
			cout << "SoundValue: " << soundValue << endl;

			if (getSprite().getPosition().x >= 1700)
			{
				m_soundAdjSprite.setPosition(1700, 575);
			}

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			m_soundAdjSprite.move(-5, 0);
			soundValue--;
			newSoundValue = soundValue;
			cout << "SoundValue: " << soundValue << endl;

			if (getSprite().getPosition().x <= 1200)
			{
				m_soundAdjSprite.setPosition(1200, 575);
			}
		}
	}
}

// This is used to reset the index to 0 upon returning to the SOUND Menu
void SoundScreen::Reset()
{
	soundIndex = 0;
	sound[0].setColor(sf::Color::Black);
	sound[1].setColor(sf::Color::White);
	sound[2].setColor(sf::Color::White);
}

// method for drawing the SOUND MENU
void SoundScreen::draw(sf::RenderWindow &window)
{
	// draws the background of the MENU
	window.draw(mySprite);
	window.draw(m_tickSprite);
	window.draw(m_soundAdjSprite);
	window.draw(m_soundBarSprite);
	// draws the buttons
	for (int i = 0; i < MAX_NUMBER_OF_SOUND_BUTTONS; i++)
	{
		window.draw(sound[i]);
	}

	for (int index = 0; index < ON_OFF_BUTTONS; index++)
	{
		window.draw(noSound[index]);
	}
}
