#include "SFML/Graphics.hpp"
#include <string>
#include <memory>

class EnemyAI
{

public:
	/*EnemyAI();
	EnemyAI(std::shared_ptr<std::vector<sf::Vector2f>> waypoints);*/


	float m_speed;
	// A set of waypoints for this AI path.
	std::shared_ptr<std::vector<sf::Vector2f>> m_wayPoints;

	/*sf::Vector2f update(sf::Vector2f enemyPos);*/


private:
	int index;
	bool xPath;
	bool yPath;

};