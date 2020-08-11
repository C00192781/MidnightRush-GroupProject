#include "Enemy.h"


Enemy::Enemy()
{

}

Enemy::Enemy(sf::Vector2f position, int path, int levelCount)
{
	//Enemy Alive walking around
	m_EnemyPosition = position;
	m_EnemySource = IntRect(30, 0, 85, 130);
	m_EnemySprite.setTextureRect(m_EnemySource);
	//enemyPosition = m_enemyAI.update(enemyPosition);
	//m_EnemySprite.setPosition(enemyPosition);
	m_EnemySprite.setPosition(m_EnemyPosition);

	m_EnemyHealth = 50;


	if (!m_EnemyTexture.loadFromFile("Sprites Folder/enemyOneSheet.png"))
	{
		// error...
	}

	//Enemy Death Sprite
	m_EnemyDeathSource = IntRect(0, 0, 180, 180);
	m_EnemyDeathSprite.setTextureRect(m_EnemyDeathSource);

	if (!m_EnemyDeathTexture.loadFromFile("Sprites Folder/enemy_death_sheet.png"))
	{
		// error...
	}
	
	m_wayPoints = getEnemyPath(levelCount, path);

	xPath = false;
	yPath = false;

	m_speed = 5;
	index = 0;

	enemyLife = true;
	shootDeathTimer = 0;

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//Swinging Textures
	////////////////////////////////////////////////////////////////////////////////////////////////
	//Enemy Death Sprite
	m_EnemySwingSource = IntRect(15, 30, 95, 150);
	m_EnemySwingSprite.setTextureRect(m_EnemySwingSource);
	m_EnemySwingSprite.setPosition(m_EnemySprite.getPosition());
	if (!m_EnemySwingTexture.loadFromFile("Sprites Folder/enemySwing.png"))
	{
		// error...
	}
}

Enemy::~Enemy()
{
}

void Enemy::Load(Texture& _enemyTexture)
{
	if (alive == true && enemySwing == false)
	{
		m_EnemySprite.setTexture(m_EnemyTexture);
	}
	else if (alive == false && enemySwing == false)
	{
		m_EnemyDeathSprite.setTexture(m_EnemyDeathTexture);
	}
	else if (enemySwing == true && alive == true)
	{
		m_EnemySwingSprite.setTexture(m_EnemySwingTexture);
	}
}

void Enemy::draw(RenderWindow& _window)
{
	Load(m_EnemyTexture);

	if (alive == true && enemySwing == false)
	{
		_window.draw(m_EnemySprite);
	}
	else if (alive == false && enemySwing == false)
	{
		_window.draw(m_EnemyDeathSprite);
	}
	if (enemySwing == true && alive == true)
	{
		_window.draw(m_EnemySwingSprite);
	}

}

void Enemy::Update()
{
	if (alive == false && enemySwing == false)
	{
		Death();
	}

	////////////////////////////////////
	test++;
	//cout << test << endl;
	if (test >= 100) //&& enemyDirection == Direction::Right)
	{
		//enemySwing = true;
		test = 0;
	}
	//////////////////////////////////////

	if (enemySwing == true && alive == true)
	{
		Attack();
	}
	//cout << m_wayPoints << endl;;

	//m_EnemyPosition.x++;
	
	m_EnemyPosition = update(m_EnemyPosition);	
	//cout << m_EnemyPosition.x << endl;
	m_EnemySprite.setPosition(update(m_EnemyPosition));

//	cout << "Waypoints yp " << m_wayPoints->at(0).x << endl;

}

void Enemy::Death()
{
	if (enemyDirection == Direction::Down) //Facing Down
	{
		m_EnemyDeathSource.left = 0;
		m_EnemyDeathSprite.setTextureRect(m_EnemyDeathSource);
		//When the player dies they die in the same position they were standimg
		m_EnemyDeathSprite.setPosition(m_EnemySprite.getPosition());
	}
	else if (enemyDirection == Direction::Up) //Facing Up
	{
		m_EnemyDeathSource.left = 180;
		m_EnemyDeathSprite.setTextureRect(m_EnemyDeathSource);
		//When the player dies they die in the same position they were standimg
		m_EnemyDeathSprite.setPosition(m_EnemySprite.getPosition());
	}
	else if (enemyDirection == Direction::Right) //Facing Right
	{
		m_EnemyDeathSource.left = 360;
		m_EnemyDeathSprite.setTextureRect(m_EnemyDeathSource);
		//When the player dies they die in the same position they were standimg
		m_EnemyDeathSprite.setPosition(m_EnemySprite.getPosition());
	}
	else if (enemyDirection == Direction::Left) //Facing left
	{
		m_EnemyDeathSource.left = 540;
		m_EnemyDeathSprite.setTextureRect(m_EnemyDeathSource);
		//When the player dies they die in the same position they were standimg
		m_EnemyDeathSprite.setPosition(m_EnemySprite.getPosition());
	}
}


