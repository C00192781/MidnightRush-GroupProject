#include "Player.h"

Player::Player()
{
	//Player Alive walking around
	m_PlayerSource = IntRect(0, 45, 150, 95);
	m_PlayerSprite.setTextureRect(m_PlayerSource);
	/*m_PlayerSprite.setPosition(-850, 2700);*/
	m_PlayerSprite.setPosition(2300, 2700);

	if (!m_PlayerTexture.loadFromFile("Sprites Folder/playersheet.png"))
	{
		// error...
	}

	//Player Death Sprite
	m_DeathSource = IntRect(0, 0, 180, 180);
	m_DeathSprite.setTextureRect(m_DeathSource);

	if (!m_DeathTexture.loadFromFile("Sprites Folder/player_death_sheet.png"))
	{
		// error...
	}

	//Player Saving Sprite
	m_SavingSource = IntRect(0, 0, 250, 250);
	m_SavingSprite.setTextureRect(m_SavingSource);

	if (!m_SavingTexture.loadFromFile("Sprites Folder/playerSaving_sheet.png"))
	{
		// error...
	}

	//Player holding a rifle
	m_PlayerRifleSource = IntRect(175, 0, 110, 150);
	m_PlayerRifleSprite.setTextureRect(m_PlayerRifleSource);
	m_PlayerRifleSprite.setPosition(m_PlayerSprite.getPosition());

	if (!m_PlayerRifleTexture.loadFromFile("Sprites Folder/player_assault_sheet.png"))
	{
		// error...
	}

	//Player holding a rifle
	m_PlayerSwingSource = IntRect(30, 0, 80, 140);
	m_PlayerSwingSprite.setTextureRect(m_PlayerSwingSource);
	m_PlayerSwingSprite.setPosition(m_PlayerSprite.getPosition());

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//Swinging Textures
	////////////////////////////////////////////////////////////////////////////////////////////////
	if (!m_PlayerSwingTexture.loadFromFile("Sprites Folder/playerSwing.png"))
	{
			// error...
	}


	momentum = 0;
	count = 0;

	bullets.reserve(64);
	std::vector<Bullet>::iterator iter = bullets.begin();

	xP = false;
	yPush = false;


	moving = true;
}


Player::~Player()
{
}

void Player::Load(Texture&, Texture&)
{
	if (alive == true && saving == false && rifle == false && swing == false)
	{
		m_PlayerSprite.setTexture(m_PlayerTexture);
	}
	else if (alive == false && saving == false && rifle == false && swing == false)
	{
		m_DeathSprite.setTexture(m_DeathTexture);
	}
	else if (alive == true && saving == true && rifle == false && swing == false)
	{
		m_SavingSprite.setTexture(m_SavingTexture);
	}
	else if (alive == true && saving == false && rifle == true && swing == false)
	{
		m_PlayerRifleSprite.setTexture(m_PlayerRifleTexture);
		m_PlayerRifleSprite.setPosition(m_PlayerSprite.getPosition());
	}
	else if (alive == true && saving == false && rifle == false && swing == true)
	{
		m_PlayerSwingSprite.setTexture(m_PlayerSwingTexture);
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].getBulletAlive() == true)
		{
			bullets[i].Load(*&bullets[i].getBulletTexture());
		}
	}
}

void Player::draw(RenderWindow& _window)
{
	if (alive == true && saving == false && rifle == false && swing == false)
	{
		_window.draw(m_PlayerSprite);
	}
	else if (alive == false && saving == false && rifle == false && swing == false)
	{
		_window.draw(m_DeathSprite);
	}
	else if (alive == true && saving == true && rifle == false && swing == false)
	{
		_window.draw(m_SavingSprite);
	}
	else if (alive == true && saving == false && rifle == true && swing == false)
	{
		_window.draw(m_PlayerRifleSprite);
	}
	if (alive == true && saving == false && rifle == false && swing == true)
	{
		_window.draw(m_PlayerSwingSprite);
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].getBulletAlive() == true)
		{
			bullets[i].draw(_window);
		}
	}
}

