#include "Wall.h"

Wall::Wall()
{

}

Wall::Wall(sf::Vector2f position, float rotation)
{
	m_WallPosition = position;
	m_WallSource = IntRect(0, 0, 140, 13);
	m_WallSprite.setTextureRect(m_WallSource);
	m_WallSprite.setRotation(rotation);
	m_WallSprite.setPosition(m_WallPosition);

	if (rotation == 0)
	{
		rotated = false;
	}
	else if (rotation == 90)
	{
		rotated = true;
	}

	if (!m_WallTexture.loadFromFile("Sprites Folder/Wall.png"))
	{
		// error...
	}

	leftDisabled = false;
	rightDisabled = false;
	upDisabled = false;
	downDisabled = false;

};



Wall::~Wall()
{

}

void Wall::Load(Texture& _WallTexture)
{
	m_WallSprite.setTexture(m_WallTexture);
}

void Wall::draw(RenderWindow& _window)
{
	Load(m_WallTexture);
	//m_WallSprite.setTexture(m_WallTexture);
	_window.draw(m_WallSprite);
}

void Wall::collisionDetection(sf::Vector2f position, Player &player)
{
	//////// Bullet Collisions with Walls ///////////
	for (int i = 0; i < player.bullets.size(); i++)
	{
		if (player.bullets[i].getBulletSprite().getGlobalBounds().intersects(m_WallSprite.getGlobalBounds()))
		{
			player.bullets.erase(player.bullets.begin() + i);
		}
	}

	//////// Collisions between player + walls 
	if (rotated == false)
	{
		m_left = m_WallSprite.getPosition().x;
		m_right = m_WallSprite.getPosition().x + m_WallTexture.getSize().x;
		m_top = m_WallSprite.getPosition().y;
		m_bottom = m_WallSprite.getPosition().y + m_WallTexture.getSize().y;
	}
	
	// change variables for the rotated wall to ensure accurate detection
	if (rotated == true)
	{
		m_left = m_WallSprite.getPosition().x;
		m_right = m_WallSprite.getPosition().x + m_WallTexture.getSize().y;
		m_top = m_WallSprite.getPosition().y;
		m_bottom = m_WallSprite.getPosition().y + m_WallTexture.getSize().x;
	}

	playerSpeed = fabs(player.speed);

	//cout << "left" << m_left << "right" << m_right << endl;

	/*if ((player.m_left >= m_left && player.m_left >= m_right) ||
		(player.m_right >= m_left && player.m_right <= m_right))
	{
		if ((player.m_top >= m_top && player.m_top <= m_bottom) ||
			(player.m_bottom >= m_top && player.m_bottom <= m_bottom))

		{*/


	if (player.presentDirection == Direction::Left)
	{
		if (rightDisabled == true)
		{
			player.moving = true;
		}
	}

	if (player.presentDirection == Direction::Right)
	{
		if (leftDisabled == true)
		{
			player.moving = true;
		}
	}

	


	if (player.m_PlayerSprite.getGlobalBounds().intersects(m_WallSprite.getGlobalBounds()))
	{

			if (player.m_right -10 > m_left)
			{
				
				if (player.presentDirection == Direction::Right)
				{
					player.m_PlayerSprite.move(-playerSpeed * 2, -0);
					//player.moving = true;
				}
				
			
			}
				
	

			if (player.m_left  + 10 < m_right)
			{
				
				if (player.presentDirection == Direction::Left)
				{
					//player.moving = false;
					player.m_PlayerSprite.move(playerSpeed * 2, -0);

					
				}

				//if (player.presentDirection == Direction::Up || player.presentDirection == Direction::Down)
				//{
				//	//player.moving = false;
				//	//leftDisabled = true;
				//}
			}


			if (player.m_top  + 10< m_bottom)
			{
				if (player.presentDirection == Direction::Up)
				{
					//player.moving = false;
					player.m_PlayerSprite.move(0, playerSpeed * 2);
				}
				//else if (player.presentDirection == Direction::Left || player.presentDirection == Direction::Right)
				//{
				//	/*player.moving = false;
				//	upDisabled = true;*/
				//}
			}

			if (player.m_bottom - 10 > m_top)
			{
				if (player.presentDirection == Direction::Up)
				{
				
				}

				/*if (player.m_right - 10 > m_left)
				{
					if (player.presentDirection == Direction::Up)
					{
						player.m_PlayerSprite.move(-playerSpeed * 5, 0);
					}
				}*/

				/*else 
				{ */
					if (player.presentDirection == Direction::Down)
					{
						//player.moving = false;
						player.m_PlayerSprite.move(0, -playerSpeed * 2);
					}
					//else if (player.presentDirection == Direction::Left || player.presentDirection == Direction::Right)
					//{
					//	/*player.moving = false;
					//	downDisabled = true;*/

					//}
				//}

				/*else if (player.presentDirection == Direction::Right)
				{
					player.m_PlayerSprite.move(0, -0);
				}*/
			}


			

		}

	}