std::shared_ptr<std::vector<sf::Vector2f>> Enemy::getEnemyPath(int mapCount, int path)
{
	std::shared_ptr<std::vector<sf::Vector2f>> waypoints;
	waypoints.reset(new std::vector<sf::Vector2f>());


	if (mapCount == 0)
	{
		if (path == 1)
		{
			waypoints->push_back(sf::Vector2f(4070, 2600));
			waypoints->push_back(sf::Vector2f(4070, 3550));
			waypoints->push_back(sf::Vector2f(3220, 3550));
			waypoints->push_back(sf::Vector2f(4070, 3550));
		}
		
		else if (path == 2)
		{
			waypoints->push_back(sf::Vector2f(4720, 2500));
			waypoints->push_back(sf::Vector2f(5020, 2500));
			waypoints->push_back(sf::Vector2f(5070, 1500));
			waypoints->push_back(sf::Vector2f(4720, 1500));
		}

		else if (path == 3)
		{
			waypoints->push_back(sf::Vector2f(4240, 1205));
			waypoints->push_back(sf::Vector2f(3520, 1205));
			waypoints->push_back(sf::Vector2f(3520, 900));
			waypoints->push_back(sf::Vector2f(3520, 1205));
			waypoints->push_back(sf::Vector2f(4240, 1205));
		}
	}
	//Level 2
	else if (mapCount == 1)
	{
		if (path == 1)
		{
			waypoints->push_back(sf::Vector2f(3260, 2700));
			waypoints->push_back(sf::Vector2f(3820, 2700));
			waypoints->push_back(sf::Vector2f(3820, 3550));
			waypoints->push_back(sf::Vector2f(3820, 2700));

		}

		else if (path == 2)
		{
			waypoints->push_back(sf::Vector2f(4800, 2500));
			waypoints->push_back(sf::Vector2f(4800, 3550));

		}

		else if (path == 3)
		{
			waypoints->push_back(sf::Vector2f(4600, 3550));
			waypoints->push_back(sf::Vector2f(4600, 2500));
		}

		else if (path == 4)
		{
			waypoints->push_back(sf::Vector2f(3120, 1300));
			waypoints->push_back(sf::Vector2f(4000, 1300));
			waypoints->push_back(sf::Vector2f(3120, 1300));
			waypoints->push_back(sf::Vector2f(3120, 2100));
		}

		else if (path == 5)
		{
			waypoints->push_back(sf::Vector2f(3260, 840));
			waypoints->push_back(sf::Vector2f(4280, 840));
		}
	}
	else if (mapCount == 2)
	{
		if (path == 1)
		{
			waypoints->push_back(sf::Vector2f(5200, 1400));
			waypoints->push_back(sf::Vector2f(5200, 2800));
			/*waypoints->push_back(sf::Vector2f(4500, 2000));
			waypoints->push_back(sf::Vector2f(5000, 2000));*/


		}

		else if (path == 2)
		{
			waypoints->push_back(sf::Vector2f(4720, 2500));
			waypoints->push_back(sf::Vector2f(5020, 2500));
			waypoints->push_back(sf::Vector2f(5070, 1500));
			waypoints->push_back(sf::Vector2f(4720, 1500));
		}

		else if (path == 3)
		{
			waypoints->push_back(sf::Vector2f(4220, 2900));
			waypoints->push_back(sf::Vector2f(4220, 3600));
			waypoints->push_back(sf::Vector2f(3100, 3600));
			waypoints->push_back(sf::Vector2f(3100, 2900));
			
			//waypoints->push_back(sf::Vector2f(4240, 1205));

		}

		else if (path == 4)
		{

		}
	}


	return waypoints;
	//cout << waypoints << endl;
}




