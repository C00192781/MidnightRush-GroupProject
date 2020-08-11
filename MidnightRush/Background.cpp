#include "Background.h"

#include <iostream>

Background::Background()
{
	// set up a shared pointer holding the number of levels
	levelCount = std::shared_ptr<int>(new int(0));
	SelectMap(*levelCount);
}

void Background::Update(sf::Event &event, Score &score, SoundScreen & sound)
{
	enemyManager.Update();
	for (int index = 0; index < wallManager.wallVector.size(); index++)
	{
		wallManager.wallVector.at(index)->collisionDetection(getPlayer().m_PlayerSprite.getPosition(), getPlayer());
	}

	player.BulletCollisions(enemyManager.enemyVector);

	for (int index = 0; index < hostageManager.hostageVector.size(); index++)
	{
		hostageManager.hostageVector.at(index)->Update(getPlayer());
	}

	collisionDetection.Update(player, enemyManager, weapon, levelState, hostageManager, audio, score, event, sound);
	

	// For Testing Purposes  
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		ResetMap();
		SelectMap(*levelCount);
	}


	if (levelState.levelComplete == true)
	{
		
		/*if (levelCount == std::shared_ptr<int>(new int(0)))
		{*/
			startingPosition = Vector2f(3200, 3600);
			player.m_PlayerSprite.setPosition(startingPosition);
			player.saving = false;
			player.alive = true;
			ResetMap();
			SelectMap(2);
			levelState.setLevelComplete(true);
		//}
		//else if (levelCount == std::shared_ptr<int>(new int(1)))
		//{

		//	/*levelCount == std::shared_ptr<int>(new int(2));
		//	SelectMap(*levelCount);*/

		//	SelectMap(2);
		//	levelState.levelComplete = false;
		//	
		//}
		
	}

	// For Testing Purposes  
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		SelectMap(1);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		SelectMap(2);
	}
}

// method for drawing the tiles/sprites from the sprite vector for the background
void Background::Draw(sf::RenderWindow *window)
{
	for (int index = 0; index < floorVector.size(); index++)
	{
		floorVector.at(index)->draw(*window);
	}

	enemyManager.Draw(*window);
	wallManager.Draw(*window);
	hostageManager.Draw(*window);
}


void Background::SelectMap(int mapCounter)
{
	cout << "The ghost of 3rd year" << endl;
	// Basically, if it's the first level, these are the variables for that map
	if (mapCounter == 0)
	{
		//startingPosition = Vector2f(3200, 3600);
		startingPosition = Vector2f(3200, 3600);
		player.m_PlayerSprite.setPosition(startingPosition);
		//levelState.m_levelCompleteSprite.setPosition(3500, 600);
		weapon.m_RifleSprite.setPosition(4200, 2500);
		levelState.m_levelGoalSprite.setPosition(3600, 900);
		levelState.m_levelGoalSprite.setRotation(90);

		*levelCount = mapCounter;
		maxRow = 30;
		maxCol = 30;
		ResetMap();
		pMap = (int*)map;
		CreateMap();
	}

	// Second Map
	if (mapCounter == 1)
	{
		startingPosition = Vector2f(3000, 3500);
		player.m_PlayerSprite.setPosition(startingPosition);

		weapon.m_RifleSprite.setPosition(3000, 3500);
		weapon.m_BatSprite.setPosition(3100, 2200);

		*levelCount = mapCounter;
		maxRow = 30;
		maxCol = 30;
		ResetMap();
		pMap = (int*)map2;
		CreateMap();
	}

	// Third Map
	if (mapCounter == 2)
	{
		startingPosition = Vector2f(3200, 3600);
		player.m_PlayerSprite.setPosition(startingPosition);
		weapon.m_RifleSprite.setPosition(5200, 1500);

		*levelCount = mapCounter;
		maxRow = 30;
		maxCol = 30;
		ResetMap();
		pMap = (int*)map3;
		CreateMap();
	}
}

void Background::ResetMap()
{
	floorVector.clear();
	hostageManager.hostageVector.clear();
	enemyManager.enemyVector.clear();
	floorVector.clear();
	wallManager.wallVector.clear();
	

}

void Background::Restart()
{
	ResetMap();
	SelectMap(*levelCount);
}

