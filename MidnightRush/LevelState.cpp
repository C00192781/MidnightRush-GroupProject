#include "LevelState.h"


LevelState::LevelState()
{

	//Next Level
	m_levelGoalSource = IntRect(0, 0, 35, 125);
	m_levelGoalSprite.setTextureRect(m_levelGoalSource);
	m_levelGoalSprite.setPosition(2000, 0);

	if (!m_levelGoalTexture.loadFromFile("Sprites Folder/nextLevel.png"))
	{
		// error...
	}

	m_levelCompleteSprite.setPosition(500, 500);
	//m_levelCompleteSprite.setOrigin(m_levelCompleteSource.width / 2, m_levelCompleteSource.height / 2);
	

	if (!m_levelCompleteTexture.loadFromFile("Sprites Folder/levelComplete.png"))
	{
		// error...
	}
	
}


LevelState::~LevelState()
{
}

void LevelState::Load(Texture& _hostageTexture)
{
	m_levelGoalSprite.setTexture(m_levelGoalTexture);
	
	if (levelComplete == true)
	{
		m_levelCompleteSprite.setTexture(m_levelCompleteTexture);
	}
}

bool LevelState::getLevelComplete()
{
	return levelComplete;
}

void LevelState::setLevelComplete(bool complete)
{
	levelComplete = complete;
}

void LevelState::draw(RenderWindow& _window)
{
	_window.draw(m_levelGoalSprite);
	
	if (levelComplete == true)
	{
		_window.draw(m_levelCompleteSprite);
	}
}

void LevelState::logoMove()
{
	if (levelComplete == true)
	{
		count++;
		if (count < 25)
		{
			m_levelCompleteSprite.setScale(1, 1);
		}
		else if (count >= 25)
		{
			m_levelCompleteSprite.setScale(1.5, 1.5);
		}
		if (count == 50)
		{
			count = 0;
		}
	}
}