sf::Vector2f Enemy::update(sf::Vector2f enemyPos)
{
	//enemyPos.x++;

	//m_wayPoints = getEnemyPath(1, 1, 1);
	
	//getEnemyPath(1, 1, 1);
	// ensures that movement we will only transition to the next waypoint once both the x and y parts of each waypoint have been reached
	if (yPath == true && xPath == true)
	{
		xPath = false;
		yPath = false;
		index++;
	}

	
	// outlines conditions for the position to adjust, in relation to the waypoint
	if (index < m_wayPoints->size() && alive == true)
	{
		/*if (left == true && up == true)
		{
			m_EnemySprite.setRotation(270);
		}
		if (left == true && down == true)
		{
			m_EnemySprite.setRotation(180);
		}
		if (right == true && up == true)
		{
			m_EnemySprite.setRotation(30);
		}
		if (right == true && down == true)
		{
			m_EnemySprite.setRotation(160);
		}*/

		if (index > 0)
		{
			if (m_wayPoints->at(index).x >= m_wayPoints->at(index - 1).x)
			{
				enemyDirection = Direction::Right;
			}
			else
			{
				enemyDirection = Direction::Left;
			}
		}
		


		if (enemyPos.x != m_wayPoints->at(index).x) // if the position isn't at the waypoint
		{
			if (enemyPos.x > m_wayPoints->at(index).x)  // if the position (for x) is greater than the waypoint going ->
			{
				enemyPos.x -= m_speed;  // then, the position will move left <-
				/*left = true;
				right = false;*/
				
			}

			if (enemyPos.x < m_wayPoints->at(index).x)  // if the position (for x) is less than the waypoint going <-
			{
				enemyPos.x += m_speed;  // then, the position will move right ->
				/*right = true;
				left = false;*/
			}
		}
		else
		{
			xPath = true;
		}

		if (enemyPos.y != m_wayPoints->at(index).y)
		{
			if (enemyPos.y > m_wayPoints->at(index).y)  // if the position (for x) is greater than the waypoint going ->
			{
				enemyPos.y -= m_speed;  // then, the position will move left <-
				/*up = true;
				down = false;*/
			}

			if (enemyPos.y < m_wayPoints->at(index).y)   // if the position (for x) is less than the waypoint going <-
			{
				enemyPos.y += m_speed;  // then, the position will move right ->
				/*down = true;
				up = false;*/
			}
		}
		else
		{
			yPath = true;
		}

		if (enemyPos.x > m_wayPoints->at(index).x - 10 && enemyPos.x < m_wayPoints->at(index).x + 10)
		{
			xPath = true;    // when the position for the x axis is reached (within a standard deviation of 1) for the waypoint, this bool is set to true
		}

		if (enemyPos.y > m_wayPoints->at(index).y + 10 && enemyPos.y < m_wayPoints->at(index).y + 10)
		{
			yPath = true;     // when the position for the y axis is reached (within a standard deviation of 1) for the waypoint, this bool is set to true
		}
	}

	if (index >= m_wayPoints->size())
	{
		index = 0;
	}
	return enemyPos;
}

