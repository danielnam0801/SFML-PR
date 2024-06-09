#include "Land.h"
#include "define.h"

Land::Land(std::shared_ptr<GameData> _data)
	: m_gamedata(_data)
{
	Init();
}

void Land::Init()
{
	// todo: 텍스처 불러와서 입히고, 위치를 정해줘야돼. vector에도 넣어야돼.
	sf::Sprite sprite1(m_gamedata->Resmgr.GetTexture("Land"));
	sf::Sprite sprite2(m_gamedata->Resmgr.GetTexture("Land"));

	sprite1.setPosition(0,m_gamedata->Window.getSize().y 
		- sprite1.getGlobalBounds().height);
	sprite2.setPosition(sprite1.getGlobalBounds().width, m_gamedata->Window.getSize().y
		- sprite1.getGlobalBounds().height);

	m_vecSprite.push_back(sprite1);
	m_vecSprite.push_back(sprite2);

}

void Land::Update(float _dt)
{
	for (size_t i = 0; i < m_vecSprite.size(); ++i)
	{
		m_vecSprite[i].move(-PIPE_MOVESPEED * _dt, 0);
		// 왼쪽으로 넘어가면, 랜드를 다시 돌려줘야돼.
		if (m_vecSprite[i].getGlobalBounds().left < -m_vecSprite[i].getGlobalBounds().width)
		{
			sf::Vector2f pos(m_gamedata->Window.getSize().x, m_vecSprite[i].getPosition().y);
//			,m_gamedata->Window.getSize().y - m_vecSprite[i].getGlobalBounds().height);
			m_vecSprite[i].setPosition(pos);
		}
	}
}

void Land::Render()
{
	for (size_t i = 0; i < m_vecSprite.size(); ++i)
	{
		m_gamedata->Window.draw(m_vecSprite[i]);
	}
}