void Player::Update()
{
	
	m_left = m_PlayerSprite.getPosition().x;
	m_right = m_PlayerSprite.getPosition().x + m_PlayerTexture.getSize().x;
	m_top = m_PlayerSprite.getPosition().y;
	m_bottom = m_PlayerSprite.getPosition().y + m_PlayerTexture.getSize().y;
	if (alive == true && saving == false && rifle == false && swing == false)
	{
		Move();
	}
	else if (alive == false && saving == false && rifle == false && swing == false)
	{
		Death();
	}
	else if (alive == true && saving == true && rifle == false && swing == false)
	{
		Saving();
	}
	else if (alive == true && saving == false && rifle == true && swing == false)
	{
		Rifle();
	}
	else if (alive == true && saving == false && rifle == false && swing == true)
	{
		SwingAnimation();
	}
	ResetMomentum();
	

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].getBulletAlive() == true)
		{
			bullets[i].Update();
		}
	}
	
}

//Player moves with the arrow keys in any direction
void Player::Move()
{
	//cout << "moving " << moving << endl;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		// decrease speed by the momentum (appropriate for the up direction)
		speed = -15 - momentum;
		m_PlayerSource = IntRect(0, 45, 150, 95);
		m_PlayerSource.left = 0;
		if (moving == true)
		{
			m_PlayerSprite.move(0, speed);
		}
		m_PlayerSprite.setTextureRect(m_PlayerSource);

		presentDirection = Direction::Up;   // FOR MOVING UP
		bulletDirection = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		// increase speed by the momentum
		speed = 15 + momentum;
		m_PlayerSource = IntRect(0, 45, 150, 95);
		m_PlayerSource.left = 150;
		if (moving == true)
		{
			m_PlayerSprite.move(0, speed);
		}
		m_PlayerSprite.setTextureRect(m_PlayerSource);

		presentDirection = Direction::Down;   // FOR MOVING DOWN
		bulletDirection = 2;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		// decrease speed by the momentum (appropriate for the left direction)
		speed = -15 - momentum;
		m_PlayerSource = IntRect(0, 0, 95, 150);
		m_PlayerSource.left = 450;
		if (moving == true)
		{
			m_PlayerSprite.move(speed, 0);
		}
		m_PlayerSprite.setTextureRect(m_PlayerSource);

		presentDirection = Direction::Left;   // FOR MOVING LEFT
		bulletDirection = 3;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		// increase speed by the momentum
		speed = 15 + momentum;
		m_PlayerSource = IntRect(0, 0, 95, 150);
		m_PlayerSource.left = 300;
		if (moving == true)
		{
			m_PlayerSprite.move(speed, 0);
		}
		m_PlayerSprite.setTextureRect(m_PlayerSource);

		presentDirection = Direction::Right;  // FOR MOVING RIGHT
		bulletDirection = 4;
	}
	//cout << "Speed: " << speed << std::endl;
}






void Player::ResetMomentum()
{
	// Momentum is dependent on killing enemies
	// The momentum will reset a certain amount of time after an enemy has been killed 
	// Note: will use sfml to work out approximate time later
	if (momentum > 0)
	{
		count++;
	}
	if (count >= 200)
	{
		count = 0;
		momentum = 0;
	}
	//std::cout << count << std::endl;
}


//Called when the player dies resulting in the player appearing on the floor dead
void Player::Death()
{
	if (presentDirection == Direction::Down)//Facing Up
	{
		m_DeathSource.left = 0;
		m_DeathSprite.setTextureRect(m_DeathSource);
		//When the player dies they die in the same position they were standimg
		m_DeathSprite.setPosition(m_PlayerSprite.getPosition()); 
	}
	else if (presentDirection == Direction::Left)//Facing Right
	{
		m_DeathSource.left = 180;
		m_DeathSprite.setTextureRect(m_DeathSource);
		m_DeathSprite.setPosition(m_PlayerSprite.getPosition());
	}
	else if (presentDirection == Direction::Up)//Facing Down
	{
		m_DeathSource.left = 360;
		m_DeathSprite.setTextureRect(m_DeathSource);
		m_DeathSprite.setPosition(m_PlayerSprite.getPosition());
	}
	else if (presentDirection == Direction::Right)//Facing Left
	{
		m_DeathSource.left = 540;
		m_DeathSprite.setTextureRect(m_DeathSource);
		m_DeathSprite.setPosition(m_PlayerSprite.getPosition());
	}
	
}

