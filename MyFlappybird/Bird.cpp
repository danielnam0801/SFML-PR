#include "Bird.h"

Bird::Bird(std::shared_ptr<GameData> _data)
	: m_gameData(_data)
	, m_animiter(0)
{
	m_vecanim.push_back(m_gameData->Resmgr.GetTexture("Bird 1"));
	m_vecanim.push_back(m_gameData->Resmgr.GetTexture("Bird 2"));
	m_vecanim.push_back(m_gameData->Resmgr.GetTexture("Bird 3"));
	m_vecanim.push_back(m_gameData->Resmgr.GetTexture("Bird 4"));
	Init();
}

void Bird::Init()
{
	m_birdsprite.setTexture(m_vecanim[m_animiter]);
	m_birdsprite.setPosition(100,
		(m_gameData->Window.getSize().y - m_gameData->Resmgr.GetTexture("Land").getSize().y)/2);
}

void Bird::Update(float dt)
{
	AnimateBird(dt);
}

void Bird::Render()
{
	m_gameData->Window.draw(m_birdsprite);
}

void Bird::BirdMove()
{

}

void Bird::AnimateBird(float _dt)
{
	static float time = 0;
	time += _dt;
	if (time > BIRD_ANIMATION_DURATION / m_vecanim.size())
	{
		time = 0;
		if (m_animiter == m_vecanim.size() -1)
			m_animiter = 0;
		else
			m_animiter++;
		m_birdsprite.setTexture(m_vecanim[m_animiter]);
	}
}