// from this method we can create a map
void Background::CreateMap()
{
	// finds out the maximum amount of tiles on the map
	maxSquares = maxRow * maxCol;
	
	for (int column = 0; column < maxCol; column++)
	{
		for (int row = 0; row < maxRow; row++)
		{
			if (pMap[maxCol*(row)+column] == 1) // Floor With Wall on Top
			{
				wallManager.wallVector.push_back(shared_ptr<Wall>(new Wall(sf::Vector2f(column * 140 + 2000, row * 140), 0)));
				floorVector.push_back(shared_ptr<Floor>(new Floor(sf::Vector2f(column * 140 + 2000, row * 140), 0)));
				
			}
			else if (pMap[maxCol*(row)+column] == 2) // Hallway Tile
			{
				floorVector.push_back(shared_ptr<Floor>(new Floor(sf::Vector2f(column * 140 + 2000, row * 140), 1)));
			}
			else if (pMap[maxCol*(row)+column] == 3)  // Floor Tile
			{
				floorVector.push_back(shared_ptr<Floor>(new Floor(sf::Vector2f(column * 140 + 2000, row * 140), 0)));
			}

			else if (pMap[maxCol*(row)+column] == 4) // Enemy with Floor, Path: 1
			{
				
				enemyManager.enemyVector.push_back(shared_ptr<Enemy>(new Enemy(sf::Vector2f(column * 140 + 2000 , row * 140), 1, *levelCount)));
				floorVector.push_back(shared_ptr<Floor>(new Floor(sf::Vector2f(column * 140 + 2000, row * 140), 0)));
			}

			else if (pMap[maxCol*(row)+column] == 5) // Enemy with Floor, Path: 2
			{
				enemyManager.enemyVector.push_back(shared_ptr<Enemy>(new Enemy(sf::Vector2f(column * 140 + 2000, row * 140), 2, *levelCount)));
				floorVector.push_back(shared_ptr<Floor>(new Floor(sf::Vector2f(column * 140 + 2000, row * 140), 0)));
			}

			else if (pMap[maxCol*(row)+column] == 6) // Hostage with Floor
			{
				hostageManager.hostageVector.push_back(shared_ptr<Hostage>(new Hostage(sf::Vector2f(column * 140 + 2000, row * 140))));
				floorVector.push_back(shared_ptr<Floor>(new Floor(sf::Vector2f(column * 140 + 2000, row * 140), 0)));
			}

			else if (pMap[maxCol*(row)+column] == 7) // Floor with Wall on Left
			{

				wallManager.wallVector.push_back(shared_ptr<Wall>(new Wall(sf::Vector2f(column * 140 + 2000, row * 140), 90)));
				floorVector.push_back(shared_ptr<Floor>(new Floor(sf::Vector2f(column * 140 + 2000, row * 140), 0)));
			}
			else if (pMap[maxCol*(row)+column] == 8) // Hallway with Wall on Left
			{
				wallManager.wallVector.push_back(shared_ptr<Wall>(new Wall(sf::Vector2f(column * 140 + 2000, row * 140), 90)));
				floorVector.push_back(shared_ptr<Floor>(new Floor(sf::Vector2f(column * 140 + 2000, row * 140), 1)));
			}
			else if (pMap[maxCol*(row)+column] == 9) // Hallway with Wall On Top
			{

				wallManager.wallVector.push_back(shared_ptr<Wall>(new Wall(sf::Vector2f(column * 140 + 2000, row * 140), 0)));
				floorVector.push_back(shared_ptr<Floor>(new Floor(sf::Vector2f(column * 140 + 2000, row * 140), 1)));
			}

			else if (pMap[maxCol*(row)+column] == 10) // Hallway Floor with Wall on Right
			{
				wallManager.wallVector.push_back(shared_ptr<Wall>(new Wall(sf::Vector2f(column * 140 + 2140, row * 140), 90)));
				floorVector.push_back(shared_ptr<Floor>(new Floor(sf::Vector2f(column * 140 + 2000, row * 140), 1)));
			}

			else if (pMap[maxCol*(row)+column] == 11) // Hallway with Enemy, Path: 1
			{
				
				enemyManager.enemyVector.push_back(shared_ptr<Enemy>(new Enemy(sf::Vector2f(column * 140 + 2000, row * 140), 1, *levelCount)));
				floorVector.push_back(shared_ptr<Floor>(new Floor(sf::Vector2f(column * 140 + 2000, row * 140), 1)));
			}

			else if (pMap[maxCol*(row)+column] == 12) // Floor with Wall on Bottom
			{
				wallManager.wallVector.push_back(shared_ptr<Wall>(new Wall(sf::Vector2f(column * 140 + 2000, row * 140 + 140), 0)));
				
				floorVector.push_back(shared_ptr<Floor>(new Floor(sf::Vector2f(column * 140 + 2000, row * 140), 0)));
			}

			else if (pMap[maxCol*(row)+column] == 13) // Floor with Wall on Right
			{
				wallManager.wallVector.push_back(shared_ptr<Wall>(new Wall(sf::Vector2f(column * 140 + 2140, row * 140), 90)));
				floorVector.push_back(shared_ptr<Floor>(new Floor(sf::Vector2f(column * 140 + 2000, row * 140), 0)));
			}

			else if (pMap[maxCol*(row)+column] == 14) // Floor with Wall on Top
			{
				wallManager.wallVector.push_back(shared_ptr<Wall>(new Wall(sf::Vector2f(column * 140 + 2000, row * 140), 0)));
				floorVector.push_back(shared_ptr<Floor>(new Floor(sf::Vector2f(column * 140 + 2000, row * 140), 0)));
			}

			else if (pMap[maxCol*(row)+column] == 15) // Hallway with Wall on Bottom
			{
				wallManager.wallVector.push_back(shared_ptr<Wall>(new Wall(sf::Vector2f(column * 140 + 2000, row * 140 + 140), 0)));
				floorVector.push_back(shared_ptr<Floor>(new Floor(sf::Vector2f(column * 140 + 2000, row * 140), 1)));
			}

			else if (pMap[maxCol*(row)+column] == 16) // Enemy with Background Tile, Path: 3
			{
				enemyManager.enemyVector.push_back(shared_ptr<Enemy>(new Enemy(sf::Vector2f(column * 140 + 2000, row * 140), 3, *levelCount)));
				floorVector.push_back(shared_ptr<Floor>(new Floor(sf::Vector2f(column * 140 + 2000, row * 140), 2)));
			}

			else if (pMap[maxCol*(row)+column] == 17) // Background Tile (it's purple)
			{
				floorVector.push_back(shared_ptr<Floor>(new Floor(sf::Vector2f(column * 140 + 2000, row * 140), 2)));
			}
			else if (pMap[maxCol*(row)+column] == 18) // Background Tile with Wall on Top
			{
				floorVector.push_back(shared_ptr<Floor>(new Floor(sf::Vector2f(column * 140 + 2000, row * 140), 2)));
				wallManager.wallVector.push_back(shared_ptr<Wall>(new Wall(sf::Vector2f(column * 140 + 2000, row * 140), 0)));
			}
			else if (pMap[maxCol*(row)+column] == 19) // Background Tile with Wall on Left
			{
				floorVector.push_back(shared_ptr<Floor>(new Floor(sf::Vector2f(column * 140 + 2000, row * 140), 2)));
				wallManager.wallVector.push_back(shared_ptr<Wall>(new Wall(sf::Vector2f(column * 140 + 2000, row * 140), 90)));
			}

			else if (pMap[maxCol*(row)+column] == 20) // Background Tile with Wall on Right
			{
				floorVector.push_back(shared_ptr<Floor>(new Floor(sf::Vector2f(column * 140 + 2000, row * 140), 2)));
				wallManager.wallVector.push_back(shared_ptr<Wall>(new Wall(sf::Vector2f(column * 140 + 2140, row * 140), 90)));
			}

			else if (pMap[maxCol*(row)+column] == 21) // Enemy with Background Tile, Path: 4
			{
				enemyManager.enemyVector.push_back(shared_ptr<Enemy>(new Enemy(sf::Vector2f(column * 140 + 2000, row * 140), 4, *levelCount)));
				floorVector.push_back(shared_ptr<Floor>(new Floor(sf::Vector2f(column * 140 + 2000, row * 140), 2)));
			}

			else if (pMap[maxCol*(row)+column] == 22) // Enemy with Background Tile, Path: 5
			{
				enemyManager.enemyVector.push_back(shared_ptr<Enemy>(new Enemy(sf::Vector2f(column * 140 + 2000, row * 140), 5, *levelCount)));
				floorVector.push_back(shared_ptr<Floor>(new Floor(sf::Vector2f(column * 140 + 2000, row * 140), 2)));
			}



		}
	}
}


