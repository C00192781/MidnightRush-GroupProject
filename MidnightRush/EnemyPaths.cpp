//#include "EnemyAI.h"
//#include <iostream>
//#include <memory>
//
//EnemyAI::EnemyAI()
//{
//
//}
//
//
//EnemyAI::EnemyAI(std::shared_ptr<std::vector<sf::Vector2f>> waypoints)
//{
//
//	m_wayPoints = waypoints;
//	xPath = false;
//	yPath = false;
//	index = 0;
//};
//
//sf::Vector2f EnemyAI::update(sf::Vector2f enemyPos)
//{
//	//enemyPos.x++;
//
//	//m_wayPoints = getEnemyPath(1, 1, 1);
//
//	//getEnemyPath(1, 1, 1);
//	// ensures that movement we will only transition to the next waypoint once both the x and y parts of each waypoint have been reached
//	if (yPath == true && xPath == true)
//	{
//		xPath = false;
//		yPath = false;
//		index++;
//	}
//
//
//
//	// outlines conditions for the position to adjust, in relation to the waypoint
//	if (index < m_wayPoints->size())
//	{
//
//		/*if (left == true && up == true)
//		{
//		m_EnemySprite.setRotation(270);
//		}
//		if (left == true && down == true)
//		{
//		m_EnemySprite.setRotation(180);
//		}
//		if (right == true && up == true)
//		{
//		m_EnemySprite.setRotation(30);
//		}
//		if (right == true && down == true)
//		{
//		m_EnemySprite.setRotation(160);
//		}*/
//
//		if (enemyPos.x != m_wayPoints->at(index).x) // if the position isn't at the waypoint
//		{
//			if (enemyPos.x > m_wayPoints->at(index).x)  // if the position (for x) is greater than the waypoint going ->
//			{
//				enemyPos.x -= m_speed;  // then, the position will move left <-
//										/*left = true;
//										right = false;*/
//			}
//
//			if (enemyPos.x < m_wayPoints->at(index).x)  // if the position (for x) is less than the waypoint going <-
//			{
//				enemyPos.x += m_speed;  // then, the position will move right ->
//										/*right = true;
//										left = false;*/
//			}
//		}
//		else
//		{
//			xPath = true;
//		}
//
//		if (enemyPos.y != m_wayPoints->at(index).y)
//		{
//			if (enemyPos.y > m_wayPoints->at(index).y)  // if the position (for x) is greater than the waypoint going ->
//			{
//				enemyPos.y -= m_speed;  // then, the position will move left <-
//										/*up = true;
//										down = false;*/
//			}
//
//			if (enemyPos.y < m_wayPoints->at(index).y)   // if the position (for x) is less than the waypoint going <-
//			{
//				enemyPos.y += m_speed;  // then, the position will move right ->
//										/*down = true;
//										up = false;*/
//			}
//		}
//		else
//		{
//			yPath = true;
//		}
//
//		if (enemyPos.x > m_wayPoints->at(index).x - 10 && enemyPos.x < m_wayPoints->at(index).x + 10)
//		{
//			xPath = true;    // when the position for the x axis is reached (within a standard deviation of 1) for the waypoint, this bool is set to true
//		}
//
//		if (enemyPos.y > m_wayPoints->at(index).y + 10 && enemyPos.y < m_wayPoints->at(index).y + 10)
//		{
//			yPath = true;     // when the position for the y axis is reached (within a standard deviation of 1) for the waypoint, this bool is set to true
//		}
//	}
//
//	if (index >= m_wayPoints->size())
//	{
//		index = 0;
//	}
//	return enemyPos;
//}
