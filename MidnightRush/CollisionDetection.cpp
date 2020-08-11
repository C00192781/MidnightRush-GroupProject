
#include "CollisionDetection.h"

CollisionDetection::CollisionDetection()
{

}

CollisionDetection::~CollisionDetection()
{

}


void CollisionDetection::Update(Player &player, EnemyManager &enemyManager, Weapon &weapon, LevelState &levelState, HostageManager &hostageManager, AudioManager &audio, Score &score, sf::Event &event, SoundScreen &sound)
{
	//cout << player.getSprite().getPosition().x << endl;
	
	Melee(player, enemyManager, audio,score, event, sound);
	PlayerDeath(player, enemyManager, audio, sound);

	BatPickUp(player, weapon, audio, sound);
	GunPickUp(player, weapon, audio, sound);
	LevelStateCollision(player, levelState, audio, sound);
	Hostage(player, enemyManager, hostageManager, audio, sound);

	
}

void CollisionDetection::Hostage(Player &player, EnemyManager &enemyManager, HostageManager &hostageManager, AudioManager &audio, SoundScreen &sound)
{
	for (int index = 0; index < hostageManager.hostageVector.size(); index++)
	{
		for (int i = 0; i < enemyManager.enemyVector.size(); i++)
		{
			if (player.saving == true)
			{
				//If the player picks up the hostage, the hostage will make a groan sound to indicate the pain they are in.
				audio.groan++;
				if (audio.groan == 2500)
				{
					audio.hostageGroan.play();
					audio.hostageGroan.setVolume(sound.soundValue);
					audio.groan = 0;
				}
				// If the player is holding a hostage and collides with the enemy
				if (player.getSavingSprite().getGlobalBounds().intersects(enemyManager.enemyVector.at(i)->getSprite().getGlobalBounds()))
				{
					if (enemyManager.enemyVector.at(i)->alive == true)
					{
						player.alive = false;
						player.saving = false;
						hostageManager.hostageVector.at(index)->alive = true;
						player.rifle = false;
						hostageManager.hostageVector.at(index)->m_HostageSprite.setPosition(player.m_PlayerSprite.getPosition());
					}
				}

			}



			// When the player moves over the hostage sprite they will pick them up and lose any weapon they were holding
			//collision.playerHostage();
			if (player.getSprite().getGlobalBounds().intersects(hostageManager.hostageVector.at(index)->getSprite().getGlobalBounds()) || player.getRifleSprite().getGlobalBounds().intersects(hostageManager.hostageVector.at(index)->getSprite().getGlobalBounds()))
			{
				//if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				//{
				if (player.alive == true)
				{
					player.saving = true;
					hostageManager.hostageVector.at(index)->alive = false;
					player.rifle = false;
					//std::cout << "Saving Hostage" << std::endl;
				}
				
			}
			

		}
	}
}

void CollisionDetection::PlayerDeath(Player &player, EnemyManager &enemyManager, AudioManager &audio, SoundScreen &sound)
{
	// COLLISION DETECTION between Player and Enemy
	// If the player and enemy collide the player dies, the music stops and the game ends

	for (int index = 0; index < enemyManager.enemyVector.size(); index++)
	{
		if ( (player.alive == true && player.getSprite().getGlobalBounds().intersects(enemyManager.enemyVector.at(index)->getSprite().getGlobalBounds()))
			
			|| (player.alive == false && player.rifle == true && player.getRifleSprite().getGlobalBounds().intersects(enemyManager.enemyVector.at(index)->getSprite().getGlobalBounds())) )
			{
				if (enemyManager.enemyVector.at(index)->alive == true)
				{
					//std::cout << "Collision" << std::endl;
					player.alive = false;
					player.rifle = false;

					/*cout << player.getSprite().getPosition().x << endl;
					cout << enemyManager.enemyVector.at(index)->getPosition().x << endl;*/
					audio.GameplayMusic.stop();
				}
			}
	}
}

void CollisionDetection::BatPickUp(Player &player, Weapon &weapon, AudioManager &audio, SoundScreen &sound)
{
	// If the player moves over the bat they will pick it up
	//collision.playerBat();
	if (player.getRifleSprite().getGlobalBounds().intersects(weapon.getBatSprite().getGlobalBounds()))
	{
		if (weapon.batAlive == true)
		{
			audio.batPickUp.play();
			audio.batPickUp.setVolume(sound.soundValue);
			player.rifle = false;
			weapon.batAlive = false;
		}
	}
}


void CollisionDetection::GunPickUp(Player &player, Weapon &weapon, AudioManager &audio, SoundScreen &sound)
{

	// If the player moves over the rifle they will pick it up
	//collision.playerRifle();
	if (player.getSprite().getGlobalBounds().intersects(weapon.getRifleSprite().getGlobalBounds()))
	{
		if (player.saving == false)
		{
			if (weapon.rifleAlive == true)
			{
				audio.riflePickUp.play();
				//audio.riflePickUp.setVolume(0);
				player.rifle = true;
				weapon.rifleAlive = false;
			}
		}

	}
}