// the assigned layout of the first map
// operates on values assigned to pMap in CreateMap() method
const int Background::map[30][30]   // 39  going across, 30 going down
{
	// 30 rows, 30 columns
	{17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,17,17,17,17,17,17,17,16,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,17,17,17, 8,10,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,17,17,17, 8,10,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,17,17,17, 8, 2, 9, 9, 9, 9,14,14,14,19,17,17,17,17,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,17,17,20,15,15,15,15,15,15, 3, 3, 3,19,17,17,17,17,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, 7, 3,13,14,14,14,14,19,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, 7, 3,13, 3, 3, 3,13,17,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, 7, 3,13, 3, 6, 3,13,17,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, 7, 3,13, 3, 3, 3,13,17,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,17,17,17,17,17,17,20,14, 1, 3, 3,13, 3, 3, 3,13,17,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,17,17,17,17,17,17,17, 7, 3, 3, 3,13, 3, 3, 3,13,17,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,17,17,17,17,17,17,17, 7, 3, 3, 3,13, 3, 3, 3,13,17,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,17,17,17,17,17,17,17, 7, 3, 3, 3, 3, 5, 3, 3,13,17,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,17,17,17,17,17,17,17, 7, 3, 3, 3, 3, 3, 3, 3,13,17,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,17,17,17,17,17,17,17, 7, 4,12,12,12,12,12,12,13,17,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,17,17,17,17,17,17,17, 8,10,17,17,17,17,17,17,18,17,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,17,17,17,17,17,17,17, 8,10,17,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,17,17,17,17,17,17,17, 8,10,17,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,17,17,17,17,17,17,17, 8,10,17,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,17,17,17,17,17,17,17, 8,10,17,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,20, 9, 9, 9, 9, 9, 9, 2,10,17,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,20.,15,15,15,15,15,15,15,15,19,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, }
};

