#include "Flash.h"

Flash::Flash(std::shared_ptr<GameData> _data)
	: m_gamedata(_data)
	, m_flashSpeed(500.f)
	, m_IsFlashOn(true)
{
	m_backShape.setSize(sf::Vector2f(m_gamedata->Window.getSize()));
	m_backShape.setFillColor(sf::Color(255, 255, 255, 0));
}

void Flash::Update(float _dt)
{
	// �÷��� �����϶� �����ߵ��� �����ߵ���.. 	// �����ϴ� �����̶�. // �����ϴ� ������.
	if (m_IsFlashOn)
	{
		int alpha = m_backShape.getFillColor().a + (m_flashSpeed * _dt);
		if (alpha >= 255)
		{
			alpha = 255;
			m_IsFlashOn = false;
		}
		m_backShape.setFillColor(sf::Color(255, 255, 255, alpha));
	}
	else
	{
		int alpha = m_backShape.getFillColor().a - (m_flashSpeed * _dt);
		if (alpha <= 0)
		{
			alpha = 0;
			//m_IsFlashOn = true;
		}
		m_backShape.setFillColor(sf::Color(255, 255, 255, alpha));
	}


}

void Flash::Render()
{
	m_gamedata->Window.draw(m_backShape);
}