void Player::Saving()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		speed = -12 - momentum;
		if (moving == true)
		{
			m_PlayerSprite.move(0, speed);
		}

		m_SavingSource.left = 500;
		m_SavingSprite.setTextureRect(m_SavingSource);
		m_SavingSprite.setPosition(m_PlayerSprite.getPosition());

		presentDirection = Direction::Up;
		bulletDirection = 1;

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		speed = 12 + momentum;
		if (moving == true)
		{
			m_PlayerSprite.move(0, speed);
		}

		m_SavingSource.left = 750;
		m_SavingSprite.setTextureRect(m_SavingSource);
		m_SavingSprite.setPosition(m_PlayerSprite.getPosition());

		presentDirection = Direction::Down;
		bulletDirection = 2;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		speed = -12 - momentum;

		if (moving == true)
		{
			m_PlayerSprite.move(speed, 0);
		}

		
		m_SavingSource.left = 250;
		m_SavingSprite.setTextureRect(m_SavingSource);
		m_SavingSprite.setPosition(m_PlayerSprite.getPosition());

		presentDirection = Direction::Left;
		bulletDirection = 3;
	}
	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		speed = 12 + momentum;
		if (moving == true)
		{
			m_PlayerSprite.move(speed, 0);
		}

		m_SavingSource.left = 0;
		m_SavingSprite.setTextureRect(m_SavingSource);
		//When the player dies they die in the same position they were standimg
		m_SavingSprite.setPosition(m_PlayerSprite.getPosition());

		presentDirection = Direction::Right;
		bulletDirection = 4;
	}
}


void Player::Rifle()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		// decrease speed by the momentum (appropriate for the up direction)
		speed = -15 - momentum;
		m_PlayerSprite.move(0, speed);
		
		m_PlayerRifleSource = IntRect(20, 0, 110, 150);
		m_PlayerRifleSource.left = 0;
		m_PlayerRifleSprite.setTextureRect(m_PlayerRifleSource);
		//m_PlayerRifleSprite.setPosition(m_PlayerSprite.getPosition());

		presentDirection = Direction::Up;
		bulletDirection = 1;

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		// increase speed by the momentum
		speed = 15 + momentum ;
		m_PlayerSprite.move(0, speed);

		m_PlayerRifleSource = IntRect(175, 0, 110, 150);
		m_PlayerRifleSource.left = 175;

		m_PlayerRifleSprite.setTextureRect(m_PlayerRifleSource);

		presentDirection = Direction::Down;
		bulletDirection = 2;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		// decrease speed by the momentum (appropriate for the left direction)
		speed = -15 - momentum;
		m_PlayerSprite.move(speed, 0);

		m_PlayerRifleSource = IntRect(300, 20, 150, 110);
		m_PlayerRifleSource.left = 300;

		m_PlayerRifleSprite.setTextureRect(m_PlayerRifleSource);

		presentDirection = Direction::Left;
		bulletDirection = 3;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		// increase speed by the momentum
		speed = 15 + momentum;
		m_PlayerSprite.move(speed, 0);

		m_PlayerRifleSource = IntRect(450, 20, 150, 110);
		m_PlayerRifleSource.left = 450;

		m_PlayerRifleSprite.setTextureRect(m_PlayerRifleSource);

		presentDirection = Direction::Right;
		bulletDirection = 4;
	}
	//cout << "Speed: " << speed << std::endl;
}


//////////////////////////////////////////
// used to allow the player to shoot bullets
/////////////////////////////////////////
void Player::Shoot()
{
	Bullet newBullet;
	// set the new bullet to being alive
	newBullet.setBulletAlive(true);
	// and set the new bullet's direction
	newBullet.setBulletDirection(bulletDirection);
	newBullet.Update();
	// push the new bullet to the back of the vector
	bullets.push_back(newBullet);

	// FOR SHOOTING UP
	if (presentDirection == Direction::Up)
	{
		//Set Bullet position to player's, with an offset
		offSetX = 78;
		bullets.back().setBulletPosition(Vector2f(m_PlayerSprite.getPosition().x + offSetX, m_PlayerSprite.getPosition().y));
	}
	// FOR SHOOTING DOWN
	else if (presentDirection == Direction::Down)
	{
		//Set Bullet position to player's
		offSetX = 50;
		OffSetY = 150;
		bullets.back().setBulletRotation(180.0f);
		bullets.back().setBulletPosition(Vector2f(m_PlayerSprite.getPosition().x + offSetX, m_PlayerSprite.getPosition().y + OffSetY));
	}
	// FOR SHOOTING LEFT
	else if (presentDirection == Direction::Left)
	{
		//Set Bullet position to player's
		OffSetY = 55;
		bullets.back().setBulletRotation(-90.0f);
		bullets.back().setBulletPosition(Vector2f(m_PlayerSprite.getPosition().x, m_PlayerSprite.getPosition().y + OffSetY));
	}
	// FOR SHOOTING RIGHT
	else if (presentDirection == Direction::Right)
	{
		//Set Bullet position to player's
		offSetX = 150;
		OffSetY = 55;
		bullets.back().setBulletRotation(90.0f);
		bullets.back().setBulletPosition(Vector2f(m_PlayerSprite.getPosition().x + offSetX, m_PlayerSprite.getPosition().y + OffSetY));
	}
}

