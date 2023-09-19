#include "Hud.h"
#include <sstream>

Hud::Hud(std::shared_ptr<GameData> _data)
	:m_gameData(_data)
	,m_twinkleSpeed(800.f)
{
	m_scoreText.setFont(m_gameData->Resmgr.GetFont("Flappy Font"));
	m_scoreText.setString("0");
	m_scoreText.setCharacterSize(128);
	m_scoreText.setFillColor(sf::Color::White);
	m_scoreText.setOrigin(m_scoreText.getGlobalBounds().width / 2,
		m_scoreText.getGlobalBounds().height / 2);
	m_scoreText.setPosition(m_gameData->Window.getSize().x / 2,
		m_gameData->Window.getSize().y / 5);
	
	m_highScoreText.setFont(m_gameData->Resmgr.GetFont("Flappy Font"));
	m_highScoreText.setString("High Score!");
	m_highScoreText.setCharacterSize(30);
	m_highScoreText.setFillColor(sf::Color(255, 192, 203));
	m_highScoreText.setOrigin(m_highScoreText.getGlobalBounds().width / 2,
		m_highScoreText.getGlobalBounds().height / 2);
	m_highScoreText.setPosition(m_gameData->Window.getSize().x / 2,
		m_scoreText.getPosition().y - m_gameData->Window.getSize().y / 10);
}

void Hud::Update(int _score)
{
	std::stringstream ss;
	ss << _score;
	m_scoreText.setString(ss.str());
}

void Hud::Render()
{
	m_gameData->Window.draw(m_scoreText);
}

void Hud::HighUpdate(float _dt)
{

	if (ishighScore)
	{
		int alpha = m_highScoreText.getFillColor().a + (m_twinkleSpeed * _dt);
		if (alpha >= 255)
		{
			ishighScore = false;
			alpha = 255;
		}
		m_highScoreText.setFillColor(sf::Color(255, 255, 255, alpha));
	}
	else {
		int alpha = m_highScoreText.getFillColor().a - (m_twinkleSpeed * _dt);
		if (alpha <= 0)
		{
			ishighScore = true;
			alpha = 0;
		}
		m_highScoreText.setFillColor(sf::Color(255, 255, 255, alpha));
	}
}

void Hud::HighRender()
{
	m_gameData->Window.draw(m_highScoreText);
}
