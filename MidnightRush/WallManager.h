//////////////////////////////////////////////////////////////
////////// Contributors: Kevin Boylan
//////////////////////////////////////////////////////////////

#pragma once

#include "Wall.h"
#include "Player.h"

class WallManager
{
public:
	WallManager();
	~WallManager();

	std::vector<shared_ptr<Wall>> getWallVector() { return wallVector; };
	

	/*void AddWall(sf::Vector2f position);*/
	

	void Update();
	
	void Draw(sf::RenderWindow &window);

	std::vector<shared_ptr<Wall>> wallVector;

	//Player player;

private:

};