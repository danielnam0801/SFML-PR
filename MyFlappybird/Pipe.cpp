#include "Pipe.h"
#include "define.h"

Pipe::Pipe(std::shared_ptr<GameData> _data)
	: m_gameData(_data)
{
}

void Pipe::Update(float _dt)
{
	if (m_clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY) {
		m_clock.restart();
		SpawnPipeDown();
		SpawnPipeUp();
	}
}

void Pipe::Render()
{
	for (size_t i = 0; i < m_vecpipesprite.size(); ++i) {
		m_gameData->Window.draw(m_vecpipesprite[i]);
	}
}

void Pipe::SpawnPipeUp()
{
	sf::Sprite pipe;
	pipe.setTexture(m_gameData->Resmgr.GetTexture("Pipe Up"));
	pipe.setPosition(m_gameData->Window.getSize().x - 100, pipe.getGlobalBounds().height/2);
	m_vecpipesprite.push_back(pipe);
}

void Pipe::SpawnPipeDown()
{
	sf::Sprite pipe;
	pipe.setTexture(m_gameData->Resmgr.GetTexture("Pipe Down"));
	pipe.setPosition(m_gameData->Window.getSize().x - 100, m_gameData->Window.getSize().y + pipe.getGlobalBounds().height/2);
	m_vecpipesprite.push_back(pipe);
}
