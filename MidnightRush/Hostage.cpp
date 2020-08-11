#include "Hostage.h"


Hostage::Hostage(sf::Vector2f position)
{
	m_HostageSource = IntRect(0, 0, 140, 140);
	m_HostageSprite.setTextureRect(m_HostageSource);
	m_HostageSprite.setPosition(position);

	if (!m_HostageTexture.loadFromFile("Sprites Folder/hostage_left.png"))
	{
		// error...
	}

}


Hostage::~Hostage()
{

}

void Hostage::Load(Texture& _hostageTexture)
{
	m_HostageSprite.setTexture(m_HostageTexture);
}

void Hostage::draw(RenderWindow& _window)
{
	Load(m_HostageTexture);
	if (alive == true)
	{
		_window.draw(m_HostageSprite);
	}
}

void Hostage::Update(Player &player)
{
	DropHostage(player);
}


void Hostage::DropHostage(Player &player)
{
	if (player.saving == true)
	{
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
		{
			player.saving = false;
			alive = true;

			if (player.presentDirection == Direction::Right)
			{
				m_HostageSprite.setPosition(player.m_PlayerSprite.getPosition().x + 200, player.m_PlayerSprite.getPosition().y);
			}
			else if (player.presentDirection == Direction::Left)
			{
				m_HostageSprite.setPosition(player.m_PlayerSprite.getPosition().x - 200, player.m_PlayerSprite.getPosition().y);
			}
			else if (player.presentDirection == Direction::Up)
			{
				m_HostageSprite.setPosition(player.m_PlayerSprite.getPosition().x, player.m_PlayerSprite.getPosition().y - 200);
			}
			else if (player.presentDirection == Direction::Down)
			{
				m_HostageSprite.setPosition(player.m_PlayerSprite.getPosition().x, player.m_PlayerSprite.getPosition().y + 200);
			}
		}
	}
}