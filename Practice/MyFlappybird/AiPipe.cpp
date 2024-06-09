#include "AiPipe.h"
#include "define.h"
AiPipe::AiPipe(std::shared_ptr<GameData> _data, int _x, int _y)
	: m_gamedata(_data)
	, m_x(_x)
	, m_y(_y)
	, m_moveTimer(PIPE_SPEED)
	, m_dir(rand() % 2)
{
	m_sprite.setTexture(m_gamedata->Resmgr.GetTexture("Ai pipe"));
}

void AiPipe::Update(float _dt)
{
	m_x -= PIPE_SPEED;
	if (m_y == PIPE_INDENT)
		m_dir = 1;
	else if (m_y == GROUND_Y - GAP_SIZE - PIPE_INDENT)
		m_dir = 0;
	if (m_moveTimer == 0)
	{
		m_moveTimer = 1;
		if (m_dir == 0)
			m_y--;
		else
			m_y++;
	}
	else
		m_moveTimer--;
}

void AiPipe::Render()
{
	m_sprite.setPosition(m_x, m_y - SCREEN_HEIGHT);
	m_sprite.setTextureRect(sf::IntRect(BIRD_SIZE *2, 0, 2*BIRD_SIZE, SCREEN_HEIGHT));
	m_gamedata->Window.draw(m_sprite);

	m_sprite.setPosition(m_x, m_y + GAP_SIZE);
	m_sprite.setTextureRect(sf::IntRect(0, 0, 2 * BIRD_SIZE, SCREEN_HEIGHT));
	m_gamedata->Window.draw(m_sprite);

}
