////////////////////////////////////////////////////////////////////////////////////////////////////////////
////// Contributors: Kevin Boylan, Thomas Bulter
////// All methods and overall framework written by Kevin Boylan
////// Kevin Boylan: 1st Level, 3rd Level
////// Thomas Butler: 2nd Level
////// Used to load in a background, consisting of tiles/sprites (easier to create and customize the maps)
////// Started: 25/10/2016
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp> 
#include <memory>

#include "Player.h"
#include "Wall.h"
#include "Floor.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "WallManager.h"
#include "HostageManager.h"
#include "CollisionDetection.h"
#include "Weapon.h"
#include "LevelState.h"
#include "AudioManager.h"
#include "Score.h"
#include "SoundScreen.h"

class Background
{

public:
	Background();
	int *pMap;
	void CreateMap();
	void SelectMap(int mapCounter);
	void ResetMap();
	void Restart();
	
	
	void Draw(sf::RenderWindow *window);
	void Update(sf::Event &event, Score & score, SoundScreen & sound);
	
	std::shared_ptr<int> getMapCount();

	

	Player & getPlayer();
	Weapon & getWeapon();

	//Score & getScore();

	SoundScreen & getSoundScreen();
	
	EnemyManager & getEnemyManager();
	LevelState & getLevelState();
	

	// I'll need to add in a method for changing the map

	

private:
	// parameters necessary for the maps
	int maxRow;
	int maxCol;
	int maxSquares;


	sf::Vector2f startingPosition;


	/*bool xBool = false;
	bool yBool = false;*/
	

	// for the first map
	static const int map[30][30];

	// for the SECOND map
	static const int map2[30][30];

	// for the THIRD map
	static const int map3[30][30];

	sf::Texture levelTexture;
	// shared pointer holding the levels
	std::shared_ptr<int> levelCount;

	

	//std::vector<shared_ptr<Wall>> wallVector;

	std::vector<shared_ptr<Floor>> floorVector;

	EnemyManager enemyManager;

	HostageManager hostageManager;

	CollisionDetection collisionDetection;

	WallManager wallManager;

	Player player;

	Weapon weapon;

	LevelState levelState;

	AudioManager audio;

//	Score score;

	SoundScreen sound;



	/*EnemyManager enemyManager;*/

	//std::vector<shared_ptr<Enemy>> enemyVector;

//	std::vector<sf::Sprite> spriteVector;


};