// This method handles bullet collisions between the player's bullets and the enemy.
// Additionally, if handles what happens when a bullet goes out of the set boundaries
void Player::BulletCollisions(std::vector<shared_ptr<Enemy>> &enemyVector)
{
	for (int index = 0; index < enemyVector.size(); index++)
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			// when the bullet goes out of the bounds we have defined
			if (bullets[i].getBulletSprite().getPosition().x > 9000 || bullets[i].getBulletSprite().getPosition().x < 0
				|| bullets[i].getBulletSprite().getPosition().y > 6000 || bullets[i].getBulletSprite().getPosition().y < -900)
			{
				// we erase these bullets
				bullets.erase(bullets.begin() + i);
			}
			// if the enemy still has health
			else if (enemyVector.at(index)->m_EnemyHealth > 0)
			{
				if (bullets[i].getBulletSprite().getGlobalBounds().intersects(enemyVector.at(index)->getSprite().getGlobalBounds()))
				{
					// we erase these bullets
					bullets.erase(bullets.begin() + i);
					enemyVector.at(index)->m_EnemyHealth -= 10;
				}
			}

			// when the enemy has no health left
			else if (enemyVector.at(index)->m_EnemyHealth <= 0)
			{
				enemyVector.at(index)->enemyLife = false;
			}
		}
	}
}


