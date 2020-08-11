#include "HostageManager.h"

HostageManager::HostageManager()
{

}

HostageManager::~HostageManager()
{

}


void HostageManager::Draw(sf::RenderWindow &window)
{
	for (int index = 0; index < hostageVector.size(); index++)
	{
		hostageVector.at(index)->draw(window);
	}
}

void HostageManager::Update()
{
	
	
}
