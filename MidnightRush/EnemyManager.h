//////////////////////////////////////////////////////////////
////////// Contributors: Kevin Boylan
//////////////////////////////////////////////////////////////

#pragma once

#include "Enemy.h"

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	std::vector<shared_ptr<Enemy>> getEnemyVector() { return enemyVector; };

	void AddEnemy(sf::Vector2f position);
	void EnemyReset();

	void Update();
	void Draw(sf::RenderWindow &window);

	std::vector<shared_ptr<Enemy>> enemyVector;

private:

};