//If the player is holding the bat and presses the space bar they will swing the bat
void Player::SwingAnimation()
{
	if (presentDirection == Direction::Right)
	{
		timer++;
		if (timer <= 7)
		{
			m_PlayerSwingSource = IntRect(25, 40, 90, 145);
			m_PlayerSwingSprite.setTextureRect(m_PlayerSwingSource);
			m_PlayerSwingSprite.setPosition(m_PlayerSprite.getPosition());
			
			timer++;
		}
		else if (timer > 8 && timer <= 14)
		{
			m_PlayerSwingSource = IntRect(150, 45, 145, 135);
			m_PlayerSwingSprite.setTextureRect(m_PlayerSwingSource);

			timer++;
		}
		else if (timer > 15 && timer <= 21)
		{
			m_PlayerSwingSource = IntRect(300, 40, 150, 105);
			m_PlayerSwingSprite.setTextureRect(m_PlayerSwingSource);

			timer++;
		}
		else if (timer > 22 && timer <= 28)
		{
			m_PlayerSwingSource = IntRect(460, 5, 140, 135);
			m_PlayerSwingSprite.setTextureRect(m_PlayerSwingSource);

			timer++;
		}
		else if (timer > 29 && timer <= 35)
		{
			m_PlayerSwingSource = IntRect(620, 0, 100, 145);
			m_PlayerSwingSprite.setTextureRect(m_PlayerSwingSource);

			timer++;
		}
		else if (timer > 36 && timer <= 42)
		{
			m_PlayerSwingSource = IntRect(755, 40, 145, 105);
			m_PlayerSwingSprite.setTextureRect(m_PlayerSwingSource);
			timer++;
		}
		else if (timer > 43 && timer <= 49)
		{
			swing = false;
			timer = 0;
		}
	}
	else if (presentDirection == Direction::Left)
	{
		timer++;
		if (timer <= 7)
		{
			m_PlayerSwingSource = IntRect(25, 190, 90, 150);
			m_PlayerSwingSprite.setTextureRect(m_PlayerSwingSource);
			m_PlayerSwingSprite.setPosition(m_PlayerSprite.getPosition());

			timer++;
		}
		else if (timer > 8 && timer <= 14)
		{
			m_PlayerSwingSource = IntRect(150, 200, 145, 135);
			m_PlayerSwingSprite.setTextureRect(m_PlayerSwingSource);

			timer++;
		}
		else if (timer > 15 && timer <= 21)
		{
			m_PlayerSwingSource = IntRect(300, 230, 150, 135);
			m_PlayerSwingSprite.setTextureRect(m_PlayerSwingSource);

			timer++;
		}
		else if (timer > 22 && timer <= 28)
		{
			m_PlayerSwingSource = IntRect(450, 230, 145, 135);
			m_PlayerSwingSprite.setTextureRect(m_PlayerSwingSource);

			timer++;
		}
		else if (timer > 29 && timer <= 35)
		{
			m_PlayerSwingSource = IntRect(635, 230, 90, 150);
			m_PlayerSwingSprite.setTextureRect(m_PlayerSwingSource);

			timer++;
		}
		else if (timer > 36 && timer <= 42)
		{
			m_PlayerSwingSource = IntRect(755, 230, 145, 105);
			m_PlayerSwingSprite.setTextureRect(m_PlayerSwingSource);

			timer++;
		}
		else if (timer > 43 && timer <= 49)
		{
			swing = false;
			timer = 0;
		}
	}
	else if (presentDirection == Direction::Down)
	{
		timer++;
		if (timer <= 7)
		{
			m_PlayerSwingSource = IntRect(0, 390, 145, 90);
			m_PlayerSwingSprite.setTextureRect(m_PlayerSwingSource);
			m_PlayerSwingSprite.setPosition(m_PlayerSprite.getPosition());

			timer++;
		}
		else if (timer > 8 && timer <= 14)
		{
			m_PlayerSwingSource = IntRect(160, 390, 135, 140);
			m_PlayerSwingSprite.setTextureRect(m_PlayerSwingSource);

			timer++;
		}
		else if (timer > 15 && timer <= 21)
		{
			m_PlayerSwingSource = IntRect(325, 385, 110, 145);
			m_PlayerSwingSprite.setTextureRect(m_PlayerSwingSource);

			timer++;
		}
		else if (timer > 22 && timer <= 28)
		{
			m_PlayerSwingSource = IntRect(465, 390, 135, 140);
			m_PlayerSwingSprite.setTextureRect(m_PlayerSwingSource);

			timer++;
		}
		else if (timer > 29 && timer <= 35)
		{
			m_PlayerSwingSource = IntRect(600, 390, 150, 95);
			m_PlayerSwingSprite.setTextureRect(m_PlayerSwingSource);

			timer++;
		}
		else if (timer > 36 && timer <= 42)
		{
			m_PlayerSwingSource = IntRect(770, 390, 110, 145);
			m_PlayerSwingSprite.setTextureRect(m_PlayerSwingSource);

			timer++;
		}
		else if (timer > 43 && timer <= 49)
		{
			swing = false;
			timer = 0;
		}
	}
	else if (presentDirection == Direction::Up)
	{
		timer++;
		if (timer <= 7)
		{
			m_PlayerSwingSource = IntRect(0, 595, 150, 85);
			m_PlayerSwingSprite.setTextureRect(m_PlayerSwingSource);
			m_PlayerSwingSprite.setPosition(m_PlayerSprite.getPosition());

			timer++;
		}
		else if (timer > 8 && timer <= 14)
		{
			m_PlayerSwingSource = IntRect(160, 540, 135, 140);
			m_PlayerSwingSprite.setTextureRect(m_PlayerSwingSource);

			timer++;
		}
		else if (timer > 15 && timer <= 21)
		{
			m_PlayerSwingSource = IntRect(315, 540, 105, 140);
			m_PlayerSwingSprite.setTextureRect(m_PlayerSwingSource);

			timer++;
		}
		else if (timer > 22 && timer <= 28)
		{
			m_PlayerSwingSource = IntRect(450, 535, 130, 145);
			m_PlayerSwingSprite.setTextureRect(m_PlayerSwingSource);

			timer++;
		}
		else if (timer > 29 && timer <= 35)
		{
			m_PlayerSwingSource = IntRect(600, 590, 150, 90);
			m_PlayerSwingSprite.setTextureRect(m_PlayerSwingSource);

			timer++;
		}
		else if (timer > 36 && timer <= 42)
		{
			m_PlayerSwingSource = IntRect(765, 540, 110, 140);
			m_PlayerSwingSprite.setTextureRect(m_PlayerSwingSource);

			timer++;
		}
		else if (timer > 43 && timer <= 49)
		{
			swing = false;
			timer = 0;
		}
	}

}

