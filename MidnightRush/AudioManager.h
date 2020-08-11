////////////////////////////////////////////////////////////////////////////////////////////////////
//////  Contributors: Thomas Butler, Kevin Boylan
//////
//////  Used to load in sounds and music
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SFML\Audio.hpp>
using namespace sf;
#include <iostream>
using namespace std;

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	/////////MUSIC//////
	// used for the background music
	Sound GameplayMusic;
	SoundBuffer GameplayMusicBuffer;

	// used for music in the Splash gamestate
	Sound splashMusic;
	SoundBuffer splashMusicBuffer;


	////SOUNDS//////
	Sound riflePickUp;
	SoundBuffer rifleBuffer;

	Sound rifleShoot;
	SoundBuffer rifleShootBuffer;

	Sound batPickUp;
	SoundBuffer batBuffer;

	Sound batSwing;
	SoundBuffer batSwingBuffer;

	Sound playerDeath;
	SoundBuffer playerDeathBuffer;

	Sound enemyDeath;
	SoundBuffer enemyDeathBuffer;

	Sound hostageGroan;
	SoundBuffer hostageGroanBuffer;

	Sound menuScroll;
	SoundBuffer menuScrollBuffer;

	Sound pausePress;
	SoundBuffer pausePressBuffer;

	Sound gameStart;
	SoundBuffer gameStartBuffer;

	float groan;
};