// the assigned layout of the SECOND map
// operates on values assigned to pMap in CreateMap() method
const int Background::map2[30][30]   // 39  going across, 30 going down
{
	// 30 rows, 30 columns
	{ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,17,20,2, 2, 19,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,17,20,2, 2, 19,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,17,20,2, 2, 19,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,17,20,3, 3, 14,14,14,14,14,14,14,14,14,14,14,14,19,17,17,17,17,17,17,17,17, },
	{ 17,17,17,22,17,17,20,3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 6, 19,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,17,17,18,18,18,18,18,18,18,18,18,18,18,7, 3, 3, 19,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,20,14,14,14,14,14,14,14,14,14,19,17,20,3, 3, 3, 19,17,17,17,17,17,17,17,17, },
	{ 17,17,17,21,17,20,3, 3, 3, 3, 3, 3, 3, 3, 3, 19,17,20,3, 3, 3, 19,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,20,3, 3, 3, 3, 3, 3, 3, 3, 3, 19,17,20,3, 3, 3, 19,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,20,3, 3, 13,18,18,18,18,7, 3, 14,14,14,3, 3, 3, 19,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,20,3 ,3, 3, 19,17,17,17,7, 3, 3, 3, 3, 3, 3, 3, 19,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,20,3, 3, 3, 19,17,17,17,18,18,18,18,18,18,18,18,17,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,20,3 ,3, 3, 14,14,14,14,14,14,14,14,14,14,14,14,19,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,20,3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 19,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,20,3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 19,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,17,18,18,18,18,18,18,18,18,18,18,18,18,7, 5, 3, 19,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,20,14,14,14,14,14,14,14,14,14,19,17,17,7, 3, 3, 19,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,17,7, 3, 3, 3, 3, 3, 3, 3, 3, 19,17,17,7, 3, 3, 19,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,17,7, 3, 3, 4, 3, 3, 3, 3, 3, 19,17,17,7, 3, 3, 19,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,17,8, 2, 10,18,18,18,7, 3, 3, 19,17,17,7, 3, 3, 19,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,17,8, 2, 10,17,17,17,7, 3, 3, 19,17,17,7, 3, 3, 19,16,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,17,8, 2, 10,17,17,17,7, 3, 3, 19,17,17,7, 3, 3, 19,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,17,8, 2, 10,17,17,17,7, 3, 3, 14,14,14,3, 3, 3, 19,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,17,8, 2, 10,17,17,17,7, 3, 3, 3, 3, 3, 3, 3, 3, 19,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,17,8, 2, 10,17,17,17,7, 3, 3, 3, 3, 3, 3, 3, 3, 19,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,17,18,18,18,17,17,17,18,18,18,18,18,18,18,18,18,17,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, }
};

