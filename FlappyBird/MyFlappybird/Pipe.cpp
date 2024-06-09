#include "Pipe.h"
#include "define.h"
#include<iostream>
Pipe::Pipe(std::shared_ptr<GameData> _data)
	: m_gamedata(_data)
{
	m_landHeight = m_gamedata->Resmgr.GetTexture("Land").getSize().y;
}

void Pipe::Update(float _dt)
{
	for (size_t i = 0; i < m_vecPipeSprite.size();)
	{
		if (m_vecPipeSprite[i].getGlobalBounds().left <
			-m_vecPipeSprite[i].getGlobalBounds().width)
			m_vecPipeSprite.erase(m_vecPipeSprite.begin() + i);
		else
		{
			m_vecPipeSprite[i].move(- PIPE_MOVESPEED * _dt,0);
			i++;
		}
	}
//	std::cout << m_vecPipeSprite.size() << std::endl;

	// Score PIPE
	for (size_t i = 0; i < m_vecScorePipeSprite.size();)
	{
		if (m_vecScorePipeSprite[i].getGlobalBounds().left <
			-m_vecScorePipeSprite[i].getGlobalBounds().width)
			m_vecScorePipeSprite.erase(m_vecScorePipeSprite.begin() + i);
		else
		{
			m_vecScorePipeSprite[i].move(-PIPE_MOVESPEED * _dt, 0);
			i++;
		}
	}
}

void Pipe::Render()
{
	for(size_t i = 0; i< m_vecPipeSprite.size();++i)
		m_gamedata->Window.draw(m_vecPipeSprite[i]);
}

void Pipe::SpawnUpdate()
{
	SetRandomOffset();
	SpawnPipeUp();
	SpawnPipeDown();
	SpawnScorePipe();
}

void Pipe::SpawnPipeUp()
{
	sf::Sprite sprite(m_gamedata->Resmgr.GetTexture("Pipe Up"));
	sprite.setPosition(m_gamedata->Window.getSize().x, -m_pipeOffset);
	m_vecPipeSprite.push_back(sprite);
}

void Pipe::SpawnPipeDown()
{
	sf::Sprite sprite(m_gamedata->Resmgr.GetTexture("Pipe Down"));
	sprite.setPosition(m_gamedata->Window.getSize().x,
		m_gamedata->Window.getSize().y - sprite.getGlobalBounds().height - m_pipeOffset);
	m_vecPipeSprite.push_back(sprite);
}

void Pipe::SpawnScorePipe()
{
	sf::Sprite sprite(m_gamedata->Resmgr.GetTexture("Score Pipe"));
	sprite.setPosition(m_gamedata->Window.getSize().x, 0);
	m_vecScorePipeSprite.push_back(sprite);
}
