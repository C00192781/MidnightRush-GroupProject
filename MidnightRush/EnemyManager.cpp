#include "EnemyManager.h"

EnemyManager::EnemyManager()
{

}

EnemyManager::~EnemyManager()
{

}


void EnemyManager::Draw(sf::RenderWindow &window)
{
	for (int index = 0; index < enemyVector.size(); index++)
	{
		enemyVector.at(index)->draw(window);
	}
}

void EnemyManager::Update()
{
	for (int index = 0; index < enemyVector.size(); index++)
	{
		enemyVector.at(index)->Update();
	}
}

void EnemyManager::AddEnemy(sf::Vector2f position)
{
	//enemyVector.clear();
}

void EnemyManager::EnemyReset()
{
	//enemyVector.clear();
}