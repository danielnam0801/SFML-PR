#include "Land.h"
#include "define.h"

Land::Land(std::shared_ptr<GameData> _data)
	:m_gameData(_data)
{
	Init();
}

void Land::Init()
{
	sf::Sprite sprite1(m_gameData->Resmgr.GetTexture("Land"));
	sf::Sprite sprite2(m_gameData->Resmgr.GetTexture("Land"));
	sprite1.setPosition(0, m_gameData->Window.getSize().y - sprite1.getGlobalBounds().height);
	sprite2.setPosition(sprite1.getGlobalBounds().width, m_gameData->Window.getSize().y - sprite1.getGlobalBounds().height);
	m_vecSprite.push_back(sprite1);
	m_vecSprite.push_back(sprite2);

	landHeight = sprite1.getLocalBounds().height;
}

void Land::Update(float _dt)
{
	for (size_t i = 0; i < m_vecSprite.size(); ++i)
	{
		m_vecSprite[i].move(-PIPE_RAND_VALUE * _dt, 0);
		if (m_vecSprite[i].getGlobalBounds().left < 
			-m_vecSprite[i].getGlobalBounds().width)
		{
			sf::Vector2f pos(m_gameData->Window.getSize().x, m_vecSprite[i].getPosition().y);
			m_vecSprite[i].setPosition(pos);
		}
	}
}

void Land::Render()
{
	for (size_t i = 0; i < m_vecSprite.size(); ++i)
	{
		m_gameData->Window.draw(m_vecSprite[i]);
	}
}