const int Background::map3[30][30]   // 39  going across, 30 going down
{
	// 30 rows, 30 columns
	{ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,20, 2, 2, 2,19,17, },
	{ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,20,14,14,14,14,14,19,17,20, 2, 2, 2,19,17, },
	{ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, 7, 3, 3, 3,13,17,17,20, 2, 2, 2,19,17, },
	{ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, 7, 3, 3, 3,13,17,17,20, 2, 2, 2,19,17, },
	{ 17,17,17,17,17,17,17,17,17,17,20, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 9, 9, 9, 9, 2, 2, 2,19,17, },
	{ 17,17,17,17,17,17,17,17,17,17,20, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,15, 2, 2, 4, 2, 2,19,17, },
	{ 17,17,17,17,17,17,17,17,17,17,20, 2, 2,15,15, 2, 2, 2, 2, 2, 2, 2,19,18,18,18,18,18,17,17, },
	{ 17,17,17,17,17,17,17,17,17,17,20, 2, 2,19,20,14, 3, 3,14, 8,10,14,14,14,14,19,17,17,17,17, },
	{ 17,17,17,17,17,17,17,17,17,17,20, 2, 2,19,20, 3, 6, 3,13,14,14, 7, 4, 3,13,17,17,17,17,17, },
	{ 17,17,17,17,17,17,17,17,17,17,20, 2, 2,19,20, 3, 3, 3,13, 3, 3, 7, 3, 3,13,17,17,17,17,17, },
	{ 17,17,17,17,17,17,17,17,17,17,20, 2, 2, 9, 9, 2, 2, 2, 2, 2, 2, 9, 2, 2, 9,19,17,17,17,17, },
	{ 17,17,17,17,17,17,17,17,17,17,20, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,19,17,17,17,17, },
	{ 17,17,17,17,17,17,17,17,17,17,20,15,15,15,15,15,15,15,15,15,15,15, 2, 2, 2,19,17,17,17,17, },
	{ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,20, 2, 2, 2,19,17,17,17,17, },
	{ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,20, 2, 2, 2,19,17,17,17,17, },
	{ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,20, 2, 2, 2,19,17,17,17,17, },
	{ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,20, 2, 2, 2,19,17,17,17,17, },
	{ 17,17,17,17,17,17,17,17,17,16,17,17,17,17,17,17,17,17,17,17,17,20, 2, 2, 2,19,17,17,17,17, },
	{ 17,17,17,17,17,17,20, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2,19,17,17,17,17, },
	{ 17,17,17,17,17,17,17, 8, 2, 2,15,15,15,15, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,19,17,17,17,17, },
	{ 17,17,17,17,17,17,17, 8, 2,10,17,17,17,17, 8, 2,10,18,18,18,18,18,18,18,18,17,17,17,17,17, },
	{ 17,17,17,17,17,17,17, 8, 2,10,17,17,17,17, 8, 2,10,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,17,17, 8, 2,10,17,17,17,17, 8, 2,10,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,17,17, 8, 2, 2, 9, 9, 9, 9, 2, 2,10,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,17,20,15,15,15,15,15,15,15,15,15,15,19,17,17,17,17,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, },
	{ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, }
};


// method so we can easily return the level we are on
std::shared_ptr<int> Background::getMapCount()
{
	return levelCount;
}

Player & Background::getPlayer()
{
	return player;
}

Weapon & Background::getWeapon()
{
	return weapon;
}

LevelState & Background::getLevelState()
{
	return levelState;
}

EnemyManager & Background::getEnemyManager()
{
	return enemyManager;
}
//
//Score & Background::getScore()
//{
//	return score;
//}

SoundScreen & Background::getSoundScreen()
{
	return sound;
}