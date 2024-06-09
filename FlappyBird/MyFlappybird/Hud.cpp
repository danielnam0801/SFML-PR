#include "Hud.h"
#include<sstream>
Hud::Hud(std::shared_ptr<GameData> _data)
	: m_gamedata(_data)
	, m_twinkelSpeed(800.f)
{
	m_scoretext.setFont(m_gamedata->Resmgr.GetFont("Flappy Font"));
	m_scoretext.setString("0");
	m_scoretext.setCharacterSize(128);
	m_scoretext.setFillColor(sf::Color::White);
	m_scoretext.setOrigin(m_scoretext.getGlobalBounds().width / 2,
		m_scoretext.getGlobalBounds().height / 2);
	m_scoretext.setPosition(m_gamedata->Window.getSize().x / 2
	,m_gamedata->Window.getSize().y / 5);

	m_highScoretext.setFont(m_gamedata->Resmgr.GetFont("Flappy Font"));
	m_highScoretext.setString("High Score!!");
	m_highScoretext.setCharacterSize(30);
	m_highScoretext.setFillColor(sf::Color(255, 192, 203));
	m_highScoretext.setOrigin(m_highScoretext.getGlobalBounds().width / 2
		, m_highScoretext.getGlobalBounds().height / 2);
	m_highScoretext.setPosition(m_gamedata->Window.getSize().x / 2
		, m_scoretext.getPosition().y - m_gamedata->Window.getSize().y / 10);
}

void Hud::Update(int _score)
{
	std::stringstream ss;
	ss << _score;
	m_scoretext.setString(ss.str());
}

void Hud::Render()
{
	m_gamedata->Window.draw(m_scoretext);
}

void Hud::HighUpdate(float _dt)
{
	if (m_isHighScore)
	{
		int alpha = m_highScoretext.getFillColor().a + (m_twinkelSpeed * _dt);
		if (alpha >= 255)
		{
			alpha = 255;
			m_isHighScore = false;
		}
		m_highScoretext.setFillColor(sf::Color(255, 255, 255, alpha));
	}
	else
	{
		int alpha = m_highScoretext.getFillColor().a - (m_twinkelSpeed * _dt);
		if (alpha <= 0)
		{
			alpha = 0;
			m_isHighScore = true;
		}
		m_highScoretext.setFillColor(sf::Color(255, 255, 255, alpha));
	}
}

void Hud::HighRender()
{
	m_gamedata->Window.draw(m_highScoretext);
}
