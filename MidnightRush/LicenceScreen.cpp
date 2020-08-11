#include "LicenceScreen.h"

#include <iostream>;
using namespace std;

LicenceScreen::LicenceScreen(float width, float height)
{
	if (!m_licenceTexture.loadFromFile("Sprites Folder/tempLicence.png"))
	{
		// error...
		cout << "Error Loading texture" << endl;
	}
	m_licenceSprite.setTexture(m_licenceTexture);
	m_licenceSprite.setOrigin(50,0);
	m_licenceSprite.setScale(1.9f, 1.9f);
}


LicenceScreen::~LicenceScreen()
{
}

void LicenceScreen::draw(sf::RenderWindow &window)
{
	window.draw(m_licenceSprite);
}