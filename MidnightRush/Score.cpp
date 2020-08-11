#include "Score.h"

Score::Score()
{
	

}

Score::Score(float base, float height)
{
	// loads in a font
	if (!myFont.loadFromFile("fonts/Shoguns Clan.ttf"))
	{
		// error
	}

	//int score = 0;

	score = 0;
	multiplier = 0;
	increase = 800;
	clockStart = false;
	clockRestart = false;
	bonus = 100;

	//int multiplier = 0;


	scoreText.setFont(myFont);
	scoreText.setScale(2.0f, 2.0f);
	scoreText.setPosition(sf::Vector2f(player.m_PlayerSprite.getPosition().x, player.m_PlayerSprite.getPosition().y));
	scoreText.setCharacterSize(30);
	scoreText.setStyle(sf::Text::Bold);
	scoreText.setColor(sf::Color::Red);
	//scoreText.setString("Score: " + std::to_string(score));

	mulitplierText.setFont(myFont);
	mulitplierText.setScale(2.0f, 2.0f);
	mulitplierText.setPosition(sf::Vector2f(base / 2 + 400, height / 3));
	mulitplierText.setCharacterSize(30);
	mulitplierText.setStyle(sf::Text::Bold);
	mulitplierText.setColor(sf::Color::Red);
	//mulitplierText.setString("Multiplier: " + std::to_string(multiplier));

	
}

Score::~Score()
{

}

void Score::AddScore(int newScoreValue)
{
	score += increase;



	//std::cout << "Score: " << score << std::endl;
	multiplier++;

	UpdateScore();
	
	clockStart = true;
	
	scoreText.setString("Score: " + std::to_string(score));
	//MulitiplierReset();
	
}

void Score::UpdateScore()
{
	if (multiplier <= 10 && multiplier > 1)
	{
		/*resetIncrease += increase * multiplier;
		increase = (increase * multiplier) / 2;*/
		score += increase * multiplier;
		
	}
	//score
	//scoreText.text = "Score: " + score;
}

void Score::MulitiplierReset()
{
	if (clockStart == true)
	{
		clock.restart();
		clockStart = false;
		clockRestart = true;
		bonus = bonus * multiplier;
		
		
	}
}

void Score::Update(int playerX, int playerY)
{
	MulitiplierReset();

	duration = (clock.getElapsedTime().asSeconds() -  start);

	if (clockRestart == true && duration >= 7.0f)
	{
		multiplier = 0;
		increase = 800;
		clockRestart = false;
	//	bonus = bonus * multiplier;
		score += bonus;
		bonus = 100;
	}

	//UpdateScore();

	//std::cout << "SCCCCCCCCCCCCOOOOOOOOOOOOOOORRRRRRRRRRRRRRRRRRREEEEEEEEEEEEEE" << elapsedTime.asSeconds() << std::endl;
	scoreText.setString("Score: " + std::to_string(score));
	mulitplierText.setString("Multiplier: " + std::to_string(multiplier));
//	cout << " xxxxxxx " << player.getSprite().getPosition().x << endl;
	//scoreText.setPosition(sf::Vector2f(playerX, playerY));
}

void Score::Reset(int reset)
{
	score = reset;
	multiplier = reset;
	bonus = 100;
}

void Score::draw(sf::RenderWindow &window)
{
	window.draw(scoreText);
	window.draw(mulitplierText);
}

	