void CollisionDetection::LevelStateCollision(Player &player, LevelState &levelState, AudioManager &audio, SoundScreen &sound)
{
	// If the player gets to a certain position with the hostage they will complete the level
	if (player.getSavingSprite().getGlobalBounds().intersects(levelState.getlevelGoalSprite().getGlobalBounds()))
	{
		//presentGameState = GameStates::Main;
		cout << "Door Collision" << endl;
		levelState.levelComplete = true;
		//cout << "LEVEL COMPLETE" << endl;
	}
}

/////code for KILLING ENEMIES (MELEE)////////////
/////Written by Kevin Boylan//////////////////////
/////Player Momentum will also increase
void CollisionDetection::Melee(Player &player, EnemyManager &enemyManager, AudioManager &audio, Score &score, sf::Event &event, SoundScreen &sound)
{
	for (int index = 0; index < enemyManager.enemyVector.size(); index++)
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Space:
				// if the player and enemy are alive, the player has the gun and we've pressed SPACE
				// If the player and enemy collide the player dies and the game ends

				if (player.rifle == false && player.saving == false && player.alive == true)
				{
					player.swing = true;
					audio.batSwing.play();
					audio.batSwing.setVolume(sound.soundValue);
				}
				switch (enemyManager.enemyVector.at(index)->alive) // if the enemy is alive
				{
				case true:

					switch (player.rifle) // if the rifle bool is false
					{
					case false:

						switch (player.alive) // if the player is alive
						{
						case true:


							// CONCERNS MELEE ATTACKS ON TOP + LEFT SIDES OF ENEMY
							if ((player.getSprite().getPosition().x <= enemyManager.enemyVector.at(index)->getSprite().getPosition().x) && ((enemyManager.enemyVector.at(index)->getSprite().getPosition().x - player.getSprite().getPosition().x) <= 200))
							{
								if (player.getSprite().getPosition().y <= enemyManager.enemyVector.at(index)->getSprite().getPosition().y)
								{
									if (((enemyManager.enemyVector.at(index)->getSprite().getPosition().y - player.getSprite().getPosition().y) <= 200)) //////////
																																						 //if (((enemy.getSprite().getPosition().y - player.getSprite().getPosition().y) <= 100) || ((enemy.getSprite().getPosition().y - player.getSprite().getPosition().y) >= -200))
									{
										//increase Player momentum 
										player.momentum += 4;
										// enemy dies
										enemyManager.enemyVector.at(index)->alive = false;
										audio.enemyDeath.play();
										audio.enemyDeath.setVolume(sound.soundValue);
										score.AddScore(100);
										break;
									}
								}
							}

							//  CONCERNS MELEE ATTACKS ON RIGHT SIDE OF ENEMY
							if ((player.getSprite().getPosition().x >= enemyManager.enemyVector.at(index)->getSprite().getPosition().x) && ((enemyManager.enemyVector.at(index)->getSprite().getPosition().x - player.getSprite().getPosition().x) >= -250))
							{
								if (player.getSprite().getPosition().y >= enemyManager.enemyVector.at(index)->getSprite().getPosition().y)
								{
									if (((enemyManager.enemyVector.at(index)->getSprite().getPosition().y - player.getSprite().getPosition().y) >= -250))
									{
										//increase Player momentum 
										player.momentum += 4;
										// enemy dies
										enemyManager.enemyVector.at(index)->alive = false;
										audio.enemyDeath.play();
										audio.enemyDeath.setVolume(sound.soundValue);
										score.AddScore(100);
										break;
									}
								}
							}

							//  CONCERNS MELEE ATTACKS ON BOTTOM OF ENEMY
							if ((player.getSprite().getPosition().x <= enemyManager.enemyVector.at(index)->getSprite().getPosition().x) && ((enemyManager.enemyVector.at(index)->getSprite().getPosition().x - player.getSprite().getPosition().x) <= 200))
							{
								if (player.getSprite().getPosition().y >= enemyManager.enemyVector.at(index)->getSprite().getPosition().y)
								{
									if (((enemyManager.enemyVector.at(index)->getSprite().getPosition().y - player.getSprite().getPosition().y) >= -200)) //////////
																																						  //if (((enemy.getSprite().getPosition().y - player.getSprite().getPosition().y) <= 100) || ((enemy.getSprite().getPosition().y - player.getSprite().getPosition().y) >= -200))
									{
										//increase Player momentum 
										player.momentum += 4;
										// enemy dies
										enemyManager.enemyVector.at(index)->alive = false;
										audio.enemyDeath.play();
										audio.enemyDeath.setVolume(sound.soundValue);
										score.AddScore(100);
										break;
									}
								}
							}
							break;
						}
						break;
					}
					break;
				}
				break;

			}
			break;

		}
	}
}
