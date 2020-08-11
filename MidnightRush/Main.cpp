#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Background.h"
#include "AudioManager.h"

#include "Menu.h"
#include "GameState.h"
#include "Options.h"
#include "LicenceScreen.h"
#include "SplashScreen.h"
#include "LevelState.h"
#include "HelpScreen.h"
#include "GameOverScreen.h"
#include "SoundScreen.h"
#include "Winner.h"

#include "Enemy.h"
//#include "Player.h"
#include "Hostage.h"
#include "Weapon.h"

#include "Bullet.h"
#include "Pause.h"

#include "Score.h"

#include "LoadScreen.h"


#include <iostream>
#include <memory>
#include <stdio.h> 

#include "CollisionDetection.h"

//
//#include "Wall.h"
//#include "Floor.h"

#include "WallManager.h"


#define screenWidth 1980
#define screenHeight 1080 

int main()
{
	// sets the size of the window
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Midnight Rush!!!");
	// finds the size of the x and y axis for the following:
	// MAIN MENU, OPTIONS MENU, PAUSE MENU, SPASHSCREEN, LICENCESCREEN, etc
	Menu menu(window.getSize().x, window.getSize().y);
	Options options(window.getSize().x, window.getSize().y); // finds the size of the x and y axis
	Pause pause(window.getSize().x, window.getSize().y); // finds the size of the x and y axis
	SplashScreen splash(window.getSize().x, window.getSize().y);
	LicenceScreen licence(window.getSize().x, window.getSize().y);
	HelpScreen helpScreen(window.getSize().x, window.getSize().y);
	GameOverScreen gameOverScreen(window.getSize().x, window.getSize().y);
	Score score(window.getSize().x, window.getSize().y);
	LoadScreen loadScreen(window.getSize().x, window.getSize().y);
	SoundScreen soundScreen(window.getSize().x, window.getSize().y);
	WinnerScreen winnerScreen(window.getSize().x, window.getSize().y);

	LevelState levelState;
	AudioManager audio;

	sf::Event event;

	window.setFramerateLimit(60);  // sets the framerate limit at 60FPS
	float timer = 0;  // this timer is for allowing the player to go through the menus when holding down the button
					  // at a reasonabe pace

	float licenceTimer = 0.0f; //sets up a timer for how long the licence screen will be shown
	float splashTimer = 0.0f;
	float gameOverTimer = 0.0f;
	float groan = 0.0f;
	float gameStartCount = 0.0f;
	bool gameStart = false;
	bool reset = false;
	float shootDeathTimer = 0;

	float enemySwingWait = 0.0f;

	// the initial game state
	GameStates presentGameState = GameStates::LicenceScreen;

	Background background;

	Player & player = background.getPlayer();
	Texture playerTexture;

	Enemy enemy;
	Texture enemyTexture;

	Texture tickTexture;


	EnemyManager enemyManager;

	//Hostage hostage;
	//Texture hostageTexture;

	//Weapon weapon;
	Texture weaponTexture;


	//WallManager wallManager;

	//CollisionDetection collisionDetection;
	

	/*sf::Sprite * pPlayerSprite;
	*pPlayerSprite = player.getSprite();*/

	/*Wall wall;
	Texture wallTexture;*/

	//Score score;


	// Viewport Code
	// Written by Kevin Boylan
	// More code for this throughout Main.cpp
	float playerX = 0;
	float playerY = 0;
	sf::View view1 = window.getDefaultView();
	//view1.zoom(0.75);

	int collisionCount = 0;
	// time before another bullet can be shot
	int bulletTimer = 20;


	while (window.isOpen())
	{
		// makes sure that the timer is always increasing 
		timer++;
		// LICENCE SCREEN - code for if the LicenceScreen is the present game state
		if (GameStates::LicenceScreen == presentGameState)
		{
			licenceTimer++;

			if (licenceTimer >= 300)
			{
				presentGameState = GameStates::SplashScreen;
			}
			audio.splashMusic.play();
			audio.splashMusic.setVolume(soundScreen.soundValue);
			licence.draw(window); // Draws the licence screen 
		}


		if (window.pollEvent(event))
		{
			// SPLASH SCREEN - code for if the SplashScreen is the present game state
			if (GameStates::SplashScreen == presentGameState)
			{
				if (event.type == Event::Closed)
				{
					window.close();
				}
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
						// When the space bar is pressed the screen changes
					case sf::Keyboard::Return:
						presentGameState = GameStates::Main;
						break;
					}
					break;
				case sf::Event::Closed:
					window.close();

					break;
				}
			}

			else if (GameStates::Play == presentGameState)
			{
				// Code for pausing the game
				// You press the ESCAPE Key and the GameState will change to PAUSE
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Escape:
						presentGameState = GameStates::Pause;
						audio.pausePress.play();
						audio.pausePress.setVolume(soundScreen.soundValue);
						audio.GameplayMusic.pause();
						break;
					}
				}

			}



			else if (presentGameState == GameStates::GameOver)
			{
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
						// When the Return button is pressed you return to main menu
					case sf::Keyboard::Return:
						presentGameState = GameStates::Main;
						reset = true;
						background.getWeapon().batAlive = true;
						break;
					case sf::Keyboard::R:
						presentGameState = GameStates::Play;
						reset = true;
						audio.GameplayMusic.play();
						audio.GameplayMusic.setLoop(true);
						audio.GameplayMusic.setVolume(soundScreen.soundValue);
						break;
					}
					break;
				case sf::Event::Closed:
					window.close();

					break;
				}
			}

			else if (presentGameState == GameStates::Pause)
			{
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
						//coming out of pause menu
					case sf::Keyboard::Escape:
						presentGameState = GameStates::Play;
						audio.pausePress.play();
						audio.pausePress.setVolume(soundScreen.soundValue);
						audio.GameplayMusic.play();
						audio.GameplayMusic.setVolume(soundScreen.soundValue);
						break;
					}
				}
			}
		}


		// MAIN MENU - code for if the Main Menu is the present game state
		if (GameStates::Main == presentGameState)
		{
			if (timer > 15)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				{
					if (menu.buttonIndex == 0)
					{

						audio.gameStart.play(); /////////////////AUDIO FOR STARTING THE GAME//////////FINISH LATER/////////////////
												//cout << gameStartCount << endl;
						presentGameState = GameStates::Load;
						timer = 0; // resets timer to 0
						audio.gameStart.setVolume(soundScreen.soundValue);
						audio.splashMusic.stop();
						// the music will play once the gameplay begin
						//audio.GameplayMusic.play();
						//audio.GameplayMusic.setLoop(true);
					}
					else if (menu.buttonIndex == 1)
					{
						presentGameState = GameStates::Options;
						options.optionsReturn = true;
						options.Reset();
						timer = 0; // resets timer to 0
					}
					else if (menu.buttonIndex == 2)
					{
						// stops the music
						audio.GameplayMusic.stop();
						// closes the window, as this is  for the "Quit" button
						window.close();
						timer = 0; // resets timer to 0
					}
					// clears the window, as we'll be moving to a new game state
					window.clear();
				}

				// if we press UP on the keyboard
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					// calls the Up() method
					menu.Up();
					timer = 0; // resets timer to 0
					audio.menuScroll.play();
					audio.menuScroll.setVolume(soundScreen.soundValue / 2);
				}
				// if we press DOWN on the keyboard
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					menu.Down();
					timer = 0; // resets timer to 0
					audio.menuScroll.play();
					audio.menuScroll.setVolume(soundScreen.soundValue / 2);
				}
			}
		}

		// OPTIONS - code for if Options is the present GameState
		if (GameStates::Options == presentGameState)
		{
			if (timer > 15)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				{
					//Sound
					if (options.optionsIndex == 0)
					{
						timer = 0;
						presentGameState = GameStates::Sound;
						soundScreen.Reset();
						audio.splashMusic.stop();
					}
					//Help
					else if (options.optionsIndex == 1)
					{
						timer = 0;
						presentGameState = GameStates::Help;
					}
					//Return to Main
					else if (options.optionsIndex == 2)
					{
						timer = 0;
						if (options.optionsReturn == true) //////////////////
						{
							presentGameState = GameStates::Main;
						}
						else
						{
							presentGameState = GameStates::Pause;
						}
					}
				}

				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					// calls the Up() method
					options.Up();
					timer = 0;
					audio.menuScroll.play();
					audio.menuScroll.setVolume(soundScreen.soundValue / 2);
				}

				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					// calls the Down() method
					options.Down();
					timer = 0;
					audio.menuScroll.play();
					audio.menuScroll.setVolume(soundScreen.soundValue / 2);
				}
			}
		}

		// Sound - code for if Sound is the present GameState
		if (GameStates::Sound == presentGameState)
		{
			if (soundScreen.soundValue >= 100)
			{
				soundScreen.soundValue = 100;
			}
			else if (soundScreen.soundValue <= 0)
			{
				soundScreen.soundValue = 0;
				soundScreen.setSound == false;
			}
			if (timer > 15)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				{
					if (soundScreen.soundIndex == 0)
					{
						timer = 0;
					}
					else if (soundScreen.soundIndex == 1)
					{
						timer = 0;
					}
					else if (soundScreen.soundIndex == 2)
					{
						presentGameState = GameStates::Options;
						audio.splashMusic.play();
						audio.splashMusic.setVolume(soundScreen.soundValue);
						timer = 0;
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					// calls the Up() method
					soundScreen.Up();
					timer = 0;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					// calls the Down() method
					soundScreen.Down();
					timer = 0;
				}

				if (soundScreen.soundIndex == 0)
				{
					timer = 0;
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					{
						soundScreen.onOff();
						//timer = 0;
					}
				}
				if (soundScreen.soundIndex == 1)
				{
					soundScreen.moveSound();
				}
			}
		}

		// HELP - if the present game state is Help, we will draw the help menu
		if (GameStates::Help == presentGameState)
		{

			if (timer > 15)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				{
					presentGameState = GameStates::Options;
					timer = 0;
				}
				helpScreen.draw(window);
			}
		}

		if (GameStates::Load == presentGameState)
		{
			loadScreen.ChangePercent();
			if (loadScreen.m_size == 1.0f)
			{
				audio.GameplayMusic.play();
				audio.GameplayMusic.setLoop(true);
				audio.GameplayMusic.setVolume(soundScreen.soundValue);
				presentGameState = GameStates::Play;
			}
			loadScreen.draw(window);
		}


		// PLAY - code for if Play is the current GameState
		// gamestate for gameplay and what will occur during that state
		else if (GameStates::Play == presentGameState)
		{
			audio.splashMusic.stop();
			
			
			

				if (player.rifle == true)
				{
					bulletTimer++;
					//cout << "bullet timer " << shootDeathTimer << endl;
					if (bulletTimer >= 10)
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
						{
							for (int i = 0; i < player.bullets.size(); i++)
							{
								bulletTimer = 0;
								bulletTimer++;
								audio.rifleShoot.play();
								audio.rifleShoot.setVolume(soundScreen.soundValue);
							}
							player.Shoot();
						}
					}
					for (int index = 0; index < background.getEnemyManager().enemyVector.size(); index++)
					{
					
						if (background.getEnemyManager().enemyVector.at(index)->enemyLife == true)
						{
							background.getEnemyManager().enemyVector.at(index)->shootDeathTimer = 0;
						}
						else if (background.getEnemyManager().enemyVector.at(index)->enemyLife == false)
						{

							background.getEnemyManager().enemyVector.at(index)->alive = false;
							background.getEnemyManager().enemyVector.at(index)->shootDeathTimer++;
							//player.momentum += 4;
							if (background.getEnemyManager().enemyVector.at(index)->shootDeathTimer > 1 && background.getEnemyManager().enemyVector.at(index)->shootDeathTimer < 3)
							{
								audio.enemyDeath.play();
								audio.enemyDeath.setVolume(soundScreen.soundValue);
								score.AddScore(0.0001);
								//cout << "Deadddddddddddddddddddddddddddddddd" << endl;
							}
					}

				}
			}

			


			// Code for implementing the VIEW
			playerX = player.getSprite().getPosition().x;
			playerY = player.getSprite().getPosition().y;
			view1.setCenter(sf::Vector2f(playerX, playerY));

			//cout << "ENEMEMEMEMEMEY HEALTH" << player.m_enemyHealth << endl;

			//If the player is within a certain distance of the enemy the enemy will attack
			if (player.getSprite().getPosition().x > enemy.getSprite().getPosition().x - 120 &&
				player.getSprite().getPosition().x < enemy.getSprite().getPosition().x + 120 &&
				player.getSprite().getPosition().y > enemy.getSprite().getPosition().y - 120 &&
				player.getSprite().getPosition().y < enemy.getSprite().getPosition().y + 120)
			{
				if (enemySwingWait < 30)
				{
					enemy.enemySwing = true;
				}
				enemySwingWait++;
				if (enemySwingWait >= 30)
				{
					enemySwingWait = 0;
				}
			}


			// If the player DIES the Game Ends
			if (player.alive == false)
			{
				gameOverTimer++;
				if (gameOverTimer < 5)
				{
					audio.playerDeath.play();
					audio.playerDeath.setVolume(soundScreen.soundValue);
				}
				if (gameOverTimer >= 50)
				{
					player.m_PlayerSprite.setPosition(1000, 100);
					presentGameState = GameStates::GameOver;
					gameOverTimer = 0;
					player.alive = true;
				}
			}
			// if the player wants to restart the game
			if (reset == true)
			{

				background.Restart();

				background.getWeapon().batAlive = true;
				background.getWeapon().rifleAlive = true;
				player.rifle = false;
				player.alive = true;
				enemy.alive = true;

				//hostage.alive = true;
				background.getLevelState().levelComplete = false;
				audio.GameplayMusic.stop();
				audio.GameplayMusic.play();
				audio.GameplayMusic.setVolume(soundScreen.soundValue);
				//player.enemyLife = true;
				player.m_enemyHealth = 50;
				//player.m_PlayerSprite.setPosition(0.0f, 0.0f);
				player.presentDirection = Direction::Right;
				score.Reset(0);
				score.multiplier = 0;
				pause.Reset();
				reset = false;
				score.score = 0;

			}
		}


		else if (GameStates::GameOver == presentGameState)
		{

			//window.clear();
			gameOverScreen.draw(window);
		}

		// PAUSE - code for if PAUSE is the present GameState
		else if (GameStates::Pause == presentGameState)
		{
			if (timer >= 15)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				{
					if (pause.pauseIndex == 0)
					{
						timer = 0;
						presentGameState = GameStates::Play;
						audio.pausePress.play();
						audio.pausePress.setVolume(soundScreen.soundValue);
						audio.GameplayMusic.play();
						audio.GameplayMusic.setVolume(soundScreen.soundValue);
					}
					else if (pause.pauseIndex == 1)
					{
						presentGameState = GameStates::Play;
						reset = true;
					}
					else if (pause.pauseIndex == 2)
					{
						timer = 0;
						presentGameState = GameStates::Options;
						options.optionsReturn = false;
						options.Reset();
					}
					else if (pause.pauseIndex == 3)
					{
						window.close();
					}
				}

				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					// calls the Up() method
					pause.Up();
					timer = 0;
				}

				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					// calls the Down() method
					pause.Down();
					timer = 0;
				}
			}
		}

		// All of these are for Drawing
		///////////////
		// First one: if the present game state is Main, we will draw the MAIN MENU
		if (presentGameState == GameStates::Main)
		{
			menu.Draw(window);
		}
		else if (presentGameState == GameStates::SplashScreen)
		{
			splash.draw(window);
		}
		else if (presentGameState == GameStates::Sound)
		{
			window.clear();
			soundScreen.draw(window);
			soundScreen.Load(tickTexture);
		}
		else if (presentGameState == GameStates::Options)
		{
			window.clear();
			options.draw(window);
		}
		else if (presentGameState == GameStates::Pause)
		{
			window.clear();
			view1.reset(sf::FloatRect(0, 0, screenWidth, screenHeight));
			view1.zoom(0.75);
			window.setView(view1);
			pause.draw(window);
		}
		else if (presentGameState == GameStates::GameOver)
		{
			view1.reset(sf::FloatRect(0, 0, screenWidth, screenHeight));
			view1.zoom(0.75);
			window.setView(view1);
			gameOverScreen.draw(window);
		}
		// if the present game state is Play, we will draw the background and the other elements
		else if (presentGameState == GameStates::Play)
		{
			window.clear();
		
			window.setView(view1);
			background.Draw(&window);
			background.Update(event, score, soundScreen);

			//enemyManager.Update();

			player.Load(playerTexture, *&player.bullet.getBulletTexture());
			player.Update();
			player.draw(window);
			//player.BulletCollisions(enemy);

			////enemy.Load(enemyTexture);
			//enemy.Update();
			//enemy.draw(window);

			/*hostage.Load(hostageTexture);
			hostage.draw(window);*/

			background.getWeapon().Load(weaponTexture);
			background.getWeapon().draw(window);

			//collisionDetection.Update(Player &player, s>> &background.enemyManager.enemyVector)

			/*wall.Load(wallTexture);
			wall.draw(window);*/

			//wall.collisionDetection(player.m_PlayerSprite.getPosition());

		//	wallManager.RetrievePlayerPosition(player.m_PlayerSprite.getPosition());

			background.getLevelState().Load(weaponTexture);
			background.getLevelState().draw(window);
			background.getLevelState().logoMove();
			//levelState.m_levelGoalSprite.setPosition(playerX, playerY);
			background.getLevelState().m_levelCompleteSprite.setPosition(playerX - window.getSize().x / 5, playerY - window.getSize().y / 4);

			score.Update(player.getPosition().x, player.getPosition().y);
			//score.
			score.scoreText.setPosition(playerX - window.getSize().x / 3, playerY - window.getSize().y / 3);
			score.mulitplierText.setPosition(playerX + window.getSize().x / 5.5, playerY - window.getSize().y / 3);
			score.draw(window);
		}

	//	cout << enemyManager.enemyVector.size() << endl;
		//cout << "PPPPPPPPPPPPPPPPPPPPPPPPPLOLLLLLLLLLLLLLLLLLAAAAAAAAAAAATTTTTTTTTTTERR" <<  player.m_PlayerSprite.getPosition().x << endl;
		window.display();
	}
}

