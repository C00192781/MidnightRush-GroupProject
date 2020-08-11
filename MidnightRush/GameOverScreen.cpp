#include "GameOverScreen.h"

#include <iostream>;
using namespace std;

GameOverScreen::GameOverScreen(float width, float height)
{
	if (!m_gameOverTexture.loadFromFile("Sprites Folder/GameOver.jpg"))
	{
		// error...
		cout << "Error Loading texture" << endl;
	}
	m_gameOverSprite.setTexture(m_gameOverTexture);
	m_gameOverSprite.setOrigin(-410, -230);
	m_gameOverSprite.setScale(0.585f, 0.585f);
	
	
}


GameOverScreen::~GameOverScreen()
{
}

void GameOverScreen::draw(sf::RenderWindow &window)
{
	window.draw(m_gameOverSprite);
}
