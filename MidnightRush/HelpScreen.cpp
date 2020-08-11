#include "HelpScreen.h"

#include <iostream>;
using namespace std;

HelpScreen::HelpScreen(float width, float height)
{
	if (!m_helpTexture.loadFromFile("Sprites Folder/tempHelp.png"))
	{
		// error...
		cout << "Error Loading texture" << endl;
	}
	m_helpSprite.setTexture(m_helpTexture);
}


HelpScreen::~HelpScreen()
{
}

void HelpScreen::draw(sf::RenderWindow &window)
{
	window.draw(m_helpSprite);
}