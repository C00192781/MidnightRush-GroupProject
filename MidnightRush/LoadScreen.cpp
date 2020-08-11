#include "LoadScreen.h"

#include <iostream>;
using namespace std;

LoadScreen::LoadScreen(float width, float height)
{
	// Red back of bar
	if (!m_BackgroundTexture.loadFromFile("Sprites Folder/loadBack.png"))
	{
		/////////////////////
		//   Error          /
		/////////////////////
	}
	m_BackgroundSprite.setTexture(m_BackgroundTexture);
	//m_BackgroundSprite.setOrigin(-750, -750);
	m_BackgroundSprite.setPosition(750, 750);
	m_BackgroundSprite.setScale(1.0f, 1.0f);

	// Green Bar
	if (!m_BarTexture.loadFromFile("Sprites Folder/loadBar.png"))
	{
		/////////////////////
		//   Error          /
		/////////////////////
	}
	m_BarSprite.setTexture(m_BarTexture);
	//m_BarSprite.setOrigin(-765, -765);
	m_BarSprite.setPosition(765, 765);
	m_BarSprite.setScale(m_size, 1.0f);

	// Load in the black screen whichh reads "Loading"
	if (!m_LoadPageTexture.loadFromFile("Sprites Folder/loadPage.png"))
	{
		/////////////////////
		//   Error          /
		/////////////////////
	}
	m_LoadPage.setTexture(m_LoadPageTexture);
	m_LoadPage.setOrigin(0, 0);
}


LoadScreen::~LoadScreen()
{
}

void LoadScreen::ChangePercent()
{
	m_BarSprite.setScale(sf::Vector2f(m_size, 1.0f));

	if (m_size >= 0.0f && m_size <= 1.0f)
	{
		m_size += 0.005;
	}
	else
	{
		m_size = 1.0f;
	}
}
void LoadScreen::draw(sf::RenderWindow &window)
{
	window.draw(m_LoadPage);
	window.draw(m_BackgroundSprite);
	window.draw(m_BarSprite);
}