void Enemy::Attack()
{
	if (enemyDirection == Direction::Right)
	{
		timer++;
		if (timer <= 7)
		{
			m_EnemySwingSource = IntRect(15, 30, 95, 150);
			m_EnemySwingSprite.setTextureRect(m_EnemySwingSource);
			m_EnemySwingSprite.setPosition(m_EnemySprite.getPosition());

			timer++;
		}
		else if (timer > 8 && timer <= 14)
		{
			m_EnemySwingSource = IntRect(160, 30, 140, 110);
			m_EnemySwingSprite.setTextureRect(m_EnemySwingSource);

			timer++;
		}
		else if (timer > 15 && timer <= 21)
		{
			m_EnemySwingSource = IntRect(300, 40, 150, 105);
			m_EnemySwingSprite.setTextureRect(m_EnemySwingSource);

			timer++;
		}
		else if (timer > 22 && timer <= 28)
		{
			m_EnemySwingSource = IntRect(460, 10, 140, 120);
			m_EnemySwingSprite.setTextureRect(m_EnemySwingSource);

			timer++;
		}
		else if (timer > 29 && timer <= 35)
		{
			m_EnemySwingSource = IntRect(620, 0, 100, 130);
			m_EnemySwingSprite.setTextureRect(m_EnemySwingSource);

			timer++;
		}
		else if (timer > 36 && timer <= 42)
		{
			m_EnemySwingSource = IntRect(750, 30, 150, 100);
			m_EnemySwingSprite.setTextureRect(m_EnemySwingSource);
			timer++;
		}
		else if (timer > 43 && timer <= 49)
		{
			enemySwing = false;
			timer = 0;
		}
	}

	else if (enemyDirection == Direction::Left)
	{
		timer++;
		if (timer <= 7)
		{
			m_EnemySwingSource = IntRect(790, 180, 90, 140);
			m_EnemySwingSprite.setTextureRect(m_EnemySwingSource);
			m_EnemySwingSprite.setPosition(m_EnemySprite.getPosition());

			timer++;
		}
		else if (timer > 8 && timer <= 14)
		{
			m_EnemySwingSource = IntRect(600, 200, 150, 130);
			m_EnemySwingSprite.setTextureRect(m_EnemySwingSource);

			timer++;
		}
		else if (timer > 15 && timer <= 21)
		{
			m_EnemySwingSource = IntRect(450, 220, 150, 125);
			m_EnemySwingSprite.setTextureRect(m_EnemySwingSource);

			timer++;
		}
		else if (timer > 22 && timer <= 28)
		{
			m_EnemySwingSource = IntRect(300, 220, 140, 120);
			m_EnemySwingSprite.setTextureRect(m_EnemySwingSource);

			timer++;
		}
		else if (timer > 29 && timer <= 35)
		{
			m_EnemySwingSource = IntRect(180, 220, 100, 130);
			m_EnemySwingSprite.setTextureRect(m_EnemySwingSource);

			timer++;
		}
		else if (timer > 36 && timer <= 42)
		{
			m_EnemySwingSource = IntRect(0, 210, 140, 105);
			m_EnemySwingSprite.setTextureRect(m_EnemySwingSource);
			timer++;
		}
		else if (timer > 43 && timer <= 49)
		{
			enemySwing = false;
			timer = 0;
		}
	}

	else if (enemyDirection == Direction::Down)
	{
		timer++;
		if (timer <= 7)
		{
			m_EnemySwingSource = IntRect(0, 370, 140, 100);
			m_EnemySwingSprite.setTextureRect(m_EnemySwingSource);
			m_EnemySwingSprite.setPosition(m_EnemySprite.getPosition());

			timer++;
		}
		else if (timer > 8 && timer <= 14)
		{
			m_EnemySwingSource = IntRect(160, 380, 135, 140);
			m_EnemySwingSprite.setTextureRect(m_EnemySwingSource);

			timer++;
		}
		else if (timer > 15 && timer <= 21)
		{
			m_EnemySwingSource = IntRect(330, 380, 115, 150);
			m_EnemySwingSprite.setTextureRect(m_EnemySwingSource);

			timer++;
		}
		else if (timer > 22 && timer <= 28)
		{
			m_EnemySwingSource = IntRect(470, 380, 130, 130);
			m_EnemySwingSprite.setTextureRect(m_EnemySwingSource);

			timer++;
		}
		else if (timer > 29 && timer <= 35)
		{
			m_EnemySwingSource = IntRect(620, 380, 135, 105);
			m_EnemySwingSprite.setTextureRect(m_EnemySwingSource);

			timer++;
		}
		else if (timer > 36 && timer <= 42)
		{
			m_EnemySwingSource = IntRect(780, 380, 110, 150);
			m_EnemySwingSprite.setTextureRect(m_EnemySwingSource);
			timer++;
		}
		else if (timer > 43 && timer <= 49)
		{
			enemySwing = false;
			timer = 0;
		}
	}

	else if (enemyDirection == Direction::Up)
	{
		timer++;
		if (timer <= 7)
		{
			m_EnemySwingSource = IntRect(750, 590, 150, 100);
			m_EnemySwingSprite.setTextureRect(m_EnemySwingSource);
			m_EnemySwingSprite.setPosition(m_EnemySprite.getPosition());

			timer++;
		}
		else if (timer > 8 && timer <= 14)
		{
			m_EnemySwingSource = IntRect(605, 540, 135, 140);
			m_EnemySwingSprite.setTextureRect(m_EnemySwingSource);

			timer++;
		}
		else if (timer > 15 && timer <= 21)
		{
			m_EnemySwingSource = IntRect(465, 540, 115, 140);
			m_EnemySwingSprite.setTextureRect(m_EnemySwingSource);

			timer++;
		}
		else if (timer > 22 && timer <= 28)
		{
			m_EnemySwingSource = IntRect(300, 540, 130, 140);
			m_EnemySwingSprite.setTextureRect(m_EnemySwingSource);

			timer++;
		}
		else if (timer > 29 && timer <= 35)
		{
			m_EnemySwingSource = IntRect(140, 590, 140, 100);
			m_EnemySwingSprite.setTextureRect(m_EnemySwingSource);

			timer++;
		}
		else if (timer > 36 && timer <= 42)
		{
			m_EnemySwingSource = IntRect(20, 535, 110, 150);
			m_EnemySwingSprite.setTextureRect(m_EnemySwingSource);
			timer++;
		}
		else if (timer > 43 && timer <= 49)
		{
			enemySwing = false;
			timer = 0;
		}
	}
}
