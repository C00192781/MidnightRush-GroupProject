//////////////////////////////////////////////////////////////
////////// Contributors: Kevin Boylan
//////////////////////////////////////////////////////////////

#pragma once

#include "Hostage.h"
#include "Player.h"

class HostageManager
{
public:
	HostageManager();
	~HostageManager();

	std::vector<shared_ptr<Hostage>> hostageVector;
	std::vector<shared_ptr<Hostage>> getHostageVector() { return hostageVector; };
	

	void Update();

	void Draw(sf::RenderWindow &window);


private:

};
