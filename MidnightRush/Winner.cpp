#include "Winner.h"

#include <iostream>;
using namespace std;

WinnerScreen::WinnerScreen(float width, float height)
{
	if (!m_winnerTexture.loadFromFile("Sprites Folder/tempWinner.png"))
	{
		// error...
		cout << "Error Loading texture" << endl;
	}
	m_winnerSprite.setTexture(m_winnerTexture);
}


WinnerScreen::~WinnerScreen()
{
}

void WinnerScreen::draw(sf::RenderWindow &window)
{
	window.draw(m_winnerSprite);
}
