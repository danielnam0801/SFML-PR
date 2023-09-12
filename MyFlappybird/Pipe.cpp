#include "Pipe.h"
#include "define.h"

Pipe::Pipe(std::shared_ptr<GameData> _data)
	: m_gameData(_data)
{
}

void Pipe::Update(float _dt)
{
	for (size_t i = 0; i < m_vecpipesprite.size(); ++i)
	{
		m_vecpipesprite[i].move(-PIPE_MOVE_SPEED * _dt, 0);
	}
	if (m_clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY) {
		m_clock.restart();
		SpawnUpdate();
	}
	DeletePipeCheck();

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
	pipe.setTexture(m_gameData->Resmgr.GetTexture("Pipe Down"));
	pipe.setPosition(m_gameData->Window.getSize().x, -m_pipeOffset);
	m_vecpipesprite.push_back(pipe);
}

void Pipe::SpawnPipeDown()
{
	sf::Sprite pipe(m_gameData->Resmgr.GetTexture("Pipe Up"));
	pipe.setPosition(m_gameData->Window.getSize().x,
		m_gameData->Window.getSize().y - pipe.getGlobalBounds().height - m_pipeOffset);
	m_vecpipesprite.push_back(pipe);
}

void Pipe::SpawnUpdate()
{
	SetRandomOffset();
	SpawnPipeDown();
	SpawnPipeUp();
}

void Pipe::DeletePipeCheck()
{
	for (size_t i = 0; i < m_vecpipesprite.size(); ++i) {
		if (m_vecpipesprite[i].getPosition().x <
			-m_vecpipesprite[i].getGlobalBounds().width)
			m_vecpipesprite.erase(m_vecpipesprite.begin() + i);
	}
}
