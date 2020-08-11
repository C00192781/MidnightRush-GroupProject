////////////////////////////////////////////////////////////////////////////////////////////////////////////
////// Contributors: Kevin Boylan
////// Class written by Kevin Boylan
//////
////// Comprised of Collision Detection Code taken out of Main.cpp
////// Kevin Boylan: 
//////
////////////////////////////////////////////////////////////////////////////////////////////////////////////



#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "EnemyManager.h"
#include "Weapon.h"
#include "LevelState.h"
#include "HostageManager.h"
#include "AudioManager.h"
#include "Score.h"
#include "SoundScreen.h"

using namespace sf;

class CollisionDetection
{
public:
	CollisionDetection();
	~CollisionDetection();

	void Update(Player &player, EnemyManager &enemyManager, Weapon &weapon, LevelState &levelState, HostageManager &hostageManager, AudioManager &audio,Score &score, sf::Event &event, SoundScreen &sound);
	void Melee(Player &player, EnemyManager &enemyManager, AudioManager &audio, Score &score, sf::Event &event, SoundScreen &sound);
	void PlayerDeath(Player &player, EnemyManager &enemyManager, AudioManager &audio, SoundScreen &sound);
	void BatPickUp(Player &player, Weapon &weapon, AudioManager &audio, SoundScreen &sound);
	void GunPickUp(Player &player, Weapon &weapon, AudioManager &audio, SoundScreen &sound);
	void LevelStateCollision(Player &player, LevelState &levelState, AudioManager &audio, SoundScreen &sound);
	void Hostage(Player &player, EnemyManager &enemyManager, HostageManager &hostageManager, AudioManager &audio, SoundScreen &sound);
	
	//SoundScreen soundScreen;
	/*void hostage(Player &player, )*/


private:
};