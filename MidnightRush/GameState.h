////////////////////////////////////////////////////////////////////////////////////
////// Contributors: Kevin Boylan, Thomas Butler
//////
////// Used to set up multiple game states which we will be able to switch between
////// Started: 25/10/2016
///////////////////////////////////////////////////////////////////////////////////

// enum classes provided for different situations and purposes
enum class GameStates
{
	// This enumerator is associated with the overall gameplay states
	SplashScreen,
	LicenceScreen,
	Main,
	Options,
	Help,
	Sound,
	Load,
	Play,
	GameOver, 
	Pause,
	Winner
};

