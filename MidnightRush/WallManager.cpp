#include "WallManager.h"

WallManager::WallManager()
{
	
}

WallManager::~WallManager()
{

}


void WallManager::Draw(sf::RenderWindow &window)
{
	for (int index = 0; index < wallVector.size(); index++)
	{
		wallVector.at(index)->draw(window);
	}
}

void WallManager::Update()
{
	
	//cout << "yyyyyyyyyyyyyyyyyyyyyyyy" << playerPosition.x << endl;
	
	
}





//void WallManager::AddEnemy(sf::Vector2f position)
//{
//	//enemyVector.clear();
//}

//void WallManager::WallReset()
//{
//	//enemyVector.clear();
//}
