#include "AudioManager.h"

AudioManager::AudioManager()
{
	///////////////////////////////////////////////////////////////////////////////////////////
	if (!GameplayMusicBuffer.loadFromFile("Music/SweetDreamsInst.ogg"))
	{
		//error
		std::cout << "Gameplay Music not Loaded" << std::endl;
	}
	GameplayMusic.setBuffer(GameplayMusicBuffer);

	///////////////////////////////////////////////////////////////////////////////////////////
	if (!splashMusicBuffer.loadFromFile("Music/SplashMusic.ogg"))
	{
		//error
		std::cout << "Splash Music not Loaded" << std::endl;
	}
	splashMusic.setBuffer(splashMusicBuffer);


	if (!rifleBuffer.loadFromFile("Music/riflePickUp.ogg"))
	{
		//error
		std::cout << "Rifle sound not Loaded" << std::endl;
	}
	riflePickUp.setBuffer(rifleBuffer);

	///////////////////////////////////////////////////////////////////////////////////////////
	if (!rifleShootBuffer.loadFromFile("Music/rifleShoot.ogg"))
	{
		//error
		std::cout << "rifleShoot sound not Loaded" << std::endl;
	}
	rifleShoot.setBuffer(rifleShootBuffer);

	///////////////////////////////////////////////////////////////////////////////////////////
	if (!playerDeathBuffer.loadFromFile("Music/playerDeath.ogg"))
	{
		//error
		std::cout << "playerDeath sound not Loaded" << std::endl;
	}
	playerDeath.setBuffer(playerDeathBuffer);

	///////////////////////////////////////////////////////////////////////////////////////////
	if (!batSwingBuffer.loadFromFile("Music/batSwing.ogg"))
	{
		//error
		std::cout << "batSwing sound not Loaded" << std::endl;
	}
	batSwing.setBuffer(batSwingBuffer);

	//////////////////////////////////////////////////////////////////////////////////////////
	if (!batBuffer.loadFromFile("Music/batPickUp.ogg"))
	{
		//error
		std::cout << "bat sound not Loaded" << std::endl;
	}
	batPickUp.setBuffer(batBuffer);

	///////////////////////////////////////////////////////////////////////////////////////////
	if (!enemyDeathBuffer.loadFromFile("Music/enemyDeath.ogg"))
	{
		//error
		std::cout << "enemyDeath sound not Loaded" << std::endl;
	}
	enemyDeath.setBuffer(enemyDeathBuffer);

	///////////////////////////////////////////////////////////////////////////////////////////
	if (!hostageGroanBuffer.loadFromFile("Music/hostageGroan.ogg"))
	{
		//error
		std::cout << "hostageGroan sound not Loaded" << std::endl;
	}
	hostageGroan.setBuffer(hostageGroanBuffer);

	///////////////////////////////////////////////////////////////////////////////////////////
	if (!menuScrollBuffer.loadFromFile("Music/menuScroll.ogg"))
	{
		//error
		std::cout << "menuScroll sound not Loaded" << std::endl;
	}
	menuScroll.setBuffer(menuScrollBuffer);

	///////////////////////////////////////////////////////////////////////////////////////////
	if (!pausePressBuffer.loadFromFile("Music/pausePress.ogg"))
	{
		//error
		std::cout << "pausePress sound not Loaded" << std::endl;
	}
	pausePress.setBuffer(pausePressBuffer);

	///////////////////////////////////////////////////////////////////////////////////////////
	if (!gameStartBuffer.loadFromFile("Music/gameStart.ogg"))
	{
		//error
		std::cout << "gameStart sound not Loaded" << std::endl;
	}
	///////////////////////////////////////////////////////////////////////////////////////////
	if (!gameStartBuffer.loadFromFile("Music/gameStart.ogg"))
	{
		//error
		std::cout << "gameStart sound not Loaded" << std::endl;
	}
	gameStart.setBuffer(gameStartBuffer);
	groan = 0.0f;
}


AudioManager::~AudioManager()
{